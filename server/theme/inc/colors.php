<?php
/**
 * Functions related to changing colors
 *
 * @package Flint
 * @since 1.3.0
 */

 /**
 * Converts Hex to HSL
 */
function flint_hex_hsl( $HexColor ) {
  $HexColor    = str_replace( '#', '', $HexColor );

  if( strlen( $HexColor ) < 3 ) str_pad( $HexColor, 3 - strlen( $HexColor ), '0' );

  $Add         = strlen( $HexColor ) == 6 ? 2 : 1;
  $AA          = 0;
  $AddOn       = $Add == 1 ? ( $AA = 16 - 1 ) + 1 : 1;

  $Red         = round( ( hexdec( substr( $HexColor, 0, $Add ) ) * $AddOn + $AA ) / 255, 6 );
  $Green       = round( ( hexdec( substr( $HexColor, $Add, $Add ) ) * $AddOn + $AA ) / 255, 6 );
  $Blue        = round( ( hexdec( substr( $HexColor, ( $Add + $Add ) , $Add ) ) * $AddOn + $AA ) / 255, 6 );


  $HSLColor    = array( 'Hue' => 0, 'Saturation' => 0, 'Luminance' => 0 );

  $Minimum     = min( $Red, $Green, $Blue );
  $Maximum     = max( $Red, $Green, $Blue );

  $Chroma      = $Maximum - $Minimum;

  $HSLColor['Luminance'] = ( $Minimum + $Maximum ) / 2;

  if( $Chroma == 0 ) {
    $HSLColor['Luminance'] = round( $HSLColor['Luminance'], 3 );
    return $HSLColor;
  }

  $Range = $Chroma * 6;

  $HSLColor['Saturation'] = $HSLColor['Luminance'] <= 0.5 ? $Chroma / ( $HSLColor['Luminance'] * 2 ) : $Chroma / ( 2 - ( $HSLColor['Luminance'] * 2 ) );

  if( $Red <= 0.004 || $Green <= 0.004 || $Blue <= 0.004 )
    $HSLColor['Saturation'] = 1;

  if( $Maximum == $Red ) { $HSLColor['Hue'] = round( ( $Blue > $Green ? 1 - ( abs( $Green - $Blue ) / $Range ) : ( $Green - $Blue ) / $Range ), 3 ); }
  else if( $Maximum == $Green ) { $HSLColor['Hue'] = round( ( $Red > $Blue ? abs( 1 - ( 4 / 3 ) + ( abs ( $Blue - $Red ) / $Range ) ) : ( 1 / 3 ) + ( $Blue - $Red ) / $Range ), 3 ); }
  else { $HSLColor['Hue'] = round( ( $Green < $Red ? 1 - 2 / 3 + abs( $Red - $Green ) / $Range : 2 / 3 + ( $Red - $Green ) / $Range ), 3 ); }

  $HSLColor['Saturation'] = round( $HSLColor['Saturation'], 3 );
  $HSLColor['Luminance']  = round( $HSLColor['Luminance'], 3 );

  return $HSLColor;
}

/**
 * Converts HSL to Hex
 */
