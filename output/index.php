<?php
//Open the session before the headers send,or will be wrong.
//Wrong info: Cannot send session cache limiter - headers already send.
session_start();
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"
  "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd"> 
<html xmlns="http://www.w3.org/1999/xhtml"> 
 
<head> 
 
    <meta http-equiv="content-type" content="text/html; charset=UTF-8"> 
    <META HTTP-EQUIV="Pragma" CONTENT="no-cache"> 
    <META HTTP-EQUIV="Expires" CONTENT="-1"> 
<link rel="shortcut icon" href="/images/favicon.ico" type="image/x-icon" />
    <title>Output Compiler!</title> 
 
    
<script type="text/javascript" src="/javascript/jquery.js"></script> 
<script type="text/javascript" src="/javascript/jquery-fieldselection.js"></script> 
<script type="text/javascript" src="/javascript/code-edit.js"></script> 
 <script language="JavaScript" type="text/javascript"> 
var default_text="Welcome to Online Compiler!";
var default_text1="upload input (stdin) !";
function alertDefaultValue()
  {
  var filename=document.getElementById('tmpname').defaultValue;
  var path="/exec/";
  var down=path+filename;
 // alert(down);
  window.location=down;
  }

function insertTab(event,obj) {
    var tabKeyCode = 9;
    if (event.which) // mozilla
        var keycode = event.which;
    else // ie
        var keycode = event.keyCode;
    if (keycode == tabKeyCode) {
        if (event.type == "keydown") {
            if (obj.setSelectionRange) {
                // mozilla
                var s = obj.selectionStart;
                var e = obj.selectionEnd;
                obj.value = obj.value.substring(0, s) + 
                    "\t" + obj.value.substr(e);
                obj.setSelectionRange(s + 1, s + 1);
                obj.focus();
            } else if (obj.createTextRange) {
                // ie
                document.selection.createRange().text="\t"
                obj.onblur = function() { this.focus(); this.onblur = null; };
            } else {
                // unsupported browsers
            }
        }
        if (event.returnValue) // ie ?
            event.returnValue = false;
        if (event.preventDefault) // dom
            event.preventDefault();
        return false; // should work in all browsers
    }
    return true;
}</script> 
</head> 
<body text="#000000" bgcolor="#FFFFFF" topmargin="0" leftmargin="0" rightmargin="0" bottommargin="0" marginheight="0" marginwidth="0" doWarn=1  style=" width:100%   "> 
  
 <table  cellpadding="0" cellspacing="0" style="border-bottom: 1px solid #ccc; margin: 0; width: 100%; padding: 8px 8px 4px 8px; "><tr> 
        <td style="text-align: left ;width= 100%  ;"> 
        <span class="logo"><a href="/"><img src="/images/cooltext443682926.png" alt="Logo"></a></span> 
        
        </td> 
        <td style="text-align: right ;width= 100%  ;"> 
        <nobr> 
          
        <font size="6" face="Times" color="green">
        <span class="menu"><a href="/about">about</a></span> </font>
        </nobr> 
        </td> 
        <div style="margin: 8px 8px 8px 8px"> 
 </table>
       
        

 
 <span class="heading"> <a name="entry" > source code :         </a></span> 
<input type="button" onclick="alertDefaultValue()" 
value="Download&Save" />
<textarea rows="1" cols="0"     style="visibility:hidden ;width= 100%  ;" name="tmpname" id="tmpname"  >
<?php               //this senmence must be left ,or the textarea may has the  whitespace,looks Ugly!
//session_start();
$data = $_SESSION['file_name'];
echo $data;
?>
</textarea>
	<table border="0" cellpadding="10" cellspacing="0"   width="100%" > 
	<tr> 
	<td style="border-right: 1px  solid #ccc; text-align:  right; vertical-align: top"> 
	 
	</td> 
	<td width="100%"  style="vertical-align: top ;width=100% ;"> 
	 
	<pre> 
<?php
	include_once '/var/www/geshi/geshi.php';  
	$data = $_SESSION['file_name'];
	$lines=file_get_contents("/var/www/exec/$data");
	if($lines!=NULL)
	{
	$source = $lines;
	$language = 'c ';
	$geshi = new GeSHi($source, $language);
 	$geshi->enable_line_numbers(GESHI_FANCY_LINE_NUMBERS,37);
 	echo $geshi->parse_code();
 	}
 	?>
 	</pre> 
	  
	</td></tr>  
	 
	</table>
	
	<br/><br/> 
	<a name="output"><span class="heading"> Output:</span></a> 
	<div class="code"> 
	<table border="0" cellpadding="10" cellspacing="0"   width="100%"> 
	<tr> 
	<td style="border-right: 1px  solid #ccc; text-align:  right; vertical-align: top ;width=100% ;"> 
	<div class="highlight">  
	</div> 
	</td> 
	<td width="100%" style="vertical-align: top ;width=100% ;"> 
	<div class="highlight"1> 
	<pre> 
