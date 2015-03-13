<?php
/**
 * The default page template
 *
 * @package Flint
 * @since 1.3.3
 */

get_header(); ?>
<?php flint_get_widgets('header'); ?>

  <div id="primary" class="content-area container">

    <div class="row">

      <?php flint_get_widgets('left'); ?>

      <div id="content" role="main" <?php flint_content_class(); ?>>

        <?php while ( have_posts() ) : the_post(); ?>

          <?php
            if ( is_active_sidebar( 'left' ) | is_active_sidebar( 'right' ) ) {
              get_template_part( 'templates/wide', 'content' );
            }
            else {
              get_template_part( 'templates/' . flint_get_template(), 'content' );
            }
          ?>

          <?php if ( comments_open() || '0' != get_comments_number() ) { comments_template(); } ?>

        <?php endwhile; ?>

      </div><!-- #content -->

      <?php flint_get_widgets('right'); ?>

    </div><!-- .row -->

  </div><!-- #primary -->

</div><!-- #page -->

<?php flint_get_widgets('footer'); ?>
<?php get_footer(); ?>
