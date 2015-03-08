<?php 
if(!session_id()) 
{ 
//echo "aa";
// Always executed even if there's already an opened session 
} 

 
if(session_id() == "") 
{ 
session_start(); 
echo "Session_id:";
$a=session_id();
echo $a;
} 
else 
{ 
// Anything you want 
} 
?>
