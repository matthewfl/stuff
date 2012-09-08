
// ==UserScript==
// @name           Wlan Login Berkeley
// @namespace      http://matthewfl.com
// @description    Automatically login to berkeley Wireless system
// @include        *
// ==/UserScript==


// stuff to make it work in chrome
if (typeof GM_log == 'undefined') {

    function GM_addStyle(css) {
	var style = document.createElement('style');
	style.textContent = css;
	document.getElementsByTagName('head')[0].appendChild(style);
    }
    
    function GM_deleteValue(name) {
	localStorage.removeItem(name);
    }
    
    function GM_getValue(name, defaultValue) {
	return localStorage.getItem(name) || defaultValue;
    }
    
    function GM_log(message) {
	console.log(message);
    }
    
    function GM_setValue(name, value) {
	localStorage.setItem(name, value);
    }
}

var url_to_check = "matthewfl.com/berkeley-wlan.html";
var unsafeWindow = this['unsafeWindow'] || window;

if(location.href.indexOf("wlan.berkeley.edu") != -1) {
    if(location.href.indexOf("cookie.cgi") != -1)
    else if(location.href.indexOf("login") != -1)
	document.forms[0].submit.click();
}


if(GM_getValue("running_check", false)) {
    if(location.href.indexOf(url_to_check) != -1)
	GM_setValue("running_check", false);
}

function check () {
    var now = new Date;
    if(now - new Date(GM_getValue("last_check", now)) > 20000) {
	// if the time since the last time this loop ran was greater than 20 seconds
	// esentally if the computer has been put to sleep or was turned off for some time
	// this is copied from an article by google on how gmail auto rechecks for mail when a computer is turned back on
	GM_setValue("running_check", true);
	var frame = document.createElement("iframe");
	frame.src = "http://" + url_to_check;
	frame.style.display = 'none';
	document.body.appendChild(frame);
	//GM_openInTab("http://" + url_to_check); // set to some url that will have some constant value that can be the result
    }
    GM_setValue("last_check", now);
}

check(); // we want to also check when the system is started
setInterval(check, 10000);
