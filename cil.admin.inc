<?php
/**
 * @file configure this module
 */
 
/**
 * menu callback page for configuring this module
 */
function cil_admin_page($op='view') {

  switch($op) {
    case 'view': return cil_admin_view();
    break;
  }
}
function cil_admin_view() {
  $headers = array('name', 'directory');
  $result = pager_query("SELECT * FROM {cil_repos}". tablesort_sql($headers));
  while ($repo = db_fetch_object($result)) {
    $rows[] = array($repo->name);
  }
  return theme('table', $headers, $rows);
}
