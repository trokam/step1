<?php
/**
 * The Header for our theme.
 *
 * Displays all of the <head> section and everything up till <header>
 *
 * @package Flint
 * @since 1.3.3
 */
?>
<!DOCTYPE html>
<!--[if lt IE 9]><html <?php language_attributes(); ?> class="ie"><![endif]-->
<!--[if gte IE 9]><!--><html <?php language_attributes(); ?>><!--<![endif]-->
<head>
  <meta charset="<?php bloginfo( 'charset' ); ?>" />
  <meta http-equiv="X-UA-Compatible" content="IE=edge,chrome=1"/>
  <meta name="viewport" content="width=device-width, initial-scale=1" />
  <link rel="profile" href="http://gmpg.org/xfn/11" />
  <link rel="pingback" href="<?php bloginfo( 'pingback_url' ); ?>" />
  <?php wp_head(); ?>
  <?php flint_options_css(); ?>
</head>
<body <?php flint_body_class(); ?>>
  <?php do_action('flint_open'); ?>
  <div id="page" class="hfeed site">
    <?php do_action( 'before' ); ?>
