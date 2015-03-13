<?php
/**
 * Template Name: Minimal
 *
 * @package Flint
 * @since 1.3.3
 */
$options = flint_get_options();
get_header('head');
if (empty($options['minimal_nav']) || $options['minimal_nav'] == 'navbar'){ get_header('nav'); } ?>
<?php flint_get_widgets('header', true); ?>

  <div id="primary" class="content-area container">

    <div class="row">

      <?php flint_get_widgets('left', true); ?>

      <div id="content" class="site-content<?php if ( flint_is_active_widgets( 'left' ) | flint_is_active_widgets( 'right' ) ) { echo ' col-xs-12 col-md-9'; } ?>" role="main">

        <?php while ( have_posts() ) : the_post(); ?>

          <?php flint_breadcrumbs('minimal'); ?>

          <?php get_template_part( 'templates/' . flint_get_template(), 'content' ); ?>

          <?php if ( comments_open() || '0' != get_comments_number() ) { comments_template(); } ?>

        <?php endwhile; ?>

      </div><!-- #content -->

      <?php flint_get_widgets('right', true); ?>

    </div><!-- .row -->

  </div><!-- #primary -->

</div><!-- #page -->

<?php flint_get_widgets('footer', true); ?>
<?php get_footer('close'); ?>