<?php
	include_once '/var/www/geshi/geshi.php';
	$data;
	$datetmp;

	
	
	
/*	$lines=file_get_contents("/var/www/output/out.txt");
	if($lines!=NULL)
	{
	$source = $lines;
	$language = 'c ';
	$geshi = new GeSHi($source, $language);
 	$geshi->enable_line_numbers(GESHI_NORMAL_LINE_NUMBERS);
 	echo $geshi->parse_code();
 	}
*/ 
 	$LimitLine=5000;         //set the outline limit ! very important !not for me ,just for the use.
 	$LineInit=0;

      //  session_start();
	$file_name = $_SESSION['file_name'];
       // echo $file_name;
        $handle = fopen("/var/www/output/out.$file_name", "r");
	if ($handle) {
	
	 
    	while (!feof($handle)) {
    	
    	 
       	 $data    =fgets($handle, 4096);
       	 if($LineInit<$LimitLine)
       	 {
       	 $datatmp.=$data;
       	 }
       	 //echo $data; 
       	 $LineInit++;
       	 //echo $LineInit;
       	 
   	  
   	 }
    	fclose($handle);
	}
	if($datatmp!=NULL)
	{
	$stringlength=strlen($datatmp);
	//echo  $datatmp[ $stringlength-1];         //if the last sentence  has "\n" ,just ingore it !
	if($datatmp[  $stringlength -1]=="\n")
	{
		$datatmp[$stringlength-1]="";
	}
	//limit the row length!
	$source = substr($datatmp,0,2000);            

	$language = 'c ';
	$geshi = new GeSHi($source, $language);
 	$geshi->enable_line_numbers(GESHI_NORMAL_LINE_NUMBERS);
 	echo $geshi->parse_code();
 	}
	
	


	$lines=file_get_contents("/var/www/output/wrong.$file_name");
	if ($lines!=NULL)
	{
	$stringlengt=strlen($lines);
	//echo  $lines[ $stringlengt-1];         //if the last sentence  has "\n" ,just ingore it !
	if($lines[  $stringlengt -1]=="\n")
	{
		$lines[$stringlengt-1]="";
	}
	
	$source = $lines;
	$language = 'c ';
	$geshi = new GeSHi($source, $language);
 	$geshi->enable_line_numbers(GESHI_NORMAL_LINE_NUMBERS);
 	echo $geshi->parse_code();	
	}
	
/*	$handle2 = fopen("/var/www/output/wrong", "r");
	if ($handle2) {
    	while (!feof($handle2)) {
       	 $data = fgets($handle2, 4096);
       	 echo $data; 
       	 
   	 }
    	fclose($handle2);
	}
*/	
	
	

	
    ?>
        
	</pre> 
	</div> 
	</td></tr></table> 
	</div> 
 
	</td> 
	</tr> 
	</table> 
	
	<br><br>
	<a name="output"><span class="heading"></span></a> 
	<div class="code"> 
	<table cellpadding="10"    width="100%"> 
	 
    	 
    	 
        <?php
	//	session_start();
		$file_name = $_SESSION['file_name'];
         $lines=file_get_contents("/var/www/output/runtime.$file_name");
         $data=file_get_contents("/var/www/output/compilertime.$file_name");
         $wrong=file_get_contents("/var/www/output/wrong.$file_name");
         $momery=file_get_contents("/var/www/output/momery.$file_name");
        if( $lines==NULL){
            if($wrong==NULL)
        	echo "Time Out!";
            //if($wrong!=NULL)
        	//compiler wrong!
        }
        else{
         
       	 echo  	 $data;
       	  
       	 echo "<br>";
       	  
       	 
       	 if($wrong==NULL)
	{
       	    echo   $lines;
       	    echo "<br>";
	    echo   $momery;
	}
       	 }   
    	?>
    	 
    	 
    	</table> 
    	<div style="margin: 8px 8px 8px 8px"> 
        <br/><br/> 
	
<br/> 
 
  <div 
   class="editor"
   id="editor"
  > 
  <form action="../submit.php" method="post" name="textform" id="textform" > 
  <table cellpadding="10" width="1%" > 
 
  <tr> 
    <td style="vertical-align: top"><span style="vertical-align:middle" >Language:</span> 
    <select style="vertical-align:middle" name="cfile" id="cfile"> 
    <option value=".c"   <?php  if ($_GET["filetype"]=="c") echo "selected";  ?> >C</option> 
    <option value=".cpp"  <?php  if ($_GET["filetype"]=="cpp") echo "selected";  ?>   >C++</option> 
    <option value=".java"  <?php  if ($_GET["filetype"]=="java") echo "selected";  ?>   >Java</option> 
    <option value=".hs" <?php  if ($_GET["filetype"]=="haskell") echo "selected";  ?> >Haskell</option> 
     <option value=".lua" <?php  if ($_GET["filetype"]=="lua") echo "selected";  ?> >Lua</option>
    <option value=".pl" <?php  if ($_GET["filetype"]=="prolog") echo "selected";  ?> >Prolog</option> 
     <option value=".py" <?php  if ($_GET["filetype"]=="python") echo "selected";  ?> >Python</option>
     <option value=".go" <?php  if ($_GET["filetype"]=="go") echo "selected";  ?> >Go</option>
    </select> 
    </td></tr>
    <tr> 
    <td style="vertical-align: middle">   <!--   //class="autoindent"   add this to support auto indent   -->
