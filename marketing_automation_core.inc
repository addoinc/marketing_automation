<?php

/**
 * @file
 * The file contains the MarketingAutomation core class to call any API
 *
 */

if (!function_exists('curl_init')) {
  throw new Exception('Marketing Automation needs the CURL PHP extension.');
}
if (!function_exists('json_decode')) {
  throw new Exception('Marketing Automation needs the JSON PHP extension.');
}

/**
 * Thrown when an API call returns an exception.
 *
 */
class MarketingAutomationApiException extends Exception
{
  /**
   * The result from the API server that represents the exception information.
   */
  protected $result;

  /**
   * Make a new API Exception with the given result.
   *
   * @param array $result The result from the API server
   */
  public function __construct($result) {
    $this->result = $result;

    $code = isset($result['code']) ? $result['code'] : 0;

    if (isset($result['message'])) {
      $msg = $result['message'];
    } else if (isset($result['data'])) {
      $msg = $result['data'];
    } else {
      $msg = 'Unknown Error. Check getResult()';
    }

    parent::__construct($msg, $code);
  }

  /**
   * Return the associated result object returned by the API server.
   *
   * @return array The result from the API server
   */
  public function getResult() {
    return $this->result;
  }

  /**
   * To make debugging easier.
   *
   * @return string The string representation of the error
   */
  public function __toString() {
    $str = 'Exception ';
    if ($this->code != 0) {
      $str .= $this->code . ': ';
    }
    return $str . $this->message;
  }
}


/**
 * The Marketing Automation API class.
 * Usage:
 * $obj = new MarketingAutomation('username', 'password');
 * $result = $obj->do_request('controller', 'method', $params);
 */
class MarketingAutomation {

  // Marketing authentication details
  // Will be initiallized in constructor
  private $login_username;
  private $login_password;
  private $jsonrpc_version = '2.0';

  // These values will be updated after successfull authentication
  private $session_id = NULL;
  private $auth_id = NULL;

  // API end point as per the url http://apps.net-results.com/api/v2/rpc/documentation.php#controller=Welcome
  private $endpoint = 'https://apps.net-results.com/api/v2/rpc/server.php';

  /**
   * Constructor function which will authenticate username, password to access API
   *
   * @param string $username
   * @param string $password
   */
  function __construct($username, $password) {
    // Login details
    if ($this->authenticate($username, $password)) {
      $this->login_username = $username;
      $this->login_password = $password;
    } else {
      throw new Exception('Authentication failed for the provided username and password');
    }
  }

  /**
   * Do authenticate with API call and check if username, password is correct
   * These username, password details will be used to send every api call
   *
   * @param string $username
   * @param string $password
   *
   * @return bool
   *  Returns TRUE with authentication is success else returns FALSE
   */
  private function authenticate($username, $password) {
    if (isset($_SESSION['automatr_session_id'])) {
      $this->session_id = $_SESSION['automatr_session_id'];
      return TRUE;
    }
    $controller = 'User';
    $method = 'getSessionId';
    $params = array('username' => $username, 'password' => $password);
    $response = $this->_do_request($controller, $method, $params, FALSE);
		if(!empty($response)) {
			if ($response->result) {
				// Once authentication is success, store the session id for future reference
				$this->session_id = $response->result;
				$_SESSION['automatr_session_id'] = $response->result;
				$this->auth_id = $response->id;
				return TRUE;
			}
		}
    return FALSE;
  }

  /**
   * Returns session id of the authenticated user.
   * @return
   *  String with session id
   */
  public function get_sessionid() {
    return $this->session_id;
  }

  /**
   * Do request to api and return the output
   * @param string $controller
   * @param string $method
   * @param array $params
   *  Array with key value pairs of different parameters
   * @return
   *  Returns json object of API response.
   */
  public function do_request($controller, $method, $params) {
    if (empty($this->login_username) || empty($this->login_password)) {
      throw new Exception('Authentication details are not provided, please provide valid authentication details');
    }
    $args = func_get_args();
    return call_user_func_array(array($this, '_do_request'), $args);
  }

  /**
   * Private function which will do curl request and call the API function
   * @param string $controller
   * @param string $method
   * @param array $params
   *   Key value pairs of parameters to API call
   * @param bool $pass_login_details
   *   For authentication request the username, password should be passed as
   *   parameters. For other requests they should be passed for CURLOPT_USERPWD.
   *   This parameter is used to identify between authentication request and
   *   other request.
   * @return
   *   Returns json object of API response
   */
  private function _do_request($controller, $method, $params, $pass_login_details = TRUE) {
    // build endpoint url
    $url = $this->endpoint . '?' . 'Controller=' . $controller;

    // Set curl options
    $ch = curl_init($url);
    curl_setopt($ch, CURLOPT_SSL_VERIFYHOST, FALSE);
    curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, FALSE);
    curl_setopt($ch, CURLOPT_RETURNTRANSFER, TRUE);
    if ($pass_login_details) {
      curl_setopt($ch, CURLOPT_USERPWD, $this->login_username . ':' . $this->login_password);
    }
    curl_setopt($ch, CURLOPT_POSTFIELDS, json_encode(array(
          'id' => uniqid(),
          'method' => $method,
          'jsonrpc' => $this->jsonrpc_version,
          'params' => $params,
        )
      )
    );
    curl_setopt($ch, CURLOPT_POST, TRUE);

    // Execute curl
    $response = curl_exec($ch);
    if ($response === false) {
      $e = new MarketingAutomationApiException(array(
             'code' => curl_errno($ch),
             'message' => curl_error($ch),
      ));
      throw $e;
    }

    // Decode reponse
    $response = json_decode($response);
    if (!isset($response->result) && isset($response->code)) {
      $e = new MarketingAutomationApiException(array(
             'code' => $response->code,
             'message' => $response->message,
             'data' => $response->data
      ));
      throw $e;
    }
    if (isset($response->error)) {
      $e = new MarketingAutomationApiException(array(
             'code' => $response->error->code,
             'message' => $response->error->message,
             'data' => $response->error->data
      ));
      throw $e;
    }

    // Close curl connection
    curl_close($ch);

    return $response;
  }

}

