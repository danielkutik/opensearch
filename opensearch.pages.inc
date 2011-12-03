<?php

/**
 * @file
 * Page callback file for the OpenSearch feed module.
 */

/**
 * Returns an open search description file.
 *
 * @param $os
 *   An object of the class OpenSearch.
 *
 * @return
 *   The XML content for the Opensearch description file.
 */
function opensearch_description($os) {
  // application/opensearchdescription+xml is not standard.
  drupal_set_header('Content-Type: application/xml; charset=utf-8');

  print theme('opensearch_description', array('opensearch' => $os));
}

/**
 * Presents an OpenSearch results page.
 *
 * @param $os
 *   An instance of the class OpenSearch.
 * @return
 *   The XML content for the Opensearch feed, or the error page 404.
 */
function opensearch_view($os) {
  if ($os['feed']) {
    // Retrieve and log the search keywords.
    $keywords = trim(search_get_keys());
    $os->watchdog($keywords);

    // OpenSearch pages are 1-indexed.
    if (isset($_GET['page'])) {
      $_GET['page']--;
    }

    $os->feed($keywords);
  }
  else {
    drupal_not_found();
  }
}
