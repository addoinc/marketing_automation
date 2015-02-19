<?php

/**
 * @file
 * The file contains the MarketingAutomation core class to call any API
 *
 */

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
    }
    else if (isset($result['data'])) {
      $msg = $result['data'];
    }
    else {
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
  // Will be initialized in constructor
  private $login_username;
  private $login_password;
  private $call_type = '_curl';
  private $jsonrpc_version = '2.0';

  // These values will be updated after successfull authentication
  private $session_id = NULL;
  private $auth_id = NULL;

  // API end point as per the url https://a.volacciapp.com/api/v2/rpc/documentation.php#controller=Welcome
  private $endpoint = 'https://a.volacciapp.com/api/v2/rpc/server.php';

  /**
   * Constructor function which will authenticate username, password to access API
   *
   * @param string $username
   * @param string $password
   */
  function __construct($username, $password, $call_type = '_do_request_curl') {
    // Login details
    if ($this->authenticate($username, $password, $call_type)) {
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
  private function authenticate($username, $password, $call_type = '_do_request_curl') {
    if (isset($_SESSION['automatr_session_id']) && $_SESSION['automatr_session_id'] != NULL) {
      $this->session_id = $_SESSION['automatr_session_id'];
      return TRUE;
    }
    $controller = 'User';
    $method = 'getSessionId';
    $params = array('username' => $username, 'password' => $password);
    if ($call_type == '_do_request_curl') {
      $response = $this->_do_request_curl($controller, $method, $params, FALSE);
    }
    else {
      $response = $this->_do_request_drupal_http($controller, $method, $params);
    }
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
   * Returns endpoint for the API
   * @return
   *  String with endpoint
   */
  public function get_end_point() {
    return $this->endpoint;
  }

  /**
   * Returns Final Url for the current API Call
   * @return
   *  String with final url
   */
  public function build_url($controller, $method) {
    $url = '';
    if ($controller == 'User' && $method == 'getSessionId') {
      $url = $this->endpoint . '?' . 'Controller=' . $controller;
    }
    else {
      $url = $this->endpoint . '?' . 'Controller=' . $controller . '&strSessionId=' . $this->session_id;
    }
    return $url;
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
  public function do_request($controller, $method, $params, $call_type = '_do_request_curl', $unique_id = NULL) {
    if (empty($this->login_username) || empty($this->login_password)) {
      throw new Exception('Authentication details are not provided, please provide valid authentication details');
    }
    if ($call_type == '_do_request_curl') {
      return $this->_do_request_curl($controller, $method, $params, TRUE, $unique_id) ;
    }
    else{
      return $this->_do_request_drupal_http($controller, $method, $params, $unique_id);
    }
  }

  /**
   * Private function which will do drupal_http_request request and call the API function
   * @param string $controller
   * @param string $method
   * @param array $params
   *   Key value pairs of parameters to API call
   * @return
   *   Returns json object of API response
   */
  private function _do_request_drupal_http($controller, $method, $params, $unique_id = NULL) {
    if (!function_exists('drupal_http_request')) {
      throw new Exception('Marketing Automation needs the CURL PHP extension.');
    }
    if ($unique_id == NULL) {
      $unique_id = uniqid();
    }
    // build endpoint url
    $url = $this->build_url($controller, $method);
    $json_params = array(
      'id' => $unique_id,
      'method' => $method,
      'params' => $params,
    );
    $encoded_json_params = json_encode($json_params);
    $options = array(
      'method' => 'POST',
      'data' => $encoded_json_params,
      'timeout' => 15,
      'max_redirects' => 10,
      'headers' => array('Content-Type' => 'application/json', 'Accept' => 'application/json'),
    );
    $response = drupal_http_request($url, $options);

    if (isset($response->code)) {
      switch($response->code) {
      case 401 :
	drupal_set_message('Authentication failed');
	$e = new MarketingAutomationApiException(array(
			 'code' => $response->code,
			 'message' => $response->data,
	      ));
	$this->session_id = NULL;
	if (isset($_SESSION['automatr_session_id'])) {
	  unset($_SESSION['automatr_session_id']);
	}
	throw $e;
	break;
      case 404 :
        $e = new MarketingAutomationApiException(array(
             'code' => $response->code,
             'message' => $response->data,
              ));
        throw $e;
        break;

      case 500 :
        $e = new MarketingAutomationApiException(array(
             'code' => '500',
             'message' => 'Server is Down',
              ));
        throw $e;
        break;

      case 200 :
      //We are good. Nothing much to do here.
      break;
      default :
      	$e = new MarketingAutomationApiException(array(
      			 'code' => $response->code,
      			 'message' => 'Something went wrong very badly',
      	      ));
      	throw $e;
      	break;
            }
    }

    // Decode reponse
    $response = json_decode($response->data);
    return $response;
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
  private function _do_request_curl($controller, $method, $params, $pass_login_details = TRUE, $unique_id = NULL) {
    if (!function_exists('curl_init')) {
      throw new Exception('Marketing Automation needs the CURL PHP extension.');
    }

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
    if ($unique_id == NULL) {
      $unique_id = uniqid();
      }
    curl_setopt($ch, CURLOPT_POSTFIELDS, json_encode(array(
          'id' => $unique_id,
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

    // Close curl connection
    curl_close($ch);

    return $response;
  }
}

