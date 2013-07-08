<?php

/**
 * @file
 * This file contains entire API definition.
 */

define('LIMIT_VALUE', 50);
define('DEFAULT_RESULTS_PER_PAGE', 50);

$MarketingAutomationAPI = array(
   // Email List
  'EmailList' => array(
    'getMultiple' => array(
      'offset' => array('required' => true, 'default' => 0),
      'limit' => array('required' => true, 'default' => LIMIT_VALUE),
      'order_by' => array('required' => true, 'default' => 'email_list_name'),
      'order_dir' => array('required' => true, 'default' => 'ASC'),
      'filters' => array('required' => false)
    ),
    'deleteOne' => array(
      'email_list_id' => array('required' => true)
    ),
    'getFolderLeaves' => array(
      'folder_id' => array('required' => true),
      'blnIsRoot' => array('required' => false),
      'order_by' => array('required' => false, 'default' => 'email_list_name'),
      'order_dir' => array('required' => false, 'default' => 'ASC'),
    ),
    'setOne' => array(
      'email_list' => array('reauired' => true)
    ),
    'getContactParticipation' => array(
      'email_list_id' => array('required' => true),
      'contact_id'  => array('required' => true),
    ),
    'getResultsPerPage' => array(
      'intResultsPerPage' => array('required' => true),
      'arrAllowed' => array('required' => false),
    ),
  ),

  // Alert
  'Alert' => array(
    'getOne' => array(
      'alert_id' => array('required' => true),
    ),
    'getMultiple' => array(
      'offset' => array('required' => true, 'default' => 0),
      'limit' => array('required' => true, 'default' => LIMIT_VALUE),
      'order_by' => array('required' => true, 'default' => 'alert_name'),
      'order_dir' => array('required' => true, 'default' => 'ASC'),
      'filters' => array('required' => false)
    ),
    'setOne' => array(
      'alert' => array('required' => true),
    ),
    'deleteOne' => array(
      'alert_id' => array('required' => true),
    ),
    'enableOne' => array(
      'alert_id' => array('required' => true),
    ),
    'disableOne' => array(
      'alert_id' => array('required' => true),
    ),
    'getResultsPerPage' => array(
      'intResultsPerPage' => array('required' => true),
      'arrAllowed' => array('required' => false),
    ),
  ),

  // Email
  'Email' => array(
    'getMultiple' => array(
      'offset' => array('required' => true, 'default' => 0),
      'limit' => array('required' => true, 'default' => LIMIT_VALUE),
      'order_by' => array('required' => true, 'default' => ''),
      'order_dir' => array('required' => true, 'default' => 'ASC'),
      'filters' => array('required' => false)
    ),
    'getSummaryMultiple' => array(),
    'deleteOne' => array(
      'contact_segment_id' => array('required' => true),
    ),
    'getFolderLeaves' => array(
      'folder_id' => array('required' => true),
      'blnIsRoot' => array('required' => false),
      'order_by' => array('required' => false, 'default' => ''),
      'order_dir' => array('required' => false, 'default' => 'ASC'),
    ),
    'submitSessionContent' => array(
      'strContentSessionId' => array('required' => true),
      'strContentInstance' => array('required' => true),
      'strContent' => array('required' => true),
    ),
    'getResultsPerPage' => array(
      'intResultsPerPage' => array('required' => true),
      'arrAllowed' => array('required' => false),
    ),
  ),


  // Custom Attribute
  'CustomAttribute' => array(
    'getMultiple' => array(
      'offset' => array('required' => true, 'default' => 0),
      'limit' => array('required' => true, 'default' => LIMIT_VALUE),
      'order_by' => array('required' => true, 'default' => ''),
      'order_dir' => array('required' => true, 'default' => 'ASC'),
      'filters' => array('required' => false)
    ),
    'getByContact' => array(
      'contact_id' => array('required' => true),
    ),
    'deleteOne' => array(
      'custom_attribute_id' => array('required' => true),
    ),
    'setOne' => array(
      'custom_attribute' => array('required' => true),
    ),
    'getResultsPerPage' => array(
      'intResultsPerPage' => array('required' => true),
      'arrAllowed' => array('required' => false),
    ),
  ),

  // Contact
  'Contact' => array(
    'getMineLeadScores' => array(
      'offset' => array('required' => true, 'default' => 0),
      'limit' => array('required' => true, 'default' => LIMIT_VALUE),
      'order_by' => array('required' => true, 'default' => ''),
      'order_dir' => array('required' => true, 'default' => 'ASC'),
      'overlay_id' => array('required' => true),
      'filters' => array('required' => false)
    ),
    'getMineLeadWebActivity' => array(
      'offset' => array('required' => true, 'default' => 0),
      'limit' => array('required' => true, 'default' => LIMIT_VALUE),
      'order_by' => array('required' => true, 'default' => ''),
      'order_dir' => array('required' => true, 'default' => 'ASC'),
      'overlay_id' => array('required' => true),
      'filters' => array('required' => false)
    ),
    'getOne' => array(
      'contact_id' => array('required' => true),
    ),
    'getOneWithScore' => array(
      'contact_id' => array('required' => true),
      'overlay_id' => array('required' => true),
    ),
    'getByLeadStatus' => array(
      'lead_status_id' => array('required' => true),
      'limit' => array('required' => true, 'default' => LIMIT_VALUE),
      'offset' => array('required' => true, 'default' => 0),
    ),
    'getMailingInfo' => array(
      'contact_id' => array('required' => true),
    ),
    'getContactIdByEmailAddress' => array(
      'email_address' => array('required' => true),
    ),
    'getContactIdByMauuid' => array(
      'mauuid' => array('required' => true),
    ),
    'getResultsPerPage' => array(
      'intResultsPerPage' => array('required' => true),
      'arrAllowed' => array('required' => false),
    ),
  ),

  // Contact Activity History
  'ContactActivityHistory' => array(
    'getContactActivity' => array(
      'contact_id' => array('required' => true,),
      'offset' => array('required' => true, 'default' => 0),
      'limit' => array('required' => true, 'default' => LIMIT_VALUE),
      'order_by' => array('required' => true, 'default' => ''),
      'order_dir' => array('required' => true, 'default' => 'ASC'),
      'filters' => array('required' => false)
    ),
    'getTypes' => array(
    ),
    'getResultsPerPage' => array(
      'intResultsPerPage' => array('required' => true),
      'arrAllowed' => array('required' => false),
    ),
  ),

);