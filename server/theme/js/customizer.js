/**
 * Theme Customizer enhancements for a better user experience.
 *
 * Contains handlers to make Theme Customizer preview reload changes asynchronously.
 *
 * @package Flint
 * @since 1.3.0
 */

( function( $ ) {
  wp.customize( 'flint_options[link_color]', function( value ) {
    value.bind( function( to ) {
      $( '.entry-header a, .entry-header a:hover, .entry-header a:focus' ).css( 'color', to );
      $( '.entry-content a, .entry-content a:hover, .entry-content a:focus' ).css( 'color', to );
    } );
  } );

  // Site title and description.
  wp.customize( 'blogname', function( value ) {
    value.bind( function( to ) {
      $( '.site-title a' ).text( to );
    } );
  } );
  wp.customize( 'blogdescription', function( value ) {
    value.bind( function( to ) {
      $( '.site-description' ).text( to );
    } );
  } );
  // Header text color.
  wp.customize( 'header_textcolor', function( value ) {
    value.bind( function( to ) {
      $( '.site-title a, .site-description' ).css( 'color', to );
    } );
  } );

  // Fill colors
  wp.customize( 'flint_options[fill]', function( value ) {
    value.bind( function( to ) {
      $( '.fill' ).css( 'background-color', to );
    } );
  } );
  wp.customize( 'flint_options[fill_color]', function( value ) {
    value.bind( function( to ) {
      $( '.fill' ).css( 'color', to );
    } );
  } );

  // Fonts
  wp.customize( 'flint_options[headings_font_family]', function( value ) {
    value.bind( function( to ) {
      $( 'h1, h2, h3, h4, h5, h6, .h1, .h2, .h3, .h4, .h5, .h6' ).css( 'font-family', to );
    } );
  } );
  wp.customize( 'flint_options[font_family_base]', function( value ) {
    value.bind( function( to ) {
      $( 'body' ).css( 'font-family', to );
    } );
  } );
} )( jQuery );
