<?php
/**
 * Flint Theme Customizer
 *
 * @package Flint
 * @since 1.3.3
 */

function flint_customize_register( $wp_customize ) {

  $defaults = flint_get_option_defaults();

  $fonts = array(
    'Open Sans'         => 'Open Sans',
    'Oswald'            => 'Oswald',
    'Roboto'            => 'Roboto',
    'Droid Sans'        => 'Droid Sans',
    'Lato'              => 'Lato',
    'Nova Square'       => 'Nova Square',
    'Strait'            => 'Strait',
    'Yanone Kaffeesatz' => 'Yanone Kaffeesatz',
  );

  $wp_customize->remove_section( 'title_tagline' );

  /**
   * Site Information panel
   */
  $wp_customize->add_panel( 'flint_site_info' , array(
    'title'    => __( 'Site Information', 'flint' ),
    'priority' => 20,
  ));

    /**
     * Title/Tagline section
     */
    $wp_customize->add_section( 'title_tagline', array(
      'title'    => __( 'Site Title & Tagline', 'flint' ),
      'priority' => 20,
      'panel'    => 'flint_site_info',
    ));

    /**
     * Organization Information section
     */
    $wp_customize->add_section( 'flint_organization', array(
      'title'    => __( 'Organization Information', 'flint' ),
      'priority' => 40,
      'panel'    => 'flint_site_info',
    ));

      /**
       * Company Name setting
       */
      $wp_customize->add_setting('flint_options[org]', array(
        'default'           => $defaults['org'],
        'sanitize_callback' => 'sanitize_text_field',
        'capability'        => 'edit_theme_options',
        'type'              => 'option',
        'transport'         => 'refresh',
      ));
      $wp_customize->add_control( new WP_Customize_Control($wp_customize, 'org', array(
        'label'    => __('Organization', 'flint'),
        'section'  => 'flint_organization',
        'settings' => 'flint_options[org]',
        'priority' => 41,
        'type'     => 'text',
      )));

      /**
       * Street Address setting
       */
      $wp_customize->add_setting('flint_options[org_address]', array(
        'default'           => $defaults['org_address'],
        'sanitize_callback' => 'sanitize_text_field',
        'capability'        => 'edit_theme_options',
        'type'              => 'option',
        'transport'         => 'refresh',
      ));
      $wp_customize->add_control( new WP_Customize_Control($wp_customize, 'org_address', array(
        'label'    => __('Street Address', 'flint'),
        'section'  => 'flint_organization',
        'settings' => 'flint_options[org_address]',
        'priority' => 42,
        'type'     => 'text',
      )));

      /**
       * City, State setting
       */
      $wp_customize->add_setting('flint_options[org_locality]', array(
        'default'           => $defaults['org_locality'],
        'sanitize_callback' => 'sanitize_text_field',
        'capability'        => 'edit_theme_options',
        'type'              => 'option',
        'transport'         => 'refresh',
      ));
      $wp_customize->add_control( new WP_Customize_Control($wp_customize, 'org_locality', array(
        'label'    => __('City, State', 'flint'),
        'section'  => 'flint_organization',
        'settings' => 'flint_options[org_locality]',
        'priority' => 43,
        'type'     => 'text',
      )));

      /**
       * Postal Code setting
       */
      $wp_customize->add_setting('flint_options[org_postal_code]', array(
        'default'           => $defaults['org_postal_code'],
        'sanitize_callback' => 'sanitize_text_field',
        'capability'        => 'edit_theme_options',
        'type'              => 'option',
        'transport'         => 'refresh',
      ));
      $wp_customize->add_control( new WP_Customize_Control($wp_customize, 'org_postal_code', array(
        'label'    => __('Zip Code', 'flint'),
        'section'  => 'flint_organization',
        'settings' => 'flint_options[org_postal_code]',
        'priority' => 44,
        'type'     => 'text',
      )));

      /**
       * Phone setting
       */
      $wp_customize->add_setting('flint_options[org_tel]', array(
        'default'           => $defaults['org_tel'],
        'sanitize_callback' => 'sanitize_text_field',
        'capability'        => 'edit_theme_options',
        'type'              => 'option',
        'transport'         => 'refresh',
      ));
      $wp_customize->add_control( new WP_Customize_Control($wp_customize, 'org_tel', array(
        'label'    => __('Phone Number', 'flint'),
        'section'  => 'flint_organization',
        'settings' => 'flint_options[org_tel]',
        'priority' => 45,
        'type'     => 'tel',
      )));

      /**
       * Fax Number setting
       */
      $wp_customize->add_setting('flint_options[org_fax]', array(
        'default'           => $defaults['org_fax'],
        'sanitize_callback' => 'sanitize_text_field',
        'capability'        => 'edit_theme_options',
        'type'              => 'option',
        'transport'         => 'refresh',
      ));
      $wp_customize->add_control( new WP_Customize_Control($wp_customize, 'org_fax', array(
        'label'    => __('Fax Number', 'flint'),
        'section'  => 'flint_organization',
        'settings' => 'flint_options[org_fax]',
        'priority' => 46,
        'type'     => 'text',
      )));

      /**
       * Email Address setting
       */
      $wp_customize->add_setting('flint_options[org_email]', array(
        'default'           => $defaults['org_email'],
        'sanitize_callback' => 'is_email',
        'capability'        => 'edit_theme_options',
        'type'              => 'option',
        'transport'         => 'refresh',
      ));
      $wp_customize->add_control( new WP_Customize_Control($wp_customize, 'org_email', array(
        'label'    => __('Email Address', 'flint'),
        'section'  => 'flint_organization',
        'settings' => 'flint_options[org_email]',
        'priority' => 47,
        'type'     => 'email',
      )));

    /**
     * Custom Footer section
     */
    $wp_customize->add_section( 'flint_footer' , array(
      'title'       => __( 'Custom Footer', 'flint' ),
      'description' => 'Customize the footer using template tags. <a href="http://sparks.starverte.com/flint/customize/#custom_footer" target="_blank">Learn more</a>',
      'priority'    => 60,
      'panel'       => 'flint_site_info',
    ));

      /**
       * Footer Text setting
       */
      $wp_customize->add_setting('flint_options[footer_content]', array(
        'default'           => $defaults['footer_content'],
        'sanitize_callback' => 'esc_textarea',
        'capability'        => 'edit_theme_options',
        'type'              => 'option',
        'transport'         => 'refresh',
      ));
      $wp_customize->add_control( new Flint_Customize_TextArea_Control($wp_customize, 'footer_content', array(
        'label'    => __('Footer Text', 'flint'),
        'section'  => 'flint_footer',
        'settings' => 'flint_options[footer_content]',
        'priority' => 61,
        'type'     => 'textarea',
      )));
  /**
   * Fonts section
   */
  $wp_customize->add_section( 'flint_section_fonts' , array(
    'title'    => __( 'Fonts', 'flint' ),
    'priority' => 30,
  ));

    /**
     * Headings font setting
     */
    $wp_customize->add_setting('flint_options[headings_font_family]', array(
      'default'           => $defaults['headings_font_family'],
      'sanitize_callback' => 'flint_sanitize_font',
      'capability'        => 'edit_theme_options',
      'type'              => 'option',
      'transport'         => 'postMessage',
    ));
    $wp_customize->add_control( new WP_Customize_Control($wp_customize, 'headings_font_family', array(
      'label'    => __('Headings', 'flint'),
      'section'  => 'flint_section_fonts',
      'settings' => 'flint_options[headings_font_family]',
      'priority' => 31,
      'type'     => 'select',
      'choices'  => $fonts,
    )));

    /**
     * Body font setting
     */
    $wp_customize->add_setting('flint_options[font_family_base]', array(
      'default'           => $defaults['font_family_base'],
      'sanitize_callback' => 'flint_sanitize_font',
      'capability'        => 'edit_theme_options',
      'type'              => 'option',
      'transport'         => 'postMessage',
    ));
    $wp_customize->add_control( new WP_Customize_Control($wp_customize, 'font_family_base', array(
      'label'    => __('Body', 'flint'),
      'section'  => 'flint_section_fonts',
      'settings' => 'flint_options[font_family_base]',
      'priority' => 32,
      'type'     => 'select',
      'choices'  => $fonts,
    )));

  /**
   * Colors section
   */

    $wp_customize->remove_control( 'header_textcolor' );

    /**
     * Link color setting
     */
    $wp_customize->add_setting('flint_options[link_color]', array(
      'default'           => $defaults['link_color'],
      'sanitize_callback' => 'sanitize_hex_color',
      'capability'        => 'edit_theme_options',
      'type'              => 'option',
      'transport'         => 'postMessage',
    ));
    $wp_customize->add_control( new WP_Customize_Color_Control($wp_customize, 'link_color', array(
      'label'    => __('Links', 'flint'),
      'section'  => 'colors',
      'settings' => 'flint_options[link_color]',
      'priority' => 60,
    )));

    /**
     * Fill background color setting
     */
    $wp_customize->add_setting('flint_options[fill]', array(
      'default'           => $defaults['fill'],
      'sanitize_callback' => 'sanitize_hex_color',
      'capability'        => 'edit_theme_options',
      'type'              => 'option',
      'transport'         => 'postMessage',
    ));
    $wp_customize->add_control( new WP_Customize_Color_Control($wp_customize, 'fill', array(
      'label'    => __('Fill', 'flint'),
      'section'  => 'colors',
      'settings' => 'flint_options[fill]',
      'priority' => 70,
    )));

    /**
     * Fill text color setting
     */
    $wp_customize->add_setting('flint_options[fill_color]', array(
      'default'           => $defaults['fill_color'],
      'sanitize_callback' => 'sanitize_hex_color',
      'capability'        => 'edit_theme_options',
      'type'              => 'option',
      'transport'         => 'postMessage',
    ));
    $wp_customize->add_control( new WP_Customize_Color_Control($wp_customize, 'fill_color', array(
      'label'    => __('Fill Text', 'flint'),
      'section'  => 'colors',
      'settings' => 'flint_options[fill_color]',
      'priority' => 80,
    )));

  /**
   * Layout panel
   */
  $wp_customize->add_panel( 'flint_panel_layout' , array(
    'title'    => __( 'Layout', 'flint' ),
    'priority' => 60,
  ));

    /**
     * Default post template section
     */
    $wp_customize->add_section( 'flint_section_post' , array(
      'title'       => __( 'Posts', 'flint' ),
      'priority'    => 10,
      'panel'       => 'flint_panel_layout',
    ));

      /**
       * Default Content Width setting
       */
      $wp_customize->add_setting('flint_options[post_default_width]', array(
        'default'           => $defaults['post_default_width'],
        'sanitize_callback' => 'flint_sanitize_width',
        'capability'        => 'edit_theme_options',
        'type'              => 'option',
        'transport'         => 'refresh',
      ));
      $wp_customize->add_control( new WP_Customize_Control($wp_customize, 'post_default_width', array(
        'label'    => __('Content Width', 'flint'),
        'section'  => 'flint_section_post',
        'settings' => 'flint_options[post_default_width]',
        'priority' => 11,
        'type'     => 'select',
        'choices'  => array(
          'slim'   => 'Slim',
          'narrow' => 'Narrow',
          'full'   => 'Full',
          'wide'   => 'Wide',
        ),
      )));

      /**
       * Featured Images on Posts setting
       */
      $wp_customize->add_setting('flint_options[post_featured_image]', array(
        'default'           => $defaults['post_featured_image'],
        'sanitize_callback' => 'flint_sanitize_featured_image',
        'capability'        => 'edit_theme_options',
        'type'              => 'option',
        'transport'         => 'refresh',
      ));
      $wp_customize->add_control( new WP_Customize_Control($wp_customize, 'post_featured_image', array(
        'label'    => __('Featured Images', 'flint'),
        'section'  => 'flint_section_post',
        'settings' => 'flint_options[post_featured_image]',
        'priority' => 12,
        'type'     => 'select',
        'choices'  => array(
          'always'   => 'Always show',
          'archives' => 'Archives/Search Only',
          'never'    => 'Hide',
        ),
      )));

    /**
     * Default page template section
     */
    $wp_customize->add_section( 'flint_section_page' , array(
      'title'       => __( 'Pages', 'flint' ),
      'priority'    => 20,
      'panel'       => 'flint_panel_layout',
    ));

      /**
       * Default Content Width setting
       */
      $wp_customize->add_setting('flint_options[page_default_width]', array(
        'default'           => $defaults['page_default_width'],
        'sanitize_callback' => 'flint_sanitize_width',
        'capability'        => 'edit_theme_options',
        'type'              => 'option',
        'transport'         => 'refresh',
      ));
      $wp_customize->add_control( new WP_Customize_Control($wp_customize, 'page_default_width', array(
        'label'    => __('Content Width', 'flint'),
        'section'  => 'flint_section_page',
        'settings' => 'flint_options[page_default_width]',
        'priority' => 21,
        'type'     => 'select',
        'choices'  => array(
          'slim'   => 'Slim',
          'narrow' => 'Narrow',
          'full'   => 'Full',
          'wide'   => 'Wide',
        ),
      )));

      /**
       * Featured Images on Pages setting
       */
      $wp_customize->add_setting('flint_options[page_featured_image]', array(
        'default'           => $defaults['page_featured_image'],
        'sanitize_callback' => 'flint_sanitize_featured_image',
        'capability'        => 'edit_theme_options',
        'type'              => 'option',
        'transport'         => 'refresh',
      ));
      $wp_customize->add_control( new WP_Customize_Control($wp_customize, 'page_featured_image', array(
        'label'    => __('Featured Images', 'flint'),
        'section'  => 'flint_section_page',
        'settings' => 'flint_options[page_featured_image]',
        'priority' => 23,
        'type'     => 'select',
        'choices'  => array(
          'always'   => 'Always show',
          'archives' => 'Archives/Search Only',
          'never'    => 'Hide',
        ),
      )));

    /**
     * Clear template section
     */
    $wp_customize->add_section( 'flint_section_clear' , array(
      'title'       => __( 'Clear Page Template', 'flint' ),
      'description' => __( 'Clear is a page template that allows you to focus on just your content, free from distractions.', 'flint' ),
      'priority'    => 30,
      'panel'       => 'flint_panel_layout',
    ));

      /**
       * Clear Content Width setting
       */
      $wp_customize->add_setting('flint_options[clear_width]', array(
        'default'           => $defaults['clear_width'],
        'sanitize_callback' => 'flint_sanitize_width',
        'capability'        => 'edit_theme_options',
        'type'              => 'option',
        'transport'         => 'refresh',
      ));
      $wp_customize->add_control( new WP_Customize_Control($wp_customize, 'clear_width', array(
        'label'    => __('Content Width', 'flint'),
        'section'  => 'flint_section_clear',
        'settings' => 'flint_options[clear_width]',
        'priority' => 31,
        'type'     => 'select',
        'choices'  => array(
          'slim'   => 'Slim',
          'narrow' => 'Narrow',
          'full'   => 'Full',
          'wide'   => 'Wide',
        ),
      )));

      /**
       * Clear Navigation setting
       */
      $wp_customize->add_setting('flint_options[clear_nav]', array(
        'default'           => $defaults['clear_nav'],
        'sanitize_callback' => 'flint_sanitize_clear_nav',
        'capability'        => 'edit_theme_options',
        'type'              => 'option',
        'transport'         => 'refresh',
      ));
      $wp_customize->add_control( new WP_Customize_Control($wp_customize, 'clear_nav', array(
        'label'    => __('Navigation', 'flint'),
        'section'  => 'flint_section_clear',
        'settings' => 'flint_options[clear_nav]',
        'priority' => 32,
        'type'     => 'select',
        'choices'  => array(
          'breadcrumbs' => 'Breadcrumbs',
          'navbar'      => 'Navigation Bar',
        ),
      )));

    /**
     * Minimal template section
     */
    $wp_customize->add_section( 'flint_section_minimal' , array(
      'title'       => __( 'Minimal Page Template', 'flint' ),
      'description' => __( 'Minimal provides an additional page template with the focus on the content and an optional widget area.', 'flint' ),
      'priority'    => 40,
      'panel'       => 'flint_panel_layout',
    ));

      /**
       * Minimal Content Width setting
       */
      $wp_customize->add_setting('flint_options[minimal_width]', array(
        'default'           => $defaults['minimal_width'],
        'sanitize_callback' => 'flint_sanitize_width',
        'capability'        => 'edit_theme_options',
        'type'              => 'option',
        'transport'         => 'refresh',
      ));
      $wp_customize->add_control( new WP_Customize_Control($wp_customize, 'minimal_width', array(
        'label'    => __('Content Width', 'flint'),
        'section'  => 'flint_section_minimal',
        'settings' => 'flint_options[minimal_width]',
        'priority' => 41,
        'type'     => 'select',
        'choices'  => array(
          'slim'   => 'Slim',
          'narrow' => 'Narrow',
          'full'   => 'Full',
          'wide'   => 'Wide',
        ),
      )));

      /**
       * Minimal Navigation setting
       */
      $wp_customize->add_setting('flint_options[minimal_nav]', array(
        'default'           => $defaults['minimal_nav'],
        'sanitize_callback' => 'flint_sanitize_minimal_nav',
        'capability'        => 'edit_theme_options',
        'type'              => 'option',
        'transport'         => 'refresh',
      ));
      $wp_customize->add_control( new WP_Customize_Control($wp_customize, 'minimal_nav', array(
        'label'    => __('Navigation', 'flint'),
        'section'  => 'flint_section_minimal',
        'settings' => 'flint_options[minimal_nav]',
        'priority' => 42,
        'type'     => 'select',
        'choices'  => array(
          'breadcrumbs' => 'Breadcrumbs',
          'navbar'      => 'Navigation Bar',
        ),
      )));

      /**
       * Minimal Widget Area setting
       */
      $wp_customize->add_setting('flint_options[minimal_widget_area]', array(
        'default'           => $defaults['minimal_widget_area'],
        'sanitize_callback' => 'flint_sanitize_minimal_widget_area',
        'capability'        => 'edit_theme_options',
        'type'              => 'option',
        'transport'         => 'refresh',
      ));
      $wp_customize->add_control( new WP_Customize_Control($wp_customize, 'minimal_widget_area', array(
        'label'    => __('Widget Area', 'flint'),
        'section'  => 'flint_section_minimal',
        'settings' => 'flint_options[minimal_widget_area]',
        'priority' => 43,
        'type'     => 'select',
        'choices'  => array(
          'none'   => 'None',
          'header' => 'Header',
          'left'   => 'Left',
          'right'  => 'Right',
          'footer' => 'Footer',
        ),
      )));

    /**
     * Widget Columns section
     */
    $wp_customize->add_section( 'flint_widget_areas' , array(
      'title'       => __( 'Widget Columns', 'flint' ),
      'description' => 'For screens larger than 768px wide, the widget areas above and below the content can be divided into 3 columns.',
      'priority'    => 180,
      'panel'       => 'flint_panel_layout',
    ));

      /**
       * Top Widget Area Columns setting
       */
      $wp_customize->add_setting('flint_options[widget_areas_above]', array(
        'default'           => $defaults['widget_areas_above'],
        'sanitize_callback' => 'flint_sanitize_widget_columns',
        'capability'        => 'edit_theme_options',
        'type'              => 'option',
        'transport'         => 'refresh',
      ));
      $wp_customize->add_control( new WP_Customize_Control($wp_customize, 'widget_areas_above', array(
        'label'    => __('Header', 'flint'),
        'section'  => 'flint_widget_areas',
        'settings' => 'flint_options[widget_areas_above]',
        'priority' => 11,
        'type'     => 'select',
        'choices'  => array(
          '1' => 'Full-width',
          '3' => '3 columns',
        ),
      )));

      /**
       * Bottom Widget Area Columns setting
       */
      $wp_customize->add_setting('flint_options[widget_areas_below]', array(
        'default'           => $defaults['widget_areas_below'],
        'sanitize_callback' => 'flint_sanitize_widget_columns',
        'capability'        => 'edit_theme_options',
        'type'              => 'option',
        'transport'         => 'refresh',
      ));
      $wp_customize->add_control( new WP_Customize_Control($wp_customize, 'widget_areas_below', array(
        'label'    => __('Footer', 'flint'),
        'section'  => 'flint_widget_areas',
        'settings' => 'flint_options[widget_areas_below]',
        'priority' => 12,
        'type'     => 'select',
        'choices'  => array(
          '1' => 'Full-width',
          '3' => '3 columns',
        ),
      )));

  /**
   * Header Image section
   */

  /**
   * Background Image section
   */

  /**
   * Navigation section
   */

  /**
   * Widgets panel
   */

  $wp_customize->get_setting( 'blogname'         )->transport = 'postMessage';
  $wp_customize->get_setting( 'blogdescription'  )->transport = 'postMessage';
  $wp_customize->get_setting( 'header_textcolor' )->transport = 'postMessage';
}
add_action( 'customize_register', 'flint_customize_register' );

