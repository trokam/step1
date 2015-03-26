<?php
/**
 * The template used for displaying custom post type content
 *
 * @package Flint
 * @since 1.3.0
 */
?>

  <div class="row">
    <?php flint_get_spacer('left'); ?>
    <article id="post-<?php the_ID(); ?>" <?php flint_post_class(); ?>>
      <header class="entry-header">
        <?php $type = get_post_type(); ?>
        <?php do_action('flint_open_entry_header_'.$type); ?>

        <h1 class="entry-title"><?php if (is_singular()) { echo the_title(); } else { echo '<a href="' . get_permalink() .'" rel="bookmark">' . get_the_title() . '</a>'; } ?></h1>
        <?php if ( current_user_can('edit_posts') ) { ?><a class="btn btn-default btn-sm btn-edit hidden-xs" href="<?php echo get_edit_post_link(); ?>">Edit</a><?php } ?>

        <div class="entry-meta">
          <?php do_action('flint_entry_meta_above_'.$type); ?>
        </div><!-- .entry-meta -->

        <?php do_action('flint_close_entry_header_'.$type); ?>

        <script src="http://code.jquery.com/jquery-1.11.2.min.js">
        </script>

        <script>
            $(document).ready(
                function()
                {
                    /***************************************************
                     * Install the function to be called when the
                     * button 'audit' is clicked.
                     ***************************************************/
                    function install_button_handler()
                    {
                        console.log("installing button handler");
                        $(".audit").click(audit_on_server);
                    }

                    /***************************************************
                   * The funtion called when the button 'audit'
                   * is clicked.
                   ***************************************************/
                    function audit_on_server(event)
                    {
                        console.log("click on button audit");
                        console.log("button property: " + event.target.name);
                        var url_index= event.target.name;
    
                        document.getElementById("search_block").style.display='none';

                        var html_block= "<em>Retrieving data ...</em>";
                        document.getElementById("audit_results").innerHTML= html_block;

                        $.post("/proc/lookfor",
                                {
                                    audit: url_index
                                },
                                function(data, status)
                                {
                                    if (status == "success")
                                    {
                                        var html_block= "<pre>" + data + "</pre>";
                                        document.getElementById("audit_results").innerHTML= html_block;
                                        document.getElementById("back_to_results").style.display='block';
                                    }
                                });

                        console.log("end button audit");
                    }

                    /***************************************************
                   * The funtion called when the button 'search'
                   * is clicked.
                   ***************************************************/
                    function search_on_server(event)
                    {
                        console.log("click on button search");
                        
                        words = document.getElementById("search_box").value;
                        if (typeof(words) == 'undefined')
                        {
                            return;
                        }

                        words= words.trim();
                        
                        if(words == "")
                        {
                            console.log("empty string");
                            return;
                        }

                        var html_block= "<em>Searching ...</em>";
                        document.getElementById("search_results").innerHTML= html_block;

                        $.post("/proc/lookfor",
                                {
                                    search: words
                                },
                                function(data, status)
                                {
                                    if (status == "success")
                                    {
                                        if (data == "")
                                        {
                                            var no_results_message= "&nbsp;<br/><em>Well, this an ongoing project!<br/>";
                                            no_results_message+= "No results by now.</em>";
                                            document.getElementById("search_results").innerHTML= no_results_message;
                                        }
                                        else
                                        {
                                            document.getElementById("search_results").innerHTML= data;
                                        }
                                    }
                                });

                        setTimeout(install_button_handler, 5000);
                        console.log("end button search");
                    }

                    /***************************************************
                   * The funtion called when a key is pressed in the 
                   * search box.
                   ***************************************************/
                    function review_input(event)
                    {
                        if(event.key == "Enter")
                        {
                            search_on_server();
                        }
                    }

                    $("#back_to_results").click(function()
                                                {
                                                    document.getElementById("audit_results").innerHTML= "";
                                                    document.getElementById("back_to_results").style.display='none';
                                                    document.getElementById("search_block").style.display='block';
                                                });
            
                    $("#search_box").keypress(review_input);
                    
                    $("#search").click(search_on_server);
                                            
                    $("#clean").click( function()
                                       {
                                            console.log("click on button clean");
                                            document.getElementById("search_results").innerHTML= "";
                                            document.getElementById("search_box").value= "";
                                        });
                                        
                    // $(".audit").click(audit_on_server);         
                    
                    console.log("Document ready");
                }
            );
        </script>

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

      <footer class="entry-meta clearfix">
      <?php do_action('flint_entry_meta_below_'.$type); ?>
      </footer><!-- .entry-meta -->

    </article><!-- #post-<?php the_ID(); ?> -->
    <?php flint_get_spacer('right'); ?>
  </div><!-- .row -->
