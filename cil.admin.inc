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
    case 'sync': return cil_admin_sync($id);
    break;
  }
}

function cil_admin_sync($id) {
  return '';
}

function cil_admin_view() {
  $output = '';

  $output .= '<p>'. l('Add', 'admin/settings/cil/add') .'</p>';
  
  $headers = array('name', 'directory');
  $result = pager_query("SELECT * FROM {cil_repos}". tablesort_sql($headers));
  while ($repo = db_fetch_object($result)) {
    $rows[] = array(
      check_plain($repo->name),
      check_plain($repo->directory),
      l('Edit', 'admin/settings/cil/edit/'. $repo->cil_repo_id),
      l('Sync', 'admin/settings/cil/sync/'. $repo->cil_repo_id),
      l('Delete', 'admin/settings/cil/edit/'. $repo->cil_repo_id),
    );
  }
  if(!count($rows)) {
    $output .= '<p>'. t('No repositories configured.') .'</p>';
  }
  else {
    $output .= theme('table', $headers, $rows);
  }
  return $output;
}

function cil_admin_form($a, $id=null) {
  $repo = cil_get($id);
  $form['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Name'),
    '#required' => TRUE,
    '#default_value' => isset($repo->name) ? $repo->name : '',
  );
  $form['directory'] = array(
    '#type' => 'textfield',
    '#title' => t('Directory'),
    '#required' => TRUE,
    '#default_value' => isset($repo->directory) ? $repo->directory : '',
  );
  if($id) {
    $form['id'] = array(
      '#type' => 'hidden',
      '#value' => $id,
    );
    $form['add'] = array(
      '#type' => 'submit',
      '#value' => t('Save'),
      '#weight' => 10,
    );    
  }
  else {
    $form['add'] = array(
      '#type' => 'submit',
      '#value' => t('Add'),
    );
  }
  return $form;
}

function cil_admin_form_validate($form, $form_state) {
}

function cil_admin_form_submit($form, $form_state) {
  $repo->name = $form_state['values']['name'];
  $repo->directory = $form_state['values']['directory'];
  if(isset($form_state['values']['id'])) {
    $repo->cil_repo_id = $form_state['values']['id'];
    drupal_write_record('cil_repos', $repo, array('cil_repo_id'));
  }
  else {
    drupal_write_record('cil_repos', $repo);
  }
  drupal_goto('admin/settings/cil');
}