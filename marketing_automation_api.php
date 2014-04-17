<?php

/**
 * @file
 * This file contains MarketingAutomationAPI which will call API functions by validating the required parameters.
 * Look at more details at http://apps.net-results.com/api/v2/rpc/documentation.php#controller=Welcome
 */


require_once 'marketing_automation_core.inc';


/**
 * The MarketingAutomationAPI class
 * Before using this make sure you have username and password to call API
 * Usage:
 * $obj = new MarketingAutomationAPI('username', 'password');
 * $result = $obj->call_method('Controller', 'Method', $params);
 */
class MarketingAutomationAPI extends MarketingAutomation {

  /**
   * Call the method of API and return the output
   * @param string $controller
   * @param string $method
   * @param string $params
   *  Key value pairs of parameters.
   *  This function will include api_definition and check if any required
   *  parameter is missed or not and if any required parameter is missed
   *  If it has default value, it will pass the default value.
   */
  public function call_method($controller, $method, $params = array(), $call_type = '_do_request_curl') {
    // The above file will include variable $MarketingAutomationAPI
    require 'api_definition.inc';

    // Get the properties details of the respecting controller method
    $method_props = $MarketingAutomationAPI[$controller][$method];

    // Check if any required parameters missed
    // Assign the default values if not provided
    $missed_required_params = array();
    foreach ($method_props as $param => $props) {
      if ($props['required'] && !array_key_exists($param, $params)) {
        if (isset($props['default'])) {
          $params[$param] = $props['default'];
        } else {
          $missed_required_params[] = $param;
        }
      }
    }

    // If no required parameters are missed then do request
    if (empty($missed_required_params)) {
      return $this->do_request($controller, $method, $params, $call_type);
    } else {
      $error_msg = 'Controller : ' . $controller . ', Method : ' . $method . ', Error message : Missed required parameters ' . implode(', ', $missed_required_params);
      throw new Exception($error_msg);
    }
  }

}