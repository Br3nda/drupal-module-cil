<?php
/**
 * @file configure this module
 */
 
/**
 * menu callback page for configuring this module
 */
function cil_admin_page() {
  $result = db_query("SELECT * FROM {cil_repos}");
  while ($repo = db_fetch_object($result)) {
    $rows[] = array($repo->name);
  }
  return theme('table', $headers, $rows);
}
