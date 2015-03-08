<?php
//Reconfiguration the framework to support the real paralle request,
//just use the apache's paralle essentially . I want to design own 
//paralle architecture with c++ and thread pool ,but it's complicated. 
//With paralle ,every request is isolated. But the identification is 
//the microtime_float,so does it be the same time of two request? 2011.04.01 

 //$filename=date("Y.m.d");
function microtime_float()          //since the Unix Epoch (0:00:00 January 1, 1970 GMT)
{
    list($usec, $sec) = explode(" ", microtime());
    return ((float)$usec + (float)$sec);
}
//use the session as the unique identification of paralle request.
//But ,this will be a problem, during one session ,all the request just be processed by order in the waiting queue.

session_start();
$file=$_POST["cfile"];
$time_start = microtime_float();
$filename=$time_start ;
$full_filename;


if($file==".c"){
 $fp = fopen( "/var/www/exec/$time_start.c", "w" );
 fwrite($fp,$_POST["text"]);
 fclose($fp);
 
//session_start();
$_SESSION['file_name'] = $time_start.".c";


// setcookie("file_name" , $time_start.".c", time() + 20);
 $full_filename = $time_start.".c";
 $fp = fopen( "/var/www/output/stdin.$full_filename", "w" );
 fwrite($fp,stripslashes($_POST["stdin"]));
 fclose($fp);
 }
 
 else if($file==".cpp"){
 $fp = fopen( "/var/www/exec/$time_start.cpp", "w" );
 fwrite($fp,$_POST["text"]);
 fclose($fp);
//session_start();
$_SESSION['file_name'] = $time_start.".cpp";


 $full_filename = $time_start.".cpp";
 
 $fp = fopen( "/var/www/output/stdin.$full_filename", "w" );
 fwrite($fp, stripslashes($_POST["stdin"]));
 fclose($fp);
 }

 
 else if($file==".java"){
 $fp = fopen( "/var/www/exec/$time_start.java", "w" );
 fwrite($fp,$_POST["text"]);
 fclose($fp);
//session_start();
$_SESSION['file_name'] = $time_start.".java";


 $full_filename = $time_start.".java";
 
 $fp = fopen( "/var/www/output/stdin.$full_filename", "w" );
 fwrite($fp, stripslashes($_POST["stdin"]));
 fclose($fp);
 }

else if($file==".go"){
 $fp = fopen( "/var/www/exec/$time_start.go", "w" );
 fwrite($fp,$_POST["text"]);
 fclose($fp);
//session_start();
$_SESSION['file_name'] = $time_start.".go";


 $full_filename = $time_start.".go";
 
 $fp = fopen( "/var/www/output/stdin.$full_filename", "w" );
 fwrite($fp, stripslashes($_POST["stdin"]));
 fclose($fp);
 }
 
 
 else if($file==".py"){
 $fp = fopen( "/var/www/exec/$time_start.py", "w" );
 fwrite($fp,$_POST["text"]);
 fclose($fp);

//session_start();
$_SESSION['file_name'] = $time_start.".py";
 $full_filename = $time_start.".py";
 
 $fp = fopen( "/var/www/output/stdin.$full_filename", "w" );
 fwrite($fp, stripslashes($_POST["stdin"]));
 fclose($fp);
 }
 
 else if($file==".hs"){
 $fp = fopen ("/var/www/exec/$time_start.hs", "w" );
 fwrite($fp,$_POST["text"]);
 fclose($fp);
 
//session_start();
$_SESSION['file_nmae'] = $time_start.".hs";
 $full_filename = $time_start.".hs";
 
 $fp = fopen( "/var/www/output/stdin.$full_filename", "w" );
 fwrite($fp, stripslashes($_POST["stdin"]));
 fclose($fp);
 }
 
 else if($file==".pl"){
 $fp = fopen( "/var/www/exec/$time_start.pl", "w" );
 fwrite($fp,$_POST["text"]);
 fclose($fp);

//session_start();
$_SESSION['file_name'] = $time_start.".pl";
 $full_filename = $time_start.".pl";
 
 $fp = fopen( "/var/www/output/stdin.$full_filename", "w" );
 fwrite($fp, stripslashes($_POST["stdin"]));
 fclose($fp);
 }
  else if($file==".lua"){
 $fp = fopen( "/var/www/exec/$time_start.lua", "w" );
 fwrite($fp,$_POST["text"]);
 fclose($fp);
// session_start();
 $_SESSION['file_name'] = $time_start.".lua"; 
 $full_filename = $time_start.".lua";
 
 $fp = fopen( "/var/www/output/stdin.$full_filename", "w" );
 fwrite($fp, stripslashes($_POST["stdin"]));
 fclose($fp);
 }
 
 
 //Compiler part!
 system("./compiler_module  $full_filename  >> /var/www/log/log.txt");
# system("sleep 2");
 
//sleep(3);                 //ensure change the tmp file ,and the daemon can lock the lockfile ,
  //use the process page replace the sleep();
 if($file==".py")
 header('Location:/output/processpython.html');
 else if( $file==".cpp")
 header('Location:/output/processcpp.html');
 else if($file==".c")
 header('Location:/output/processc.html');
 else if($file==".java")
 header('Location:/output/processjava.html');
  else if($file==".go")
 header('Location:/output/processgo.html');
 else if($file==".hs")
 header('Location:/output/processhaskell.html');
 else if($file==".pl")
 header('Location:/output/processprolog.html');
 else if($file==".lua")
 header('Location:/output/processlua.html');
?>
