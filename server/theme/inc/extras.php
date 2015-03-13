<?php
/**
 * Custom functions that act independently of the theme templates
 *
 * Eventually, some of the functionality here could be replaced by core features
 *
 * @package Flint
 * @since 1.3.0
 */

/**
 * Get our wp_nav_menu() fallback, wp_page_menu(), to show a home link.
 */
function flint_page_menu_args( $args ) {
  $args['show_home'] = true;
  return $args;
}
add_filter( 'wp_page_menu_args', 'flint_page_menu_args' );

/**
 * Adds a class of group-blog to blogs with more than 1 published author
 */
function flint_body_class_multi_author( $classes ) {
  if ( is_multi_author() ) { $classes[] = 'group-blog'; }
  return $classes;
}
add_filter( 'body_class', 'flint_body_class_multi_author' );

/**
 * Filter in a link to a content ID attribute for the next/previous image links on image attachment pages
 */
function flint_attachment_link( $url, $id ) {
  if ( ! is_attachment() && ! wp_attachment_is_image( $id ) )
    return $url;

  $image = get_post( $id );
  if ( ! empty( $image->post_parent ) && $image->post_parent != $id )
    $url .= '#main';

  return $url;
}
add_filter( 'attachment_link', 'flint_attachment_link', 10, 2 );
