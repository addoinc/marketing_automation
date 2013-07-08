<?php

/**
 * @file
 * This file contains generatic class for EmailList controller and its methods
 * Look at more details at http://apps.net-results.com/api/v2/rpc/documentation.php#controller=EmailList
 */


require_once 'marketing_automation_core.inc';


/**
 * The EmailList controller class
 * Before using this make sure to configure automatr username and password at
 *  automatr configuration path admin/config/marketing/automatr/settings
 * Usage:
 * $email_list_obj = new MarketingAutomationAPI();
 * $result = $email_list_obj->call_method('Controller', 'Method', $params);
 */
class MarketingAutomationAPI extends MarketingAutomation {


  public function call_method($controller, $method, $params = array()) {

    require_once 'api_definition.inc';

    $method_props = $MarketingAutomationAPI[$controller][$method];
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

    if (empty($missed_required_params)) {
      return $this->do_request($controller, $method, $params);
    } else {
      $error_msg = 'Controller : ' . $controller . ', Method : ' . $method . ', Error message : Missed required parameters ' . implode(', ', $missed_required_params);
      throw new Exception($error_msg);
    }
  }


}