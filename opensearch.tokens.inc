<?php

/**
 * @file
 * Implements search tokens that can be used from third-party modules
 * or from opensearch.module.
 */

/**
 * Implements opensearch_token_info().
 */
function opensearch_token_info() {
  $type = array(
    'name' => t('Search'),
    'description' => t('Tokens related to search modules.'),
    'needs-data' => 'search',
  );

  $search = array();

  $search['keywords'] = array(
    'name' => t("Keywords"),
    'description' => t("The keywords of the search request."),
  );
  $search['module'] = array(
    'name' => t("Module name"),
    'description' => t("The module handling the search data."),
  );
  $search['module-full'] = array(
    'name' => t("Full module name"),
    'description' => t("The name of the module handling the search data, complete of extension."),
  );
  $search['name'] = array(
    'name' => t("Search title"),
    'description' => t("The title of the search module."),
  );
  $search['name-lowercase'] = array(
    'name' => t("Lower case search title"),
    'description' => t("The title of the search module, in lower case characters."),
  );
  $search['opensearch-url'] = array(
    'name' => t("Opensearch URL"),
    'description' => t("The OpenSearch URL of the search page."),
  );
  $search['url'] = array(
    'name' => t("Search page URL"),
    'description' => t("The search page URL."),
  );
  $search['url-relative'] = array(
    'name' => t("Relative search page URL"),
    'description' => t("The relative search page URL."),
  );

  return array(
    'types' => array('search' => $type),
    'tokens' => array('search' => $search),
  );
}

/**
 * Implements hook_tokens().
 */
function opensearch_tokens($type, $tokens, array $data = array(), array $options = array()) {
  $info = search_get_info();
  $replacements = array();
  $sanitize = !empty($options['sanitize']);
  $url_options = array();

  if (isset($options['language'])) {
    $url_options['language'] = $options['language'];
  }


  if ($type == 'search' && !empty($data['search']) && isset($info[$data['search']])) {
    $search = $data['search'];

    foreach ($tokens as $name => $original) {
      switch ($name) {
        case 'keywords':
          $keywords = trim(opensearch_search_get_keys());
          $replacements[$original] = $sanitize ? check_plain($keywords) : trim($keywords);
          break;

        case 'module':
          $replacements[$original] = $search;
          break;

        case 'module-full':
          $replacements[$original] = "$search.module";
          break;

        case 'name':
          $replacements[$original] = $info[$search]['title'];
          break;

        case 'name-lowercase':
          $replacements[$original] = drupal_strtolower($info[$search]['title']);
          break;

        case 'opensearch-url':
          $replacements[$original] = url('opensearch/' . $info[$search]['path'], $url_options);
          break;

        case 'url':
          $replacements[$original] = url('search/' . $info[$search]['path'], $url_options + array('absolute' => TRUE));
          break;

        case 'url-relative':
          $replacements[$original] = url('search/' . $info[$search]['path'], $url_options);
          break;
      }
    }
  }

  return $replacements;
}
