<?php
/**
 * The template for displaying Archive pages
 *
 * @package Flint
 * @since 1.3.0
 */

get_header(); ?>
<?php flint_get_widgets('header'); ?>

  <section id="primary" class="content-area container">

    <div class="row">

      <?php flint_get_widgets('left'); ?>

      <div id="content" role="main" <?php flint_content_class(); ?>>

      <?php if ( have_posts() ) : ?>

        <header class="page-header">
          <h1 class="page-title">
            <?php
              /**
               * Template actions before title
               */
              if ( is_category() ) { do_action('flint_open_cat_title'); }
              elseif  ( is_tag() ) { do_action('flint_open_tag_title'); }
              elseif  ( is_tax() ) { do_action('flint_open_' . single_term_title( '', false ) . '_title'); }
              else                 { do_action('flint_open_archive_title'); }

              /**
               * Title of archive page
               */
              if ( is_category() ) { printf( __( '%s', 'flint' ), '<span>' . single_cat_title( '', false ) . '</span>' ); }
              elseif  ( is_tag() ) { printf( __( '%s', 'flint' ), '<span>' . single_tag_title( '', false ) . '</span>' ); }

              elseif ( is_author() ) {
                the_post();
                printf( __( '%s', 'flint' ), '<span class="vcard"><a class="url fn n" href="' . esc_url( get_author_posts_url( get_the_author_meta( 'ID' ) ) ) . '" title="' . esc_attr( get_the_author() ) . '" rel="me">' . get_the_author() . '</a></span>' );
                rewind_posts();
              }

              elseif ( is_day() )   { printf( __( '%s', 'flint' ), '<span>' . get_the_date()        . '</span>' ); }
              elseif ( is_month() ) { printf( __( '%s', 'flint' ), '<span>' . get_the_date( 'F Y' ) . '</span>' ); }
              elseif ( is_year() )  { printf( __( '%s', 'flint' ), '<span>' . get_the_date( 'Y' )   . '</span>' ); }

              elseif ( is_tax( 'post_format', 'post-format-aside' ) ) { _e( 'Asides', 'flint' ); }
              elseif ( is_tax( 'post_format', 'post-format-image' ) ) { _e( 'Images', 'flint' ); }
              elseif ( is_tax( 'post_format', 'post-format-video' ) ) { _e( 'Videos', 'flint' ); }
              elseif ( is_tax( 'post_format', 'post-format-quote' ) ) { _e( 'Quotes', 'flint' ); }
              elseif ( is_tax( 'post_format', 'post-format-link'  ) ) { _e( 'Links' , 'flint' ); }

              elseif ( is_tax() ) { printf( __( '%s', 'flint' ), '<span>' . single_term_title( '', false ) . '</span>' ); }

              else { _e( '<span>' . 'Archives' . '</span>', 'flint' ); }

              /**
               * Template actions after title
               */
              if ( is_category() ) { do_action('flint_close_cat_title'); }
              elseif  ( is_tag() ) { do_action('flint_close_tag_title'); }
              elseif  ( is_tax() ) { do_action('flint_close_' . single_term_title( '', false ) . '_title'); }
              else                 { do_action('flint_close_archive_title'); }
            ?>
          </h1>
          <?php
            /**
             * Term Description
             */
            if ( is_category() ) {
              $category_description = category_description();
              if ( ! empty( $category_description ) ) { echo apply_filters( 'category_archive_meta', '<div class="taxonomy-description">' . $category_description . '</div>' ); }
            }
            elseif ( is_tag() ) {
              $tag_description = tag_description();
              if ( ! empty( $tag_description ) ) { echo apply_filters( 'tag_archive_meta', '<div class="taxonomy-description">' . $tag_description . '</div>' ); }
            }
            elseif ( is_tax( 'post_format' ) ) {}
            elseif ( is_tax() ) {
              $term_description = term_description();
              if ( ! empty( $term_description ) ) { echo apply_filters( 'tag_archive_meta', '<p class="taxonomy-description">' . $term_description . '</p>' ); }
            }
          ?>
        </header><!-- .page-header -->

        <?php while ( have_posts() ) : the_post(); ?>

          <?php get_template_part( 'format', get_post_format() ); ?>

        <?php endwhile; ?>

        <?php flint_content_nav( 'nav-below' ); ?>

      <?php else : ?>

        <?php get_template_part( 'no-results', 'archive' ); ?>

      <?php endif; ?>

      </div><!-- #content -->

      <?php flint_get_widgets('right'); ?>

    </div><!-- .row -->

  </section><!-- #primary -->

<?php flint_get_widgets('footer'); ?>
<?php get_footer(); ?>

