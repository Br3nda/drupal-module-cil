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

  $output .= '<p>'. l('Add', 'admin/settings/cil/add') .'</p>';
  
  $headers = array('name', 'directory');
  $result = pager_query("SELECT * FROM {cil_repos}". tablesort_sql($headers));
  while ($repo = db_fetch_object($result)) {
    $rows[] = array($repo->name);
  }
  if(!count($rows)) {
    $output .= '<p>'. t('No repositories configured.') .'</p>';
  }
  else {
    $output .= theme('table', $headers, $rows);
  }
  return $output;
}

function cil_admin_form($id=null) {
  $form['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Name'),
    '#required' => TRUE
  );
  $form['directory'] = array(
    '#type' => 'textfield',
    '#title' => t('Directory'),
    '#required' => TRUE
  );
  $form['add'] = array(
    '#type' => 'submit',
    '#value' => t('Add'),
  );
  return $form;
}

function cil_admin_form_validate($form, $form_state) {
}