<?php
/**
 * The template for displaying Comments
 *
 * @package Flint
 * @since 1.3.0
 */

if ( post_password_required() )
  return;
?>
<div class="row">
  <?php flint_get_template('margins'); ?>
  <div id="comments" class="comments-area <?php flint_get_template('content'); ?>">

    <?php if ( have_comments() ) : ?>
      <h2 class="comments-title">
        <?php
          printf( _nx( 'One thought on &ldquo;%2$s&rdquo;', '%1$s thoughts on &ldquo;%2$s&rdquo;', get_comments_number(), 'comments title', 'flint' ),
            number_format_i18n( get_comments_number() ), '<span>' . get_the_title() . '</span>' );
        ?>
      </h2>

      <?php if ( get_comment_pages_count() > 1 && get_option( 'page_comments' ) ) : ?>
      <ul class="pager comments-nav-above">
        <li class="previous"><?php previous_comments_link( __( 'Older Comments', 'flint' ) ); ?></li>
        <li class="next"><?php next_comments_link( __( 'Newer Comments', 'flint' ) ); ?></li>
      </ul><!-- .pager -->
      <?php endif; // check for comment navigation ?>

      <ol class="comment-list">
        <?php wp_list_comments( array( 'callback' => 'flint_comment' ) ); ?>
      </ol><!-- .comment-list -->

      <?php if ( get_comment_pages_count() > 1 && get_option( 'page_comments' ) ) : ?>
      <ul class="pager comments-nav-below">
        <li class="previous"><?php previous_comments_link( __( 'Older Comments', 'flint' ) ); ?></li>
        <li class="next"><?php next_comments_link( __( 'Newer Comments', 'flint' ) ); ?></li>
      </ul><!-- .pager -->
      <?php endif; // check for comment navigation ?>

    <?php endif; // have_comments() ?>

    <?php
      if ( ! comments_open() && '0' != get_comments_number() && post_type_supports( get_post_type(), 'comments' ) ) :
    ?>
      <p class="no-comments"><?php _e( 'Comments are closed.', 'flint' ); ?></p>
    <?php endif; ?>

    <?php flint_comment_form(); ?>

  </div><!-- #comments -->
  <?php flint_get_template('margins'); ?>
</div>
