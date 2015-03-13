<?php
/**
 * The template for displaying search forms in Flint
 *
 * @package Flint
 * @since 1.0.0
 */
?>
  <form method="get" id="searchform" class="form-inline" action="<?php echo esc_url( home_url( '/' ) ); ?>" role="search">
    <label for="s" class="screen-reader-text"><?php _ex( 'Search', 'assistive text', 'flint' ); ?></label>
    <input type="search" class="form-control" name="s" value="<?php echo esc_attr( get_search_query() ); ?>" id="s" placeholder="<?php echo esc_attr_x( 'Search &hellip;', 'placeholder', 'flint' ); ?>" />
  </form>
