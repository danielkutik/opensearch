<?php
// $Id$

/**
 * @file
 * Page callback file for the opensearch module.
 */

/**
 * Menu callback; return an open search description feed.
 */
function opensearch_description($info) {
  // Some modules do not provide search keywords in order to get a results page
  // so double check if the current request is a search result page.
  if (_opensearch_is_search_result_page()) {
    return opensearch_view($info);
  }

  // application/opensearchdescription+xml is not standard.
  drupal_set_header('Content-Type: application/xml; charset=utf-8');

  print theme('opensearch_description', $info);
}

/**
 * Return an open search results feed.
 */
function opensearch_feed($info, $keywords, $results) {
  global $base_url;

  $namespaces = array(
    'xmlns:opensearch' => 'http://a9.com/-/spec/opensearch/1.1/',
    'xmlns:atom' => 'http://www.w3.org/2005/Atom',
    'xmlns:relevance' => 'http://a9.com/-/opensearch/extensions/relevance/1.0/',
  );

  $items = '';
  foreach ($results as $result) {
    // Merge some default values into the search result to avoid PHP notices.
    $result += array('snippet' => '');

    // Build the RSS item's properties and attributes.
    $args = array(array(
      'key' => 'guid',
      'value' => $result['link'],
      'attributes' => array(
        'isPermaLink' => 'false',
      ),
      'relevance:score' => isset($result['score']) ? (float) $result['score'] : NULL,
    ));

    // Format the the search result as an RSS item.
    $items .= format_rss_item($result['title'], $result['link'], $result['snippet'], $args);
  }

  $description = _opensearch_check_plain($info->settings['rss_description'], $info->type);
  $title = _opensearch_check_plain($info->settings['rss_title'], $info->type);

  $query = $_GET;
  unset($query['q']);

  $args = array(
    // @todo Find a better way to get the following three values.
    'opensearch:totalResults' => isset($GLOBALS['pager_total_items'][0]) ? $GLOBALS['pager_total_items'][0] : 0,
    'opensearch:startIndex' => isset($GLOBALS['pager_page_array'][0]) ? $GLOBALS['pager_page_array'][0] * 10 + 1 : 1,
    'opensearch:itemsPerPage' => 10,
    array(
      'key' => 'atom:link',
      'attributes' => array(
        'rel' => 'self',
        'href' => url('opensearch/' . $info->type . '/' . drupal_urlencode($keywords), array('query' => $query, 'absolute' => TRUE)),
        'type' => 'application/rss+xml',
      ),
    ),
    array(
      'key' => 'atom:link',
      'attributes' => array(
        'rel' => 'search',
        'href' => url('opensearch/'.  $info->type, array('absolute' => TRUE)),
        'type' => 'application/opensearchdescription+xml',
      ),
    ),
    array(
      'key' => 'atom:link',
      'attributes' => array(
        'rel' => 'alternate',
        'href' => url('search/'.  $info->type, array('absolute' => TRUE)),
        'type' => 'text/html',
      ),
    ),
    array(
      'key' => 'opensearch:Query',
      'attributes' => array('role' => 'request', 'searchTerms' => $keywords),
    ),
  );

  $output = array();
  $output[] = '<?xml version="1.0" encoding="utf-8" ?>';
  $output[] = '<rss version="2.0"' . drupal_attributes($namespaces) . '>';
  $output[] = format_rss_channel($title, $base_url, $description, $items, NULL, $args);
  $output[] = '</rss>';

  drupal_set_header('Content-Type: application/rss+xml; charset=utf-8');
  print implode("\n", $output);
}

/**
 * Menu callback; presents an opensearch results page.
 */
function opensearch_view($info) {
  global $base_url;

  if ($info->feed) {
    // Retrieve and log the search keywords.
    $keywords = _opensearch_get_search_keywords();
    watchdog('opensearch', '%keys (@type).', array('%keys' => $keywords, '@type' => module_invoke($info->type, 'search', 'name')), WATCHDOG_NOTICE, l(t('results'), 'search/' . $info->type . '/' . $keywords));

    // OpenSearch pages are 1-indexed
    // @todo Explain more why this is needed.
    if (isset($_GET['page'])) {
      $_GET['page']--;
    }

    // Collect the search results and display the feed.
    $results = module_invoke($info->type, 'search', 'search', $keywords);
    opensearch_feed($info, $keywords, $results);
  }
  else {
    // @todo Why are we not returning some kind of 404 page here instead of an
    // empty RSS feed?
    $output = array();
    $output[] = '<?xml version="1.0" encoding="utf-8" ?>';
    $output[] = '<rss version="2.0">';
    $output[] = '</rss>';

    drupal_set_header('Content-Type: application/rss+xml; charset=utf-8');
    print implode("\n", $output);
  }
}
