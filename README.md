marketing_automation
=====================
This is a marketing automation API.

Requirements
------------
1. PHP 5.3+
2. PHP CURL
3. PHP JSON Extension
3. Username, Password to access the API // Todo: Update information about how to get these.

Usage
-----
1. Check API definition in file api_definition.inc file
2. Example call to get the EmailList controller, getMultiple method

```php

require_once '/path/to/marketing_automation/marketing_automation_api.php';
$username = 'username'; // update this value with your username
$password = 'password'; // update this value with your password
$obj = new MarketingAutomationAPI($username, $password);
// Here default parameters defined for respective controller, method in api_definition.inc file will be applied
$email_lists = $obj->call_method('EmailList', 'getMultiple');

```
3. Example call to get the EmailLists of second page data assuming each page lists 50 records

```php

require_once '/path/to/marketing_automation/marketing_automation_api.php';
$username = 'username'; // update this value with your username
$password = 'password'; // update this value with your password
$obj = new MarketingAutomationAPI($username, $password);
$params = array('offset' => 51, 'limit' => 50, 'order_by' => 'email_list_name', 'order_dir' => 'ASC');
$email_lists = $obj->call_method('EmailList', 'getMultiple', $params);

```