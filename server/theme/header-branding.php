<?php
/**
 * The Header for our theme.
 *
 * Displays the branding header element
 *
 * @package Flint
 * @since 1.3.0
 */
?>

  <div id="masthead" class="fill site-header" role="banner">
    <?php if (current_theme_supports('custom-header')) { ?>
      <div class="container hidden-xs">
        <div class="row">
          <?php $header_image = get_header_image();
          if ( ! empty( $header_image ) ) { ?>
            <a href="<?php echo esc_url( home_url( '/' ) ); ?>" title="<?php echo esc_attr( get_bloginfo( 'name', 'display' ) ); ?>" rel="home" <?php if ( display_header_text() ) { ?> class="hidden-xs hidden-sm col-md-2"<?php } ?>>
              <img src="<?php header_image(); ?>" width="<?php echo get_custom_header()->width; ?>" height="<?php echo get_custom_header()->height; ?>" alt="" />
            </a>
          <?php } /* if ( ! empty( $header_image ) ) */
          if ( display_header_text() ) { ?>
            <div class="site-branding <?php if ( ! empty( $header_image ) ) { ?>hidden-xs col-sm-12 col-md-10<?php } ?>">
              <h1 class="site-title hidden-xs"><a href="<?php echo esc_url( home_url( '/' ) ); ?>" title="<?php echo esc_attr( get_bloginfo( 'name', 'display' ) ); ?>" rel="home"><?php bloginfo( 'name' ); ?></a></h1>
              <h2 class="site-description hidden-xs"><?php bloginfo( 'description' ); ?></h2>
            </div><!-- .site-branding -->
          <?php } /* if ( display_header_text() ) */ ?>
        </div><!-- .row -->
      </div><!-- .container -->
    <?php } /* if (current_theme_supports('custom-header')) */ ?>
  </div><!-- #masthead -->
