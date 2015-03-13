<?php
/**
 * Flint Options
 * WordPress Options API
 *
 * @package Flint
 * @since 1.3.3
 */

function flint_get_option_defaults() {
  $defaults = array(
    'text_color'                 => '#404040',
    'body_bg'                    => '#ffffff',
    'fill_color'                 => '#ffffff',
    'fill'                       => '#222222',
    'link_color'                 => '#428bca',

    'font_family_base'           => 'Open Sans',
    'headings_font_family'       => 'Open Sans',

    'org'                        => '',
    'org_address'                => '',
    'org_locality'               => '',
    'org_postal_code'            => '',
    'org_tel'                    => '',
    'org_fax'                    => '',
    'org_email'                  => '',

    'clear_nav'                  => 'breadcrumbs',
    'clear_width'                => 'full',

    'footer_content'             => '',

    'page_featured_image'        => 'always',
    'page_default_width'         => 'full',

    'post_featured_image'        => 'always',
    'post_default_width'         => 'full',

    'minimal_nav'                => 'navbar',
    'minimal_widget_area'        => 'none',
    'minimal_width'              => 'full',

    'widget_areas_above'         => '1',
    'widget_areas_below'         => '1',
  );

  return apply_filters('flint_option_defaults', $defaults);
}

/**
 * Gets array of theme options
 * For backwards compatibility, can also get single value
 *
 * @var string Deprecated. The single option to return.
 */
function flint_get_options( $option = null ) {
  $defaults = flint_get_option_defaults();

  $defaults['body_bg']    = get_theme_mod('background_color', $defaults['body_bg'   ]);
  $defaults['fill_color'] = get_theme_mod('header_textcolor', $defaults['fill_color']);

  //BEGIN - backwards compatibility
  $colors    = get_option( 'flint_colors'    );
  $fonts     = get_option( 'flint_fonts'     );
  $general   = get_option( 'flint_general'   );
  $layout    = get_option( 'flint_layout'    );
  $templates = get_option( 'flint_templates' );
  $wa        = get_option( 'flint_wa'        );

  $defaults['fill']                 = !empty($colors['canvas'])                 ? $colors['canvas']                 : $defaults['fill'];
  $defaults['link_color']           = !empty($colors['link'])                   ? $colors['link']                   : $defaults['link_color'];

  $defaults['font_family_base']     = !empty($fonts['body_font'])               ? $fonts['body_font']               : $defaults['font_family_base'];
  $defaults['headings_font_family'] = !empty($fonts['heading_font'])            ? $fonts['heading_font']            : $defaults['headings_font_family'];

  $defaults['org']                  = !empty($general['company'])               ? $general['company']               : $defaults['org'];
  $defaults['org_address']          = !empty($general['address'])               ? $general['address']               : $defaults['org_address'];
  $defaults['org_locality']         = !empty($general['locality'])              ? $general['locality']              : $defaults['org_locality'];
  $defaults['org_postal_code']      = !empty($general['postal_code'])           ? $general['postal_code']           : $defaults['org_postal_code'];
  $defaults['org_tel']              = !empty($general['tel'])                   ? $general['tel']                   : $defaults['org_tel'];
  $defaults['org_fax']              = !empty($general['fax'])                   ? $general['fax']                   : $defaults['org_fax'];
  $defaults['org_email']            = !empty($general['email'])                 ? $general['email']                 : $defaults['org_email'];

  $defaults['clear_nav']            = !empty($templates['clear_nav'])           ? $templates['clear_nav']           : $defaults['clear_nav'];
  $defaults['clear_width']          = !empty($templates['clear_width'])         ? $templates['clear_width']         : $defaults['clear_width'];

  $defaults['footer_content']       = !empty($general['text'])                  ? $general['text']                  : $defaults['footer_content'];

  $defaults['page_featured_image']  = !empty($layout['pages_image'])            ? $layout['pages_image']            : $defaults['page_featured_image'];
  $defaults['page_default_width']   = !empty($templates['default_width'])       ? $templates['default_width']       : $defaults['page_default_width'];

  $defaults['post_featured_image']  = !empty($layout['posts_image'])            ? $layout['posts_image']            : $defaults['post_featured_image'];
  $defaults['post_default_width']   = !empty($templates['default_post_width'])  ? $templates['default_post_width']  : $defaults['post_default_width'];

  $defaults['minimal_nav']          = !empty($templates['minimal_nav'])         ? $templates['minimal_nav']         : $defaults['minimal_nav'];
  $defaults['minimal_widget_area']  = !empty($templates['minimal_widget_area']) ? $templates['minimal_widget_area'] : $defaults['minimal_widget_area'];
  $defaults['minimal_width']        = !empty($templates['minimal_width'])       ? $templates['minimal_width']       : $defaults['minimal_width'];

  $defaults['widget_areas_above']   = !empty($wa['header'])                     ? $wa['header']                     : $defaults['widget_areas_above'];
  $defaults['widget_areas_below']   = !empty($wa['footer'])                     ? $wa['footer']                     : $defaults['widget_areas_below'];
  //END - backwards compatibility

  $flint_options = wp_parse_args( get_option( 'flint_options' ), $defaults );

  if (!empty($option)) {
    $search = array(
      'canvas-text',
      'canvas',
      'link',
      'body_font',
      'heading_font',
      'company',
      'address',
      'locality',
      'postal_code',
      'tel',
      'fax',
      'email',
      'text',
      'pages_image',
      'default_width',
      'posts_image',
      'default_post_width',
      'header',
      'footer',
    );

    $replace = array(
      'fill_color',
      'fill',
      'link_color',
      'font_family_base',
      'headings_font_family',
      'org',
      'org_address',
      'org_locality',
      'org_postal_code',
      'org_tel',
      'org_fax',
      'org_email',
      'footer_content',
      'page_featured_image',
      'page_default_width',
      'post_featured_image',
      'post_default_width',
      'widget_areas_above',
      'widget_areas_below',
    );

    $_option = str_replace( $search, $replace, $option );

    return $flint_options[$_option];
  }
  else {
    return $flint_options;
  }
}

