<?php
/**
 * Displays content for the single posts
 *
 * @package Flint
 * @since 1.3.0
 */
?>

  <div class="col-xs-12 col-sm-2">
    <?php if (is_singular()) { flint_post_thumbnail(); } else { flint_post_thumbnail( 'post', 'archive' ); } ?>
  </div>

  <article id="post-<?php the_ID(); ?>" <?php post_class('col-xs-12 col-sm-8'); ?>>
    <header class="entry-header">
      <?php $type = get_post_type(); ?>
      <?php do_action('flint_open_entry_header_'.$type); ?>

      <h1 class="entry-title"><?php the_title(); ?></h1>

      <div class="entry-meta">
        <?php do_action('flint_entry_meta_above_'.$type); ?>
      </div><!-- .entry-meta -->

      <?php do_action('flint_close_entry_header_'.$type); ?>

    </header><!-- .entry-header -->

    <div class="entry-content">
      <?php the_content(); ?>
      <?php
        flint_link_pages( array(
          'before' => '<ul class="pagination">',
          'after'  => '</ul>',
        ) );
      ?>
    </div><!-- .entry-content -->

    <footer class="entry-meta clearfix">
      <?php do_action('flint_entry_meta_below_'.$type); ?>
    </footer><!-- .entry-meta -->
  </article><!-- #post-<?php the_ID(); ?> -->

  <div class="hidden-xs col-sm-2"></div>