function flint_hsl_hex( $Hue = 0, $Saturation = 0, $Luminance = 0 ) {

  $HSLColor    = array( 'Hue' => $Hue, 'Saturation' => $Saturation, 'Luminance' => $Luminance );
  $RGBColor    = array( 'Red' => 0, 'Green' => 0, 'Blue' => 0 );


  foreach( $HSLColor as $Name => $Value ) {
    if( is_string( $Value ) && strpos( $Value, '%' ) !== false )
      $Value = round( round( (int)str_replace( '%', '', $Value ) / 100, 2 ) * 255, 0 );

    else if( is_float( $Value ) )
      $Value = round( $Value * 255, 0 );

    $Value    = (int)$Value * 1;
    $Value    = $Value > 255 ? 255 : ( $Value < 0 ? 0 : $Value );
    $ValuePct = round( $Value / 255, 6 );

    ${'the_'.$Name} = $ValuePct;
  }

  $RGBColor['Red']   = $the_Luminance;
  $RGBColor['Green'] = $the_Luminance;
  $RGBColor['Blue']  = $the_Luminance;

  $Radial  = $the_Luminance <= 0.5 ? $the_Luminance * ( 1.0 + $the_Saturation ) : $the_Luminance + $the_Saturation - ( $the_Luminance * $the_Saturation );

  if( $Radial > 0 ) {
    $Ma   = $the_Luminance + ( $the_Luminance - $Radial );
    $Sv   = round( ( $Radial - $Ma ) / $Radial, 6 );
    $Th   = $the_Hue * 6;
    $Wg   = floor( $Th );
    $Fr   = $Th - $Wg;
    $Vs   = $Radial * $Sv * $Fr;
    $Mb   = $Ma + $Vs;
    $Mc   = $Radial - $Vs;

    if ($Wg == 1) {
      $RGBColor['Red']   = $Mc;
      $RGBColor['Green'] = $Radial;
      $RGBColor['Blue']  = $Ma;
    }
    else if( $Wg == 2 ) {
      $RGBColor['Red']   = $Ma;
      $RGBColor['Green'] = $Radial;
      $RGBColor['Blue']  = $Mb;
    }
    else if( $Wg == 3 ) {
      $RGBColor['Red']   = $Ma;
      $RGBColor['Green'] = $Mc;
      $RGBColor['Blue']  = $Radial;
    }
    else if( $Wg == 4 ) {
      $RGBColor['Red']   = $Mb;
      $RGBColor['Green'] = $Ma;
      $RGBColor['Blue']  = $Radial;
    }
    else if( $Wg == 5 ) {
      $RGBColor['Red']   = $Radial;
      $RGBColor['Green'] = $Ma;
      $RGBColor['Blue']  = $Mc;
    }
    else {
      $RGBColor['Red']   = $Radial;
      $RGBColor['Green'] = $Mb;
      $RGBColor['Blue']  = $Ma;
    }
  }

  $RGBColor['Red']   = ($C = round( $RGBColor['Red'] * 255, 0 )) < 15 ? '0'.dechex( $C ) : dechex( $C );
  $RGBColor['Green'] = ($C = round( $RGBColor['Green'] * 255, 0 )) < 15 ? '0'.dechex( $C ) : dechex( $C );
  $RGBColor['Blue']  = ($C = round( $RGBColor['Blue'] * 255, 0 )) < 15 ? '0'.dechex( $C ) : dechex( $C );

  return $RGBColor;
}

/**
 * Darkens Hex color by defined percentage
 */
function flint_darken( $HexColor, $percent ) {
  $HSLColor = flint_hex_hsl($HexColor);
  $HSLColor['Luminance'] = $HSLColor['Luminance'] - ($percent/100);
  $HSLColor['Luminance'] = $HSLColor['Luminance'] < 0 ? 0 : $HSLColor['Luminance'];
  $RGBColor = flint_hsl_hex($HSLColor['Hue'],$HSLColor['Saturation'],$HSLColor['Luminance']);
  return '#' . $RGBColor['Red'].$RGBColor['Green'].$RGBColor['Blue'];
}

/**
 * Lightens Hex color by defined percentage
 */
function flint_lighten( $HexColor, $percent ) {
  $HSLColor = flint_hex_hsl($HexColor);
  $HSLColor['Luminance'] = $HSLColor['Luminance'] + ($percent/100);
  $HSLColor['Luminance'] = $HSLColor['Luminance'] < 0 ? 0 : $HSLColor['Luminance'];
  $RGBColor = flint_hsl_hex($HSLColor['Hue'],$HSLColor['Saturation'],$HSLColor['Luminance']);
  return '#' . $RGBColor['Red'].$RGBColor['Green'].$RGBColor['Blue'];
}

?>
