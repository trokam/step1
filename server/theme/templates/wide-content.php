<?php
/**
 * Displays content for the "Wide" template.
 *
 * @package Flint
 * @since 1.3.0
 */
?>

  <div class="row">
    <article id="post-<?php the_ID(); ?>" <?php post_class('col-xs-12'); ?>>
      <header class="entry-header">
        <?php $type = get_post_type(); ?>
        <?php do_action('flint_open_entry_header_'.$type); ?>

        <h1 class="entry-title"><?php if (is_singular()) { echo the_title(); } else { echo '<a href="' . get_permalink() .'" rel="bookmark">' . get_the_title() . '</a>'; } ?></h1>
        <?php if ( current_user_can('edit_posts') ) { ?><a class="btn btn-default btn-sm btn-edit hidden-xs" href="<?php echo get_edit_post_link(); ?>">Edit</a><?php } ?>

        <div class="entry-meta">
          <?php do_action('flint_entry_meta_above_'.$type); ?>
        </div><!-- .entry-meta -->

        <?php do_action('flint_close_entry_header_'.$type); ?>

      </header><!-- .entry-header -->

      <?php if ( is_search() ) : ?>
      <div class="entry-summary">
        <?php the_excerpt(); ?>
      </div><!-- .entry-summary -->
      <?php else : ?>
      <div class="entry-content">
        <?php flint_the_content(); ?>
        <?php
        flint_link_pages( array(
          'before' => '<ul class="pagination">',
          'after'  => '</ul>',
        ) ); ?>
      </div><!-- .entry-content -->
      <?php endif; ?>
    </article><!-- #page-<?php the_ID(); ?> -->

  </div><!-- .row -->
