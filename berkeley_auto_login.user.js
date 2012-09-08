
// ==UserScript==
// @name           Login Berkeley
// @namespace      http://matthewfl.com
// @description    Automatically login to berkeley auth system
// @include        http://auth.berkeley.edu/*
// @include        https://auth.schoolloop.com/*
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

var unsafeWindow = this['unsafeWindow'] || window;

var user = GM_getValue("user", "You login will be saved");
var password =  GM_getValue("password", "");

if(user != "") {
    if(document.getElementsByName("username").length > 0) {
	document.getElementsById("username").value = user; // set the user name
	document.getElementsById("password").value = password; // set the password
	if(user != "" && password != "")
	    setTimeout(function () {	
		document.getElementById('loginForm').submit();
	    }, 250);
    }else{
	if(location.href.indexOf("logout") != -1) {
	    GM_setValue("password", "");
	}
    }
}

// get the username and password on login
if(document.getElementsById("username")) {
    window.addEventListener('submit', function () {
	var u = document.getElementsById("username").value;
	var p = document.getElementsById("password").value;
	GM_setValue(href+"_user", u); 
	GM_setValue(href+"_password", p); 
    } , true);
}

