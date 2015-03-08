/* Code editor */

function autoindent(e) {
/*
var nVer = navigator.appVersion;
var nAgt = navigator.userAgent;
var browserName  = navigator.appName;
var fullVersion  = ''+parseFloat(navigator.appVersion); 
var majorVersion = parseInt(navigator.appVersion,10);
var nameOffset,verOffset,ix;

// In MSIE, the true version is after "MSIE" in userAgent
if ((verOffset=nAgt.indexOf("MSIE"))!=-1) {
 browserName = "Microsoft Internet Explorer";
 fullVersion = nAgt.substring(verOffset+5);
}
  if(browserName=="Microsoft Internet Explorer") return true;
  */
  var k = e.keyCode || e.charCode;
  if (k != 13) return true;
  e.preventDefault();
  var range = $(this).getSelection();
  var pos = range.start;
  var ws = $(this).val().substr(0,pos);
  ws = ws.match(/(^|\n)([ ]*)[^\n]*$/);
  ws = ws[2];
  ws = "\n" + ws;
  $(this).replaceSelection(ws);
  $(this).setSelection({pos: pos + ws.length});
}

$(function() {
  $('textarea.autoindent').keypress(autoindent);       //jQuery awesome! ,in the textarea ,class=autoindent ,just let jQuery find it .
});

