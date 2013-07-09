<?php

/**
 * @file
 * The file contains the MarketingAutomation core class to call any API
 *
 */


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
    $controller = 'User';
    $method = 'getSessionId';
    $params = array('username' => $username, 'password' => $password);
    $response = $this->_do_request($controller, $method, $params, FALSE);
    if ($response->result) {
      // Once authentication is success, store the session id for future reference
      $this->session_id = $response->result;
      $this->auth_id = $response->id;
      return TRUE;
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
      $error_msg = 'Error executing the curl request' . ' ' . curl_errno($ch) . ' : ' . curl_error($ch);
      throw new Exception($error_msg);
    }

    // Decode reponse
    $response = json_decode($response);
    if (isset($response->error)) {
      throw new Exception($response->error->message);
    }

    // Close curl connection
    curl_close($ch);

    return $response;
  }

}