<textarea <?php 
include_once '/var/www/log/detectbrowser.php';
$TkBrowser=new Browser ;
 
$browser = $TkBrowser->detect(); 
if ($browser['name']!='msie')
  echo 'class="autoindent"';
 ?> 
   cols="120" rows="25" name="text" id="text" style="background-color: #EEE8AA;border: 1px dotted #000000;  margin: 0px 0px 0px 0px;" 
     onkeydown="return insertTab(event,this);" onkeyup="return insertTab(event,this);" onkeypress="return insertTab(event,this);"
wrap="off"><?php               //this senmence must be left ,or the textarea may has the  whitespace,looks Ugly!
    	$i='0';          
	$data;
      //  session_start(); 
	$file_name = $_SESSION['file_name'];
	$handle = @fopen("/var/www/exec/$file_name", "r");
	if ($handle) {
	while (!feof($handle)) {
	  
       	 	$data =fgets($handle, 4096);
       	 	echo $data;
       	 	 
       	 }
       	 fclose($handle);
       	 }
       	 
       	
    	flush();
    	 
        ?></textarea></td> 
  </tr> 
  <tr> 
    <td style="vertical-align: middle">
    <textarea  cols="120" rows="15" name="stdin" id="stdin" style="background-color: #EEE8AA;border: 1px dotted #000000;height:40px; margin: 0px 0px 0px 0px;" onClick="if(document.textform.stdin.value==default_text1)document.textform.stdin.value='' "; onkeydown="return insertTab(event,this);" onkeyup="return insertTab(event,this);" onkeypress="return insertTab(event,this);">
<?php
//	session_start();
	$file_name = $_SESSION['file_name'];
	$handle = @fopen("/var/www/output/stdin.$file_name", "r");
	if ($handle) {
	while (!feof($handle)) {
	  
       	 	$data =fgets($handle, 4096);
       	 	echo $data;
       	 	 
       	 }
       	 fclose($handle);
       	 }

 //Unset the _SESSION['lock'] ,release the same session request lock.
 // 	unset($_SESSION['lock']);
session_destroy();
 	?></textarea></td> 
  </tr> 
  
   <tr> 
    <td colspan="2" style="vertical-align: middle; text-align: right"> 
         <table cellspacing="0" cellpadding="0" width="100%" > 
<tr>
     
      
      <td style="text-align: right"> 
      <input type="submit" name="submit" id="submit" value="Submit"/> 
      </td> 
      </tr></table> 
       
       
    
    </td> 
  </tr> 
  </table> 
  </form> 
  </div> 
  
  <p style="background-color:Wheat       ;text-align:center">   alex zhang
</p>


<script>
$('#text').keypress(function(event){
if (event.ctrlKey)
{
	$('#submit').click();
}
}
);
</script>


  <script type="text/javascript" charset="utf-8">
  var is_ssl = ("https:" == document.location.protocol);
  var asset_host = is_ssl ? "https://s3.amazonaws.com/getsatisfaction.com/" : "http://s3.amazonaws.com/getsatisfaction.com/";
  document.write(unescape("%3Cscript src='" + asset_host + "javascripts/feedback-v2.js' type='text/javascript'%3E%3C/script%3E"));
</script>

<script type="text/javascript" charset="utf-8">
  var feedback_widget_options = {};

  feedback_widget_options.display = "overlay";  
  feedback_widget_options.company = "alexzhang";
  feedback_widget_options.placement = "right";
  feedback_widget_options.color = "#222";
  feedback_widget_options.style = "idea";
  
  
  
  
  
  

  var feedback_widget = new GSFN.feedback_widget(feedback_widget_options);
</script>

<script type="text/javascript">
var gaJsHost = (("https:" == document.location.protocol) ? "https://ssl." : "http://www.");
document.write(unescape("%3Cscript src='" + gaJsHost + "google-analytics.com/ga.js' type='text/javascript'%3E%3C/script%3E"));
</script>
<script type="text/javascript">
try {
var pageTracker = _gat._getTracker("UA-10642680-1");
pageTracker._trackPageview();
} catch(err) {}</script>
 </body> 
</html> 
