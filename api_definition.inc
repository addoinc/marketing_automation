<?php

/**
 * @file
 * This file contains entire API definition with its parameter details.
 */

if (!defined('LIMIT_VALUE')) {
  define('LIMIT_VALUE', 50);
}


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
      'order_by' => array('required' => true, 'default' => 'custom_attribute'),
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
    'submitContactImport' => array(
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

  // Contact Segment
  'ContactSegment' => array(
    'getMultiple' => array(
      'offset' => array('required' => true, 'default' => 0),
      'limit' => array('required' => true, 'default' => LIMIT_VALUE),
      'order_by' => array('required' => true, 'default' => 'contact_segment_name'),
      'order_dir' => array('required' => true, 'default' => 'ASC'),
      'filters' => array('required' => false)
    ),
    'getSummaryMultiple' => array(
    ),
    'deleteOne' => array(
      'contact_segment_id' => array('required' => true),
    ),
    'setDefault' => array(
      'contact_segment_id' => array('required' => true),
    ),
    'getContactIds' => array(
      'contact_segment_id' => array('required' => true),
      'offset' => array('required' => true, 'default' => 0),
      'limit' => array('required' => true, 'default' => LIMIT_VALUE),
      'start_date' => array('required' => true),
      'stop_date' => array('required' => true),
    ),
    'getContactParticipation' => array(
      'contact_segment_id' => array('required' => true),
      'contact_id' => array('required' => true),
      'start_date' => array('required' => true),
      'stop_date' => array('required' => true),
    ),
    'getFolderLeaves' => array(
      'folder_id' => array('required' => true),
      'blnIsRoot' => array('required' => false),
      'order_by' => array('required' => false, 'default' => ''),
      'order_dir' => array('required' => false, 'default' => 'ASC'),
    ),
    'getResultsPerPage' => array(
      'intResultsPerPage' => array('required' => true),
      'arrAllowed' => array('required' => false),
    ),
  ),

  // Visit
  'Visit' => array(
    'getMineMultiple' => array(
      'offset' => array('required' => true, 'default' => 0),
      'limit' => array('required' => true, 'default' => LIMIT_VALUE),
      'order_by' => array('required' => true, 'default' => ''),
      'order_dir' => array('required' => true, 'default' => 'ASC'),
      'overlay_id' => array('required' => true),
      'domain_group_id' => array('required' => true),
      'start_date' => array('required' => true),
      'stop_date' => array('required' => true),
      'filters' => array('required' => false)
    ),
    'getAnonymousMultiple' => array(
      'offset' => array('required' => true, 'default' => 0),
      'limit' => array('required' => true, 'default' => LIMIT_VALUE),
      'order_by' => array('required' => true, 'default' => ''),
      'order_dir' => array('required' => true, 'default' => 'ASC'),
      'overlay_id' => array('required' => true),
      'domain_group_id' => array('required' => true),
      'start_date' => array('required' => true),
      'stop_date' => array('required' => true),
      'filters' => array('required' => false)
    ),
    'getAllMultiple' => array(
      'offset' => array('required' => true, 'default' => 0),
      'limit' => array('required' => true, 'default' => LIMIT_VALUE),
      'order_by' => array('required' => true, 'default' => ''),
      'order_dir' => array('required' => true, 'default' => 'ASC'),
      'contact_segment_id' => array('required' => true),
      'start_date' => array('required' => true),
      'stop_date' => array('required' => true),
      'filters' => array('required' => false)
    ),
    'getUnsegmentedContactDetail' => array(
      'contact_id' => array('required' => true),
      'domain_group_id' => array('required' => true),
      'start_date' => array('required' => true),
      'stop_date' => array('required' => true),
    ),
    'getContactDetail' => array(
      'contact_id' => array('required' => true),
      'contact_segment_id' => array('required' => true),
      'start_date' => array('required' => true),
      'stop_date' => array('required' => true),
    ),
    'getFirstVisit' => array(
      'contact_id' => array('required' => true),
      'contact_segment_id' => array('required' => true),
    ),
    'getResultsPerPage' => array(
      'intResultsPerPage' => array('required' => true),
      'arrAllowed' => array('required' => false),
    ),
  ),

  // Folder Email List
  'FolderEmailList' => array(
    'getMultiple' => array(
    ),
    'deleteOne' => array(
      'folder_id' => array('required' => true),
    ),
    'getFolderTree' => array(
    ),
    'getResultsPerPage' => array(
      'intResultsPerPage' => array('required' => true),
      'arrAllowed' => array('required' => false),
    ),
  ),

  // Report
  'Report' => array(
    'getMultiple' => array(
      'offset' => array('required' => true, 'default' => 0),
      'limit' => array('required' => true, 'default' => LIMIT_VALUE),
      'order_by' => array('required' => true, 'default' => 'report_name'),
      'order_dir' => array('required' => true, 'default' => 'ASC'),
      'filters' => array('required' => false)
    ),
    'getOne' => array(
      'report_id' => array('required' => true),
    ),
    'setOne' => array(
      'report' => array('required' => true),
    ),
    'deleteOne' => array(
      'report_id' => array('required' => true),
    ),
    'enableOne' => array(
      'report_id' => array('required' => true),
    ),
    'disableOne' => array(
      'report_id' => array('required' => true),
    ),
    'getResultsPerPage' => array(
      'intResultsPerPage' => array('required' => true),
      'arrAllowed' => array('required' => false),
    ),
  ),

  // User
  'User' => array(
    'getSessionId' => array(
      'username' => array('required' => true),
      'password' => array('required' => true),
    ),
    'isDefaultContactSegmentId' => array(
      'contact_segment_id' => array('required' => true),
    ),
    'setOne' => array(
      'user' => array('required' => true),
    ),
    'getOneByEmail' => array(
      'email' => array('required' => true),
    ),
    'getResultsPerPage' => array(
      'intResultsPerPage' => array('required' => true),
      'arrAllowed' => array('required' => false),
    ),
  ),

  // Lead Score Overlay
  'LeadScoreOverlay' => array(
    'getMultiple' => array(
      'offset' => array('required' => true, 'default' => 0),
      'limit' => array('required' => true, 'default' => LIMIT_VALUE),
      'order_by' => array('required' => true, 'default' => ''),
      'order_dir' => array('required' => true, 'default' => 'ASC'),
      'filters' => array('required' => false)
    ),
    'getOne' => array(
      'lead_score_overlay_id' => array('required' => true),
    ),
    'getDefault' => array(
    ),
    'getAll' => array(
    ),
    'getResultsPerPage' => array(
      'intResultsPerPage' => array('required' => true),
      'arrAllowed' => array('required' => false),
    ),
  ),

  // Lead Status
  'LeadStatus' => array(
    'getMultiple' => array(
      'offset' => array('required' => true, 'default' => 0),
      'limit' => array('required' => true, 'default' => LIMIT_VALUE),
      'order_by' => array('required' => true, 'default' => ''),
      'order_dir' => array('required' => true, 'default' => 'ASC'),
      'filters' => array('required' => false)
    ),
    'deleteOne' => array(
      'lead_status_id' => array('required' => true),
    ),
    'getResultsPerPage' => array(
      'intResultsPerPage' => array('required' => true),
      'arrAllowed' => array('required' => false),
    ),
  ),

  // Domain Group
  'DomainGroup' => array(
    'getAll' => array(
    ),
    'getResultsPerPage' => array(
       'intResultsPerPage' => array('required' => true, 'default' => LIMIT_VALUE),
       'arrAllowed' => array('required' => true),
    ),
  ),
);