<?php
session_start();
if(isset($_SESSION['hello']))
     $_SESSION['hello'] = $_SESSION['hello'] + 1;
else
    $_SESSION['hello'] = 1;

echo $_SESSION['hello'];
?>
<?php
//print_r($_COOKIE);
//echo $_COOKIE["file_name"];
?>
