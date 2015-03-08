<?php
//
// Include the GeSHi library
//
include_once 'geshi.php';
 
//
// Define some source to highlight, a language to use
// and the path to the language files
//
$lines=file_get_contents("test");
 
echo $lines;
$source = $lines;
$language = 'cpp ';
 
//
// Create a GeSHi object
//
 
$geshi = new GeSHi($source, $language);
 $geshi->enable_line_numbers(GESHI_FANCY_LINE_NUMBERS,37);
//
// And echo the result!
//
echo $geshi->parse_code();
?>
