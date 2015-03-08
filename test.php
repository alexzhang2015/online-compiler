<?php
 //$filename=date("Y.m.d");
/*function microtime_float()          //since the Unix Epoch (0:00:00 January 1, 1970 GMT)
{
    list($usec, $sec) = explode(" ", microtime());
    return ((float)$usec + (float)$sec);
}
$file=$_POST["cfile"];
$time_start = microtime_float();
$filename=(string)$time_start + (string)".c";
 
 if($file==".c"){
 
 echo "hello it's c";
 }
 
 if($file==".cpp"){
 
 echo "hello it's c++";
 }
 echo $_POST["cfile"];
 echo $_POST["text"];
 
 echo $_POST["submit"];
 /*$fp = fopen( "/var/www/test", "w" );
 fwrite($fp,stripslashes($_POST["text"]));
 fclose($fp);
 
 	$handle2 = fopen("/var/www/test", "r");
	if ($handle2) {
    	while (!feof($handle2)) {
       	 $data = fgets($handle2, 4096);
       	 echo $data;
 */
 
 

$fp = fopen("lock", "r+");

if (flock($fp, LOCK_EX)) { // do an exclusive lock
    ftruncate($fp, 0); // truncate file
    fwrite($fp, "Write something here\n");
    sleep(5);
    flock($fp, LOCK_UN); // release the lock
} else {
    echo "Couldn't get the lock!";
}

echo "over lock!";
fclose($fp);

 
 ?>
