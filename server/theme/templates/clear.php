<?php
/**
 * Template Name: Clear
 *
 * @package Flint
 * @since 1.3.3
 */
$options = flint_get_options();
get_header('head');
if ($options['clear_nav'] == 'navbar'){ get_header('nav'); } ?>

  <div id="primary" class="content-area container">
    <div class="row">
      <div id="content" class="site-content" role="main">

        <?php while ( have_posts() ) : the_post(); ?>

          <?php flint_breadcrumbs('clear'); ?>

          <?php get_template_part( 'templates/' . flint_get_template(), 'content' ); ?>

          <?php if ( comments_open() || '0' != get_comments_number() ) { comments_template(); } ?>

        <?php endwhile; ?>

      </div><!-- #content -->
    </div><!-- .row -->
  </div><!-- #primary -->
</div><!-- #page -->

<?php get_footer('close'); ?>
