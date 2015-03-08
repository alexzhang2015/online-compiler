<?php
 //$filename=date("Y.m.d");
function microtime_float()          //since the Unix Epoch (0:00:00 January 1, 1970 GMT)
{
    list($usec, $sec) = explode(" ", microtime());
    return ((float)$usec + (float)$sec);
}
$file=$_POST["cfile"];
$time_start = microtime_float();
$filename=$time_start ;
if($file==".c"){
 $fp = fopen( "/var/www/exec/$time_start.c", "w" );
 fwrite($fp,stripslashes($_POST["text"]));
 fclose($fp);
 
 $fp = fopen( "/var/www/tmp", "w" );
 fwrite($fp,$filename);
 fwrite($fp,".c");
 fclose($fp);
 }
 
 if($file==".c++"){
 $fp = fopen( "/var/www/exec/$time_start.cpp", "w" );
 fwrite($fp,stripslashes($_POST["text"]));
 fclose($fp);
 
 $fp = fopen( "/var/www/tmp", "w" );
 fwrite($fp,$filename);
 fwrite($fp,".cpp");
 fclose($fp);
 }
 


 header('Location: http://127.0.0.1/output');
?>
