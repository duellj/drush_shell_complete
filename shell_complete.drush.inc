<?php
// $Id$

/**
 * Implementation of hook_drush_command().
 */
function shell_complete_drush_command() {
  $items['shell-complete'] = array(
    'description' => 'List commands for shell completion',
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH,
    'argument' => array(
      'command' => 'List command specific arguments and options',
    ),
    'hidden' => TRUE,
  );

  return $items;
}

/**
 * Implementation of hook_drush_help().
 */
function shell_complete_drush_help($section) {
  switch ($section) {
    case 'drush:shell-complete':
      return dt("List commands for shell completion.");
  }
}

/**
 * Drush callback; list available commands for shell completion.
 */
function drush_shell_complete($command = FALSE) {
  $commands = drush_get_commands();
  if (empty($command)) {
    ksort($commands);
    foreach($commands as $key => $command) {
      if (!$command['hidden'] && !in_array($key, $command['deprecated-aliases'])) {
        $rows[] = $key . ':' . str_replace(':', '\:', $command['description']);
      }
    }
  }
  else {
    if (array_key_exists($command, $commands)) {
      $command = $commands[$command];
      foreach ($command['arguments'] as $key => $description) {
        $rows[] = $key . ':' . str_replace(':', '\:', $description;
      }
    }
  }
  print join("\n", $rows) . "\n";
  return;
}
