<?php
/**
 * @package Flint
 * @since 1.3.0
 */
?>

  <div class="row">
    <article id="post-<?php the_ID(); ?>" <?php post_class('col-xs-12'); ?>>
      <div class="entry-content">
        <h4><?php flint_the_content(); ?></h4>
        <?php if ( current_user_can('edit_posts') ) { ?><a class="btn btn-default btn-sm btn-edit hidden-xs" href="<?php echo get_edit_post_link(); ?>">Edit Status</a><?php } ?>
      </div><!-- .entry-content -->

      <footer class="entry-meta clearfix">
        <?php flint_posted_on(); ?>
        <span class="sep"> | </span>
        <?php do_action('flint_entry_meta_below_post'); ?>
      </footer><!-- .entry-meta -->
    </article><!-- #post-<?php the_ID(); ?> -->
  </div><!-- .row -->
