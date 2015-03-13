<?php
/**
 * Gallery Post Format Template
 *
 * The template for displaying the post content for gallery posts
 *
 * @package Flint
 * @since 1.3.0
 */
?>

  <div class="row">
    <?php flint_get_spacer('left'); ?>
    <article id="post-<?php the_ID(); ?>" <?php flint_post_class(); ?>>
      <header class="entry-header">
        <h1 class="entry-title"><?php if (is_single()) { echo the_title(); } else { echo '<a href="' . get_permalink() .'" rel="bookmark">' . get_the_title() . '</a>'; } ?></h1>
        <?php if ( current_user_can('edit_posts') ) { ?><a class="btn btn-default btn-sm btn-edit hidden-xs" href="<?php echo get_edit_post_link(); ?>">Edit Gallery</a><?php } ?>
        <?php if (is_single()) {} else { ?><a class="btn btn-info btn-block visible-xs-block" href="<?php echo get_permalink(); ?>">View gallery</a><?php } ?>
        <div class="entry-meta">
          <?php do_action('flint_entry_meta_above_post'); ?>
        </div><!-- .entry-meta -->
      </header><!-- .entry-header -->

      <?php if ( is_search() ) : ?>
      <div class="entry-summary">
        <?php the_excerpt(); ?>
      </div><!-- .entry-summary -->
      <?php else : ?>
      <div class="entry-content">
        <?php if (is_single()) { flint_the_content(); }
        else {
          $pattern = get_shortcode_regex();
          preg_match( "/$pattern/s", get_the_content(), $match );
          $atts   = isset( $match[3] ) ? shortcode_parse_atts( $match[3] ) : array();
          $images = isset( $atts['ids'] ) ? explode( ',', $atts['ids'] ) : false;

          if ( ! $images ) {
            $images = get_posts( array(
            'post_parent'      => get_the_ID(),
            'fields'           => 'ids',
            'post_type'        => 'attachment',
            'post_mime_type'   => 'image',
            'orderby'          => 'menu_order',
            'order'            => 'ASC',
            'numberposts'      => 999,
            'suppress_filters' => false
            ) );
          }

          if ( $images ) {
            $total_images = count( $images );
            $image        = array_shift( $images ); ?>

            <p><a class="gallery-thumb hidden-xs" href="<?php the_permalink(); ?>"><?php echo wp_get_attachment_image( $image, 'large' ); ?></a></p>

            <p class="gallery-info">
              <?php
              printf( _n( 'This gallery contains <a %1$s>%2$s photo</a>.', 'This gallery contains <a %1$s>%2$s photos</a>.', $total_images, 'flint' ),
              'href="' . get_permalink() . '" title="' . esc_attr( sprintf( __( 'Permalink to %s', 'flint' ), the_title_attribute( 'echo=0' ) ) ) . '" rel="bookmark"',
              number_format_i18n( $total_images )
              ); ?>
            </p>

            <?php the_excerpt(); ?>

          <?php } // if ( $images )
        } //not single ?>
        <?php
        flint_link_pages( array(
          'before' => '<ul class="pagination">',
          'after'  => '</ul>',
        ) ); ?>
      </div><!-- .entry-content -->
      <?php endif; ?>
      <footer class="entry-meta clearfix">
        <?php do_action('flint_entry_meta_below_post'); ?>
      </footer><!-- .entry-meta -->
    </article><!-- #page-<?php the_ID(); ?> -->
    <?php flint_get_spacer('right'); ?>
  </div><!-- .row -->
