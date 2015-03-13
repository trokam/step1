<?php
/**
 * Creates Custom Header page
 *
 * @package Flint
 * @since 1.3.0
 */

if ( ! function_exists( 'flint_header_style' ) ) :
/**
 * Styles the header image and text displayed on the blog
 */
function flint_header_style() {

  if ( HEADER_TEXTCOLOR == get_header_textcolor() )
    return;
  ?>
  <style type="text/css">
  <?php
    if ( 'blank' == get_header_textcolor() ) :
  ?>
    .site-title,
    .site-description {
      position: absolute !important;
      clip: rect(1px 1px 1px 1px); /* IE6, IE7 */
      clip: rect(1px, 1px, 1px, 1px);
    }
  <?php
    else :
  ?>
    .site-title a,
    .site-description {
      color: #<?php echo get_header_textcolor(); ?>;
    }
  <?php endif; ?>
  </style>
  <?php
}
endif; // flint_header_style

if ( ! function_exists( 'flint_admin_header_style' ) ) :
/**
 * Styles the header image displayed on the Appearance > Header admin panel.
 */
function flint_admin_header_style() {
  $options = flint_get_options();
  $colors  = flint_get_colors();
?>
  <style type="text/css">
    @import url("//fonts.googleapis.com/css?family=Open+Sans:300italic,400italic,600italic,700italic,400,300,600,700");
    .row::before, .row::after {
      display: table;
      content: " ";
    }
    .row::after {
      clear: both;
    }
    .appearance_page_custom-header #heading {
      background: <?php echo $colors['fill']; ?>;
      border: none;
    }
    img {
      height:auto;
      max-width: 160px;
      padding-top: 10px;
      padding-bottom: 10px;
      vertical-align: middle;
      border: 0;
    }
    .col-xs-2, .col-xs-8 {
      float: left;
      position: relative;
      min-height: 1px;
      padding-right: 15px;
      padding-left: 15px;
      -webkit-box-sizing: border-box;
      -moz-box-sizing: border-box;
      box-sizing: border-box;
    }
    .col-xs-2 {
      width: 16.666666666666664%;
    }
    .col-xs-8 {
      width: 66.66666666666666%;
    }
    .site-branding h1 {
      font-size: 56px!important;
      margin: .67em 0;
    }
    .site-branding h2 {
      font-size: 18px!important;
    }
    .site-branding h1,
    .site-branding h2 {
      font-family: "<?php echo $options['headings_font_family']; ?>", sans-serif!important;
      font-weight: 500!important;
      line-height: 1.1;
      margin-top: 20px;
      margin-bottom: 10px;
    }


  </style>
<?php
}
endif; // flint_admin_header_style

if ( ! function_exists( 'flint_admin_header_image' ) ) :
/**
 * Custom header image markup displayed on the Appearance > Header admin panel.
 */
function flint_admin_header_image() { ?>
  <div id="heading" class="row">
    <?php
    if ( 'blank' == get_header_textcolor() || '' == get_header_textcolor() )
      $style = ' style="display:none;"';
    else
      $style = ' style="color:#' . get_header_textcolor() . ';"';
    ?>
    <?php $header_image = get_header_image();
    if ( ! empty( $header_image ) ) { ?>
      <a href="<?php echo esc_url( home_url( '/' ) ); ?>" title="<?php echo esc_attr( get_bloginfo( 'name', 'display' ) ); ?>" rel="home" <?php if ( display_header_text() ) { ?> class="col-xs-2"<?php } ?>>
        <img src="<?php header_image(); ?>" width="<?php echo get_custom_header()->width; ?>" height="<?php echo get_custom_header()->height; ?>" alt="" />
      </a>
    <?php } // if ( ! empty( $header_image ) )
    if ( display_header_text() ) { ?>
    <div class="site-branding <?php if ( ! empty( $header_image ) ) { ?>col-xs-8<?php } ?>">
      <h1 class="site-title" style="font-size: 27px;font-weight:bold;text-shadow:none;"><a href="<?php echo esc_url( home_url( '/' ) ); ?>" title="<?php echo esc_attr( get_bloginfo( 'name', 'display' ) ); ?>" rel="home" style="color:#<?php echo get_header_textcolor() ?>;text-decoration: none;"><?php bloginfo( 'name' ); ?></a></h1>
      <h2 class="site-description" style="font-weight:bold;text-shadow:none;color:#<?php echo get_header_textcolor() ?>"><?php bloginfo( 'description' ); ?></h2>
    </div>
    <?php } // if ( display_header_text() ) ?>
  </div>
<?php }
endif; // flint_admin_header_image
