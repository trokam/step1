<?php
/**
 * The template for displaying 404 pages (Not Found).
 *
 * @package Flint
 * @since 1.3.3
 */

get_header(); ?>

  <div id="primary" class="content-area container">
    <div id="content" class="site-content" role="main">
      <div class="row">
        <div class="hidden-xs col-sm-2 col-md-2"></div>
        <article id="post-0" class="post error404 not-found col-xs-12 col-sm-8 col-md-8">
          <header class="entry-header">
            <?php do_action('flint_open_entry_header_404'); ?>
            <h1 class="entry-title"><?php _e( 'Are we missing something?', 'flint' ); ?></h1>
            <?php do_action('flint_close_entry_header_404'); ?>
          </header><!-- .entry-header -->

          <?php if ( is_search() ) : ?>
          <div class="entry-summary">
            <?php the_excerpt(); ?>
          </div><!-- .entry-summary -->
          <?php else : ?>
          <div class="entry-content">
            <p><?php _e( 'It looks like nothing was found at this location. Maybe try one of the links below or a search?', 'flint' ); ?></p>

            <?php get_search_form(); ?>

            <?php the_widget( 'WP_Widget_Recent_Posts' ); ?>

            <?php if ( flint_categorized_blog() ) : // Only show the widget if site has multiple categories. ?>
            <div class="widget widget_categories">
              <h2 class="widgettitle"><?php _e( 'Most Used Categories', 'flint' ); ?></h2>
              <ul>
              <?php
                wp_list_categories( array(
                  'orderby'    => 'count',
                  'order'      => 'DESC',
                  'show_count' => 1,
                  'title_li'   => '',
                  'number'     => 10,
                ) );
              ?>
              </ul>
            </div><!-- .widget -->
            <?php endif; ?>

            <?php
            /* translators: %1$s: smiley */
            $archive_content = '<p>' . sprintf( __( 'Try looking in the monthly archives. %1$s', 'flint' ), convert_smilies( ':)' ) ) . '</p>';
            the_widget( 'WP_Widget_Archives', 'dropdown=1', "after_title=</h2>$archive_content" );
            ?>

            <?php the_widget( 'WP_Widget_Tag_Cloud' ); ?>

          </div><!-- .entry-content -->
          <?php endif; ?>

          <footer class="entry-meta clearfix">
            <?php if ( ! post_password_required() && ( comments_open() || '0' != get_comments_number() ) ) : ?>
              <span class="sep"> | </span>
              <span class="comments-link"><?php comments_popup_link( __( 'Leave a comment', 'flint' ), __( '1 Comment', 'flint' ), __( '% Comments', 'flint' ) ); ?></span>
            <?php endif; ?>
          </footer><!-- .entry-meta -->
        </article><!-- #page-<?php the_ID(); ?> -->
        <div class="hidden-xs col-sm-2 col-md-2"></div>
      </div><!-- .row -->
    </div><!-- #content -->
  </div><!-- #primary -->
</div><!-- #page -->

<?php get_footer(); ?>
