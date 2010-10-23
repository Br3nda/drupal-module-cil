<?php
/**
 * @file configure this module
 */
 
/**
 * menu callback page for configuring this module
 */
function cil_admin_page($op='view', $id=null) {

  switch($op) {
    case 'view': return cil_admin_view();
    break;
    case 'add' : return drupal_get_form('cil_admin_form');
    break;
    case 'edit': return drupal_get_form('cil_admin_form', $id);
    break;
    
  }
}
function cil_admin_view() {
  $output = '';

  $output .= l('Add', 'admin/settings/cil/add');
  
  $headers = array('name', 'directory');
  $result = pager_query("SELECT * FROM {cil_repos}". tablesort_sql($headers));
  while ($repo = db_fetch_object($result)) {
    $rows[] = array($repo->name);
  }
  if(!count($rows)) {
    $output .= t('No repositories configured');
  }
  else {
    $output .= theme('table', $headers, $rows);
  }
  return $output;
}

function cil_admin_form($id) {
  $form['name'] = array(
  );
  return $form;
}