function flint_get_colors() {
  $options = flint_get_options();
  $calc = array(
    'link_hover_color' => flint_darken($options['link_color'], 15),
    'blockquote_border_color' => flint_lighten($options['fill'], 15),
    'fill_darker' => flint_darken($options['fill'], 20),
    'fill_light' => flint_lighten($options['fill'], 15),
    'fill_link_color' => flint_darken($options['fill_color'], 15),
    'fill_link_hover_color' => $options['fill_color'],
  );
  return wp_parse_args( $options, $calc );
}

function flint_get_address( $schema = true, $args = array() ) {
  $options = flint_get_options();

  $defaults = array(
    'before' => '<span id="street" itemprop="streetAddress">',
    'item1'  => $options['org_address'],
    'sep1'   => '</span>, <span id="locality" itemprop="addressLocality">',
    'item2'  => $options['org_locality'],
    'sep2'   => '</span> <span id="postal-code" itemprop="postalCode">',
    'item3'  => $options['org_postal_code'],
    'after'  => '</span>',
    'open'   => '<div id="org" itemscope itemtype="http://schema.org/Organization"><span id="address" itemprop="address" itemscope itemtype="http://schema.org/PostalAddress">',
    'close'  => '</span></div>',
  );

  $alts = array(
    'before' => '',
    'item1'  => $options['org_address'],
    'sep1'   => ', ',
    'item2'  => $options['org_locality'],
    'sep2'   => ' ',
    'item3'  => $options['org_postal_code'],
    'after'  => '',
    'open'   => '',
    'close'  => '',
  );

  $args = $schema == true ? wp_parse_args( $args, $defaults ) : wp_parse_args( $args, $alts );
  $output = $args['open'] . $args['before'] . $args['item1'] . $args['sep1'] . $args['item2'] . $args['sep2'] . $args['item3'] . $args['after'] . $args['close'];
  echo $output;
}

