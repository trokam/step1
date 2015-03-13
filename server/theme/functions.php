<?php
/**
 * Flint functions and definitions
 *
 * @package Flint
 * @version 1.3.3
 */

/**
 * Set the content width based on the theme's design and stylesheet.
 */
if ( ! isset( $content_width ) )
  $content_width = 750; /* pixels */

if ( ! function_exists( 'flint_after_setup_theme' ) ) :
/**
 * Sets up theme defaults and registers support for various WordPress features.
 */
function flint_after_setup_theme() {

  require( get_template_directory() . '/inc/class-flint_bootstrap_menu.php' );

  require( get_template_directory() . '/inc/template-tags.php' );

  require( get_template_directory() . '/inc/colors.php' );

  require( get_template_directory() . '/inc/extras.php' );

  require( get_template_directory() . '/inc/customizer.php' );

  require( get_template_directory() . '/inc/options.php' );

  load_theme_textdomain( 'flint', get_template_directory() . '/languages' );

  register_nav_menus( array(
    'primary' => __( 'Primary Menu', 'flint' ),
  ) );

  add_editor_style( 'editor-style.css' );

  add_theme_support( 'automatic-feed-links' );

  add_theme_support( 'post-thumbnails' );

  add_theme_support( 'html5' );

  add_theme_support( 'post-formats', array( 'aside', 'chat', 'gallery', 'link', 'status' ) );

  add_theme_support( 'title-tag' );

  $defaults = flint_get_option_defaults();

  /**
   * Implement the Custom Background feature
   */
  $args = array(
    'default-color' => $defaults['body_bg'],
    'default-image' => '',
  );

  $args = apply_filters( 'flint_custom_background_args', $args );

  add_theme_support( 'custom-background', $args );

  /**
   * Implement Custom Header feature
   */
  $header = array(
    'default-image'          => '',
    'default-text-color'     => $defaults['fill_color'],
    'width'                  => 300,
    'height'                 => 300,
    'flex-height'            => true,
    'flex-width'             => true
  );

  $header = apply_filters( 'flint_custom_header_args', $header );

  add_theme_support( 'custom-header', $header );

  /**
   * Add theme support for Infinite Scroll.
   * See: http://jetpack.me/support/infinite-scroll/
   */
  add_theme_support( 'infinite-scroll', array(
    'container' => 'content',
    'footer'    => 'page',
  ) );
}
endif; // flint_after_setup_theme
add_action( 'after_setup_theme', 'flint_after_setup_theme' );

/**
 * Implement the Custom Header feature
 */
require( get_template_directory() . '/inc/custom-header.php' );

/**
 * Register widgetized areas and update sidebar with default widgets
 */
function flint_widgets_init() {
  $options = flint_get_options();

  $widget_areas = array();

  if ( $options['widget_areas_above'] == '3' ) {
    array_push($widget_areas, 'Header Left', 'Header Center', 'Header Right' );
  }
  else {
    array_push($widget_areas, 'Header' );
  }

  array_push($widget_areas, 'Left' );

  array_push($widget_areas, 'Right' );

  if ($options['widget_areas_below'] == '3' ) {
    array_push($widget_areas, 'Footer Left', 'Footer Center', 'Footer Right' );
  }
  else {
    array_push($widget_areas, 'Footer' );
  }

  foreach ($widget_areas as $widget_area) {
    register_sidebar( array(
      'name'          => $widget_area,
      'id'            => str_replace(' ','_',strtolower($widget_area)),
      'before_widget' => '<aside id="%1$s" class="widget %2$s">',
      'after_widget'  => '</aside>',
      'before_title'  => '<h1 class="widget-title">',
      'after_title'   => '</h1>',
    ) );
  }
}
add_action( 'widgets_init', 'flint_widgets_init' );

/**
 * Enqueue scripts and styles
 */
