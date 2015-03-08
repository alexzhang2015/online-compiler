<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN"> 
<html> 
<head> 

 
<link rel="openid.server" href="http://127.0.0.1/php-openid-2.0.1/examples/server/server.php" />
 
<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1"> 
<link rel="shortcut icon" href="/images/favicon.ico" type="image/x-icon" />
<title>Online Compiler!</title> 
<script type="text/javascript" src="/javascript/jquery.js"></script> 
<script type="text/javascript" src="/javascript/jquery-fieldselection.js"></script> 
<script type="text/javascript" src="/javascript/code-edit.js"></script> 
<script language="JavaScript" type="text/javascript"> 
var default_text="Welcome to Online Compiler!";
var default_text1="upload input (stdin) !";
 
  
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
    
    
}


 

</script> 
</head> 
<body text="#000000" bgcolor="#FFFFFF" topmargin="0" leftmargin="0" rightmargin="0" bottommargin="0" marginheight="0" marginwidth="0" onLoad="document.textform.text.focus();doWarn=1 ;">   <!-- auto choice the textarea when load the page!-->
<form method=post action=submit.php  name="textform" id="textform" > 


<textarea
 <?php 
include_once '/var/www/log/detectbrowser.php';
$TkBrowser=new Browser ;
 
$browser = $TkBrowser->detect(); 
if ($browser['name']!='msie')
  echo 'class="autoindent"';
 ?> 
 cols="100" rows="30" name="text" id="text" style="background-color: #EEE8AA;border: 1px dotted #000000;width:  100%  ;height:79% ;margin: 0px 0px 0px 0px;" onClick="if(document.textform.text.value==default_text)document.textform.text.value=''" onkeydown="return insertTab(event,this);" onkeyup="return insertTab(event,this);" onkeypress="return insertTab(event,this);">Welcome to Online Compiler!</textarea> <br>
<!--
textarea class="autoindent " ,JQuery Autoindent   http://thelackthereof.org/projects/javascript/autoindent/editor-test.html
but it can't support IE well! 
-->

<textarea cols="100" rows="30" name="stdin" id="stdin" style="background-color: #EEE8AA;border: 1px dotted #000000;width:100%; height:60px; margin: 0px 0px 0px 0px;" onClick="if(document.textform.stdin.value==default_text1)document.textform.stdin.value=''" onkeydown="return insertTab(event,this);" onkeyup="return insertTab(event,this);" onkeypress="return insertTab(event,this);">upload input (stdin) !</textarea> <br>

<table width="100%" cellpadding="0" cellspacing="0" style="border-bottom: 1px solid #ccc; margin: 0; width: 100%; padding: 8px 8px 4px 8px;">
<tr>
<td style="text-align: left">
<nobr>
<input type="radio"  name="cfile" value=".c">C  &nbsp&nbsp&nbsp
 
<input type="radio" checked="checked" name="cfile" value=".cpp">C++ &nbsp&nbsp&nbsp
<input type="radio" name="cfile" value=".java">Java &nbsp&nbsp&nbsp
<input type="radio" name="cfile" value=".hs">Haskell &nbsp&nbsp&nbsp 
<input type="radio" name="cfile" value=".lua">Lua &nbsp&nbsp&nbsp 
<input type="radio" name="cfile" value=".pl">Prolog &nbsp&nbsp&nbsp
<input type="radio" name="cfile" value=".py">Python &nbsp&nbsp&nbsp
<input type="radio" name="cfile" value=".go">Go &nbsp&nbsp&nbsp


<input type="submit" name="submit" id="submit" value="Submit"/> 
</nobr>
</td>
<td style="text-align: right"> 
        <nobr> 
          
        
        <span class="menu"><a href="/about">about</a></span> 
        </nobr> 
        </td> 
</tr>
</table>
</form>
<div>
<p style="background-color:Wheat       ;text-align:center">     alex zhang
</p>
</div>

<script>
$('#text').keypress(function(event){
if (event.ctrlKey)
{
	$('#submit').click();
}
}
);
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