function flint_customize_preview_init() {
  wp_enqueue_script( 'flint_customizer', get_template_directory_uri() . '/js/customizer.js', array( 'customize-preview' ), flint_theme_version(), true );

  wp_enqueue_style( 'open-sans'        , '//fonts.googleapis.com/css?family=Open+Sans:300,600,300,700,300italic,600italic,700italic', array(), '' );
  wp_enqueue_style( 'oswald'           , '//fonts.googleapis.com/css?family=Oswald:300,400,700'                                     , array(), '' );
  wp_enqueue_style( 'roboto'           , '//fonts.googleapis.com/css?family=Roboto:300,300italic,400,400italic,700,700italic'       , array(), '' );
  wp_enqueue_style( 'droid-sans'       , '//fonts.googleapis.com/css?family=Droid+Sans:400,700'                                     , array(), '' );
  wp_enqueue_style( 'lato'             , '//fonts.googleapis.com/css?family=Lato:300,400,700,300italic,400italic,700italic'         , array(), '' );
  wp_enqueue_style( 'nova-square'      , '//fonts.googleapis.com/css?family=Nova+Square'                                            , array(), '' );
  wp_enqueue_style( 'strait'           , '//fonts.googleapis.com/css?family=Strait'                                                 , array(), '' );
  wp_enqueue_style( 'yanone-kaffeesatz', '//fonts.googleapis.com/css?family=Yanone+Kaffeesatz:400,300,700'                          , array(), '' );
}
add_action( 'customize_preview_init', 'flint_customize_preview_init' );

