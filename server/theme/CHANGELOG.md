###Flint 1.3.3
For complete diff, check out [Pull Request](https://github.com/starverte/flint/pull/176)
- Fixed bug that was causing navigation menu to not work on mobile layouts
- Fixed customizer bugs
- Added action `flint_open` to header
- Fixed footer widget area, so that like the footer, is always on the bottom of the page

###Flint 1.3.2
For complete diff, check out [Pull Request](https://github.com/starverte/flint/pull/174)
- Deleted HTML5 Shiv
- Added `translation-ready` tag

###Flint 1.3.1
For complete diff, check out [Pull Request](https://github.com/starverte/flint/pull/172)
- Fix for fatal error for PHP < 5.5
- Updated to Bootstrap 3.3.2

###Flint 1.3.0
For complete diff, check out [Pull Request](https://github.com/starverte/flint/pull/168)
- Header and Footer widget areas can now be divided into three columns
- Added Yanone Kaffeesatz font
- Added theme support for `title-tag`
- Improved responsive grid
- Improved Theme Customizer
- Improved Options API handling
- Improved sidebar layout display
- Slightly darker text color for clarity
- Removed Theme Options page (use Customizer instead)
- `flint_get_options` returns ALL options
- All references to `canvas` changed to `fill` to avoid confusion with `<canvas>` and theme by same name
- Updated Bootstrap to 3.3.1

###Flint 1.2.2
For complete diff, check out [Pull Request](https://github.com/starverte/flint/pull/164)
- Upgraded to Bootstrap 3.2
- Margin and padding tweaks (no more `#top-pad`)
- Code cleanup
- Global color variables for better consistency

###Flint 1.2.1
For complete diff, check out [Pull Request](https://github.com/starverte/flint/pull/159)
- Significant changes to `flint_get_template()` in order to work properly and not have extraneous code
- WordPress Toolbar doesn't affect page layout (no more hiding of nav menu)
- Right footer content now `text-align: right;`
- Space headers appropriately
- Changed font links from `http://` to `//`

###Flint 1.2.0
For complete diff, check out [Pull Request](https://github.com/starverte/flint/pull/155)
- New Widget Areas: Header, Left, Right (and Footer)
- Minimal template supports new widget areas
- New font: Strait
- Bug fixes

###Flint 1.1.3
For complete diff, check out [Pull Request](https://github.com/starverte/flint/pull/147)
- Fix footer link

###Flint 1.1.2
Alias for Flint 1.1.1 for WordPress.org

###Flint 1.1.1 - March 1, 2014
For complete diff, check out [Pull Request](https://github.com/starverte/flint/pull/141)
- Upgrade to Bootstrap 3.1.1
- Thinner font styles
- Fix override conflict with .widgets.widgets-footer
- Register defaults for custom footer options
- Implement two footer elements
 - Custom Footer Area
 - Site Credits
- New actions!
 - `flint_open_entry_header_404` / `flint_close_entry_header_404`
 - `flint_open_entry_header_$type` / `flint_close_entry_header_$type`
 - `flint_open_cat_title` / `flint_close_cat_title`
 - `flint_open_tag_title` / `flint_close_tag_title`
 - `flint_open_$term_title` / `flint_close_$term_title`
 - `flint_open_archive_title` / `flint_close_archive_title`
 - `flint_entry_meta_above_$term` / `flint_entry_meta_below_$term`


###Flint 1.1.0 - November 20, 2013
For complete diff, check out [Pull Request](https://github.com/starverte/flint/pull/109)
- Upgraded to Bootstrap 3.0.2
- Added templates: Clear, Minimal, Wide, Full, Narrow, Slim
- Added customizer support: change fonts, colors, and more
- Added theme options
 - Custom Footer
 - Featured Images: Show or hide on posts and pages
 - Default page template: Content width, Footer widget area width
 - Clear: Navigation, content width
 - Minimal: Navigation, content width, widget area


###Flint 1.0.5 - October 3, 2013
- Update branding
- Add bottom margin to articles

###Flint 1.0.4 - October 3, 2013
- Add `get_sidebar()` to `front-page.php` to display sidebar on front page
- Change sidebar display name from "Sidebar" to "Footer" for clarity
- Change sidebar functional name from `sidebar-1` to `footer` for clarity

###Flint 1.0.3 - September 23, 2013
- Removed `.hentry { margin: 0 0 6em; }`
- Added spacing and top border to `#comments`

###Flint 1.0.2 - August 27, 2013
- Renamed "font" directory to "fonts" so glyphicon font can work (fixes [#103](https://github.com/starverte/flint/issues/103))
- Fixed footer for small screens (fixes [#101](https://github.com/starverte/flint/issues/101))
- Updated editor-style.css (fixes [#98](https://github.com/starverte/flint/issues/98))

###Flint 1.0.1 - August 24, 2013
- Shipped with Bootstrap 3
- Changed `is_single()` to `is_singular()` for `type-page.php` and `type.php`
- Sidebar no longer shows up if there are not any widgets
- `h1.entry-title` is now slightly larger than `h1`

###Flint 1.0.0 - August 24, 2013
- Shipped with Bootstrap 3 (stable)
- Removed Font Awesome files (weren't used)
- Updated template structure (see issue [#91](https://github.com/starverte/flint/issues/91))

###Flint 0.14.0 - August 18, 2013
- Initial release
- Shipped with Bootstrap 3 RC 2 and Font Awesome 3.2.1
