// openads.js
//
// Show ad from openads adserver.

function openads_show_ad(adserver, adzone)
{
     if ( !document.openads_used ) document.openads_used = ',';
     openads_random = new String(Math.random());
     openads_random = openads_random.substring(2,11);

     document.write("<" + "script type='text/javascript' src='");
     document.write(adserver + "/adjs.php?n=" + openads_random);
     document.write("&amp;what=zone:" + adzone);
     document.write("&amp;exclude=" + document.openads_used);
     if (document.referer) document.write("&amp;referer=" + escape(document.referer));
     document.write ("'><" + "/script>");
}

function phpads_show_ad(adserver, adzone)
{
     openads_show_ad(adserver, adzone);
}

