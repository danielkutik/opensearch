<?php
// $Id$

/**
 * @file
 * Hooks provided by the OpenSearch feed module.
 */

/**
 * @addtogroup hooks
 * @{
 */

/**
 * Allows other modules to change the OpenSearch RSS item.
 *
 * @param $result
 *   The search result, as returned from the module implementing the search
 *   hook.
 * @param $args
 *   The fourth argument passed to @code format_rss_item() @endcode.
 */
 function hook_opensearch_rss_item_alter(&$result, $&$args) {
 }

/**
 * Allows other modules to change the OpenSearch RSS channel.
 *
 * @param $namespaces
 *   The array containing the list of the namespaces used for the RSS channel.
 * @param $args
 *   The sixth argument passed to @code format_rss_item() @endcode.
 */
 function hook_opensearch_rss_channel_alter(&$namespaces, &$args) {
 }

/**
 * Allows other modules to change the default settings used by the module.
 *
 * @param $defaults
 *   The array containing the default module settings.
 */
 function hook_opensearch_default_settings_alter(&$defaults) {
 }

/**
 * @} End of "addtogroup hooks".
 */