if (class_exists('WP_Customize_Control')) {
  class Flint_Customize_TextArea_Control extends WP_Customize_Control {
    public $type = 'textarea';
    public $description;

    public function render_content() {
      ?>
      <label>
        <?php if ( ! empty( $this->label ) ) : ?>
          <span class="customize-control-title"><?php echo esc_html( $this->label ); ?></span>
        <?php endif;
        if ( ! empty( $this->description ) ) : ?>
          <span class="description customize-control-description"><?php echo $this->description; ?></span>
        <?php endif; ?>
        <textarea rows="5" <?php $this->link(); ?>><?php echo esc_textarea( $this->value() ); ?></textarea>
      </label>
      <?php
    }
  }
}

function flint_sanitize_font( $input ) {
  $valid = array(
    'Open Sans'         => 'Open Sans',
    'Oswald'            => 'Oswald',
    'Roboto'            => 'Roboto',
    'Droid Sans'        => 'Droid Sans',
    'Lato'              => 'Lato',
    'Nova Square'       => 'Nova Square',
    'Strait'            => 'Strait',
    'Yanone Kaffeesatz' => 'Yanone Kaffeesatz',
  );

  if ( array_key_exists( $input, $valid ) ) {
    return $input;
  } else {
    return $defaults['font_family_base'];
  }
}

