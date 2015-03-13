<?php
/**
 * Link Post Format Template
 *
 * The template for displaying the post content for link posts
 *
 * @package Flint
 * @since 1.3.0
 */
?>

  <div class="row">
    <?php flint_get_spacer('left'); ?>
    <article id="post-<?php the_ID(); ?>" <?php flint_post_class(); ?>>
      <div class="entry-content">
        <h3><?php flint_the_content(); ?></h3>
        <?php if ( current_user_can('edit_posts') ) { ?><a class="btn btn-default btn-sm btn-edit hidden-xs" href="<?php echo get_edit_post_link(); ?>">Edit Link</a><?php } ?>
      </div><!-- .entry-content -->

      <footer class="entry-meta clearfix">
        <?php flint_posted_on(); ?>
        <span class="sep"> | </span>
        <?php do_action('flint_entry_meta_below_post'); ?>
      </footer><!-- .entry-meta -->
    </article><!-- #post-<?php the_ID(); ?> -->
    <?php flint_get_spacer('right'); ?>
  </div><!-- .row -->
