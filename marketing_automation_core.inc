<?php

/**
 * @file
 * The file contains the generic helper class to call any API of automatr
 *
 */


/**
 * The Marketing Automation API class.
 * Before using this make sure to configure automatr username and password at
 *  automatr configuration path admin/config/marketing/automatr/settings
 * Usage:
 * $automatr = new MarketingAutomation();
 * $result = $automatr->do_request('controller', 'method', $params);
 */
class MarketingAutomation {

  // Marketing authentication details
  // Will be initiallized in constructor
  private  $login_username;
  private $login_password;
  private $jsonrpc_version = '2.0';

  // These values will be updated after successfull authentication
  private $session_id = null;
  private $auth_id = null;

  // API end point as per the url http://apps.net-results.com/api/v2/rpc/documentation.php#controller=Welcome
  private $endpoint = 'https://apps.net-results.com/api/v2/rpc/server.php';

  function __construct($username, $password) {
    // Login details
    if ($this->authenticate($username, $password)) {
      $this->login_username = $username;
      $this->login_password = $password;
    } else {
      throw new Exception('Authentication failed for the provided username and password');
    }

  }

  private function authenticate($username, $password) {
    $controller = 'User';
    $method = 'getSessionId';
    $params = array('username' => $username, 'password' => $password);
    $response = $this->_do_request($controller, $method, $params, FALSE);
    if ($response->result) {
      $this->session_id = $response->result;
      $this->auth_id = $response->id;
      return true;
    }
    return false;
  }

  public function get_sessionid() {
    return $this->session_id;
  }

  /**
   * Do request to api and return the output
   * @param controller - Controller of API
   */
  public function do_request($controller, $method, $params) {
    if (empty($this->login_username) || empty($this->login_password)) {
      throw new Exception('Authentication details are not provided, please provide valid authentication details');
    }
    $args = func_get_args();
    return call_user_func_array(array($this, '_do_request'), $args);
  }

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