function flint_sanitize_width( $input ) {
  $valid = array(
    'slim'   => 'Slim',
    'narrow' => 'Narrow',
    'full'   => 'Full',
    'wide'   => 'Wide',
  );

  if ( array_key_exists( $input, $valid ) ) {
    return $input;
  } else {
    return $defaults['post_default_width'];
  }
}

function flint_sanitize_clear_nav( $input ) {
  $valid = array(
    'breadcrumbs' => 'Breadcrumbs',
    'navbar'      => 'Navigation Bar',
  );

  if ( array_key_exists( $input, $valid ) ) {
    return $input;
  } else {
    return $defaults['clear_nav'];
  }
}

function flint_sanitize_minimal_nav( $input ) {
  $valid = array(
    'breadcrumbs' => 'Breadcrumbs',
    'navbar'      => 'Navigation Bar',
  );

  if ( array_key_exists( $input, $valid ) ) {
    return $input;
  } else {
    return $defaults['minimal_nav'];
  }
}

function flint_sanitize_minimal_widget_area( $input ) {
  $valid = array(
    'none'   => 'None',
    'header' => 'Header',
    'left'   => 'Left',
    'right'  => 'Right',
    'footer' => 'Footer',
  );

  if ( array_key_exists( $input, $valid ) ) {
    return $input;
  } else {
    return $defaults['minimal_widget_area'];
  }
}

function flint_sanitize_featured_image( $input ) {
  $valid = array(
    'always'   => 'Always show',
    'archives' => 'Archives/Search Only',
    'never'    => 'Hide',
  );

  if ( array_key_exists( $input, $valid ) ) {
    return $input;
  } else {
    return $defaults['post_featured_image'];
  }
}

function flint_sanitize_widget_columns( $input ) {
  $valid = array(
    '1' => 'Full-width',
    '3' => '3 columns',
  );

  if ( array_key_exists( $input, $valid ) ) {
    return $input;
  } else {
    return $defaults['widget_areas_above'];
  }
}