function flint_enqueue_scripts() {

  /**
   * Load Twitter Bootstrap
   */
  wp_enqueue_script( 'bootstrap', get_template_directory_uri() . '/js/bootstrap.min.js', array('jquery'), '3.0.0', true );
  wp_enqueue_style( 'bootstrap-css', get_template_directory_uri() . '/css/bootstrap.min.css', array() , '3.0.0' );

  wp_enqueue_script( 'flint-skip-link-focus-fix', get_template_directory_uri() . '/js/skip-link-focus-fix.js', array(), '9f3e2cd', true );

  if ( is_singular() && comments_open() && get_option( 'thread_comments' ) ) {
    wp_enqueue_script( 'comment-reply' );
  }

  if ( is_singular() && wp_attachment_is_image() ) {
    wp_enqueue_script( 'flint-keyboard-image-navigation', get_template_directory_uri() . '/js/keyboard-image-navigation.js', array( 'jquery' ), '4c99b2a' );
  }

  /*
   * Load Google Fonts
   */
  $options = flint_get_options();

  switch ($options['font_family_base']) {
    case 'Open Sans':
      wp_enqueue_style( 'open-sans', '//fonts.googleapis.com/css?family=Open+Sans:300,600,300,700,300italic,600italic,700italic', array(), flint_theme_version() );
      break;
    case 'Oswald':
      wp_enqueue_style( 'oswald', '//fonts.googleapis.com/css?family=Oswald:300,400,700', array(), flint_theme_version() );
      break;
    case 'Roboto':
      wp_enqueue_style( 'roboto', '//fonts.googleapis.com/css?family=Roboto:300,300italic,400,400italic,700,700italic', array(), flint_theme_version() );
      break;
    case 'Droid Sans':
      wp_enqueue_style( 'droid-sans', '//fonts.googleapis.com/css?family=Droid+Sans:400,700', array(), flint_theme_version() );
      break;
    case 'Lato':
      wp_enqueue_style( 'lato', '//fonts.googleapis.com/css?family=Lato:300,400,700,300italic,400italic,700italic', array(), flint_theme_version() );
      break;
    case 'Nova Square':
      wp_enqueue_style( 'nova-square', '//fonts.googleapis.com/css?family=Nova+Square', array(), flint_theme_version() );
      break;
    case 'Strait':
      wp_enqueue_style( 'strait', '//fonts.googleapis.com/css?family=Strait', array(), flint_theme_version() );
      break;
    case 'Yanone Kaffeesatz':
      wp_enqueue_style( 'yanone-kaffeesatz', '//fonts.googleapis.com/css?family=Yanone+Kaffeesatz:300,400,700', array(), flint_theme_version() );
      break;
  }
  if ( $options['headings_font_family'] != $options['font_family_base'] ) {
    switch ($options['headings_font_family']) {
      case 'Open Sans':
        wp_enqueue_style( 'open-sans', '//fonts.googleapis.com/css?family=Open+Sans:300,600,300,700,300italic,600italic,700italic', array(), flint_theme_version() );
        break;
      case 'Oswald':
        wp_enqueue_style( 'oswald', '//fonts.googleapis.com/css?family=Oswald:300,400,700', array(), flint_theme_version() );
        break;
      case 'Roboto':
        wp_enqueue_style( 'roboto', '//fonts.googleapis.com/css?family=Roboto:300,300italic,400,400italic,700,700italic', array(), flint_theme_version() );
        break;
      case 'Droid Sans':
        wp_enqueue_style( 'droid-sans', '//fonts.googleapis.com/css?family=Droid+Sans:400,700', array(), flint_theme_version() );
        break;
      case 'Lato':
        wp_enqueue_style( 'lato', '//fonts.googleapis.com/css?family=Lato:300,400,700,300italic,400italic,700italic', array(), flint_theme_version() );
        break;
      case 'Nova Square':
        wp_enqueue_style( 'nova-square', '//fonts.googleapis.com/css?family=Nova+Square', array(), flint_theme_version() );
        break;
      case 'Strait':
        wp_enqueue_style( 'strait', '//fonts.googleapis.com/css?family=Strait', array(), flint_theme_version() );
        break;
      case 'Yanone Kaffeesatz':
        wp_enqueue_style( 'yanone-kaffeesatz', '//fonts.googleapis.com/css?family=Yanone+Kaffeesatz:300,400,700', array(), flint_theme_version() );
        break;
    }
  }

  /**
   * Load theme stylesheet
   */
  wp_enqueue_style( 'flint-style', get_stylesheet_uri(), array(), flint_theme_version() );
}
add_action( 'wp_enqueue_scripts', 'flint_enqueue_scripts' );

add_filter( 'use_default_gallery_style', '__return_false' );


//BEGIN - Backwards compatibility for add_theme_support( 'title-tag' )
//Remove after WordPress 4.3 released
if ( ! function_exists( '_wp_render_title_tag' ) ) {
  function flint_render_title() {
      ?>
      <title><?php wp_title( '|', true, 'right' ); ?></title>
      <?php
  }
  add_action( 'wp_head', 'flint_render_title' );
}
//END - Backwards compatibility for add_theme_support( 'title-tag' )

