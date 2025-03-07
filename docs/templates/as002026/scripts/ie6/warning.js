/*******************************************************************************************/
/*
/*		This template may have been modified pursuant to the GNU General Public License,
/*		and as distributed it includes or is derivative of works licensed under 
/*		the GNU General Public License or other free or open source software licenses.
/*
/*		Designed by 'AS Designing'
/*		Web: http://www.asdesigning.com
/*		Email: info@asdesigning.com
/*
/*******************************************************************************************/

var msg1 = "Did you know that your Internet Explorer is out of date?";
var msg2 = "To get the best possible experience using our website we recommend that you upgrade to a newer version or other web browser. A list of the most popular web browsers can be found below.";
var msg3 = "Just click on the icons to get to the download page";
var br1 = "Internet Explorer 7+";
var br2 = "Firefox 3+";
var br3 = "Safari 3+";
var br4 = "Opera 9.5+";
var br5 = "Chrome 2.0+";
var url1 = "http://www.microsoft.com/windows/Internet-explorer/default.aspx";
var url2 = "http://www.mozilla.com/firefox/";
var url3 = "http://www.apple.com/safari/download/";
var url4 = "http://www.opera.com/download/";
var url5 = "http://www.google.com/chrome";
var imgPath;

function e(str) 
{
	imgPath = str;
	var _body = document.getElementsByTagName('body')[0];
	var _d = document.createElement('div');
	var _l = document.createElement('div');
	var _h = document.createElement('h1');
	var _p1 = document.createElement('p');
	var _p2 = document.createElement('p');
	var _ul = document.createElement('ul');
	var _li1 = document.createElement('li');
	var _li2 = document.createElement('li');
	var _li3 = document.createElement('li');
	var _li4 = document.createElement('li');
	var _li5 = document.createElement('li');
	var _ico1 = document.createElement('div');
	var _ico2 = document.createElement('div');
	var _ico3 = document.createElement('div');
	var _ico4 = document.createElement('div');
	var _ico5 = document.createElement('div');
	var _lit1 = document.createElement('div');
	var _lit2 = document.createElement('div');
	var _lit3 = document.createElement('div');
	var _lit4 = document.createElement('div');
	var _lit5 = document.createElement('div');
	
	_body.appendChild(_l);
	_body.appendChild(_d);
	_d.appendChild(_h);
	_d.appendChild(_p1);
	_d.appendChild(_p2);
	_d.appendChild(_ul);
	_ul.appendChild(_li1);
	_ul.appendChild(_li2);
	_ul.appendChild(_li3);
	_ul.appendChild(_li4);
	_ul.appendChild(_li5);
	_li1.appendChild(_ico1);
	_li2.appendChild(_ico2);
	_li3.appendChild(_ico3);
	_li4.appendChild(_ico4);
	_li5.appendChild(_ico5);
	_li1.appendChild(_lit1);
	_li2.appendChild(_lit2);
	_li3.appendChild(_lit3);
	_li4.appendChild(_lit4);
	_li5.appendChild(_lit5);
	_d.setAttribute('id','_d');
	_l.setAttribute('id','_l');
	_h.setAttribute('id','_h');
	_p1.setAttribute('id','_p1');
	_p2.setAttribute('id','_p2');
	_ul.setAttribute('id','_ul');
	_li1.setAttribute('id','_li1');
	_li2.setAttribute('id','_li2');
	_li3.setAttribute('id','_li3');
	_li4.setAttribute('id','_li4');
	_li5.setAttribute('id','_li5');
	_ico1.setAttribute('id','_ico1');
	_ico2.setAttribute('id','_ico2');
	_ico3.setAttribute('id','_ico3');
	_ico4.setAttribute('id','_ico4');
	_ico5.setAttribute('id','_ico5');
	_lit1.setAttribute('id','_lit1');
	_lit2.setAttribute('id','_lit2');
	_lit3.setAttribute('id','_lit3');
	_lit4.setAttribute('id','_lit4');
	_lit5.setAttribute('id','_lit5');
	
	var _width = document.documentElement.clientWidth;
	var _height = document.documentElement.clientHeight;
	var _dl = document.getElementById('_l');
	
	_dl.style.width =  _width+"px";
	_dl.style.height = _height+"px";
	_dl.style.position = "absolute";
	_dl.style.top = "0px";
	_dl.style.left = "0px";
	_dl.style.filter = "alpha(opacity=50)";
	_dl.style.background = "#fff";
	
	var _dd = document.getElementById('_d');
	
	_ddw = 650;_ddh = 260;
	_dd.style.width = _ddw+"px";
	_dd.style.height = _ddh+"px";
	_dd.style.position = "absolute";
	_dd.style.top = ((_height-_ddh)/2)+"px";
	_dd.style.left = ((_width-_ddw)/2)+"px";
	_dd.style.padding = "20px";
	_dd.style.background = "#fff";
	_dd.style.border = "1px solid #ccc";
	_dd.style.fontFamily = "'Lucida Grande','Lucida Sans Unicode',Arial,Verdana,sans-serif";
	_dd.style.listStyleType = "none";
	_dd.style.color = "#4F4F4F";
	_dd.style.fontSize = "12px";
	_h.appendChild(document.createTextNode(msg1));
	
	var _hd = document.getElementById('_h');
	
	_hd.style.display = "block";
	_hd.style.fontSize = "1.3em";
	_hd.style.marginBottom = "0.5em";
	_hd.style.color = "#333";
	_hd.style.fontFamily = "Helvetica,Arial,sans-serif";
	_hd.style.fontWeight = "bold";
	_p1.appendChild(document.createTextNode(msg2));
	
	var _p1d = document.getElementById('_p1');
	
	_p1d.style.marginBottom = "1em";_p2.appendChild(document.createTextNode(msg3));
	
	var _p2d = document.getElementById('_p2');
	
	_p2d.style.marginBottom = "1em";
	
	var _uld = document.getElementById('_ul');
	
	_uld.style.listStyleImage = "none";
	_uld.style.listStylePosition = "outside";
	_uld.style.listStyleType = "none";
	_uld.style.margin = "0 px auto";
	_uld.style.padding = "0px";
	_uld.style.paddingLeft = "10px";
	
	var _li1d = document.getElementById('_li1');
	var _li2d = document.getElementById('_li2');
	var _li3d = document.getElementById('_li3');
	var _li4d = document.getElementById('_li4');
	var _li5d = document.getElementById('_li5');
	var _li1ds = _li1d.style;
	var _li2ds = _li2d.style;
	var _li3ds = _li3d.style;
	var _li4ds = _li4d.style;
	var _li5ds = _li5d.style;
	
	_li1ds.background = _li2ds.background = _li3ds.background = _li4ds.background = _li5ds.background = "transparent url('"+imgPath+"background_browser.gif') no-repeat scroll left top";
	_li1ds.cursor = _li2ds.cursor = _li3ds.cursor = _li4ds.cursor = _li5ds.cursor = "pointer";
	_li1d.onclick = function() {window.location = url1 }; 
	_li2d.onclick = function() {window.location = url2 };
	_li3d.onclick = function() {window.location = url3 }; 
	_li4d.onclick = function() {window.location = url4 }; 
	_li5d.onclick = function() {window.location = url5 }; 
	_li1ds.styleFloat = _li2ds.styleFloat = _li3ds.styleFloat = _li4ds.styleFloat = _li5ds.styleFloat = "left";
	_li1ds.width = _li2ds.width = _li3ds.width = _li4ds.width = _li5ds.width = "120px";
	_li1ds.height = _li2ds.height = _li3ds.height = _li4ds.height = _li5ds.height = "122px";
	_li1ds.margin = _li2ds.margin = _li3ds.margin = _li4ds.margin = _li5ds.margin = "0 10px 10px 0";
	
	var _ico1d = document.getElementById('_ico1');
	var _ico2d = document.getElementById('_ico2');
	var _ico3d = document.getElementById('_ico3');
	var _ico4d = document.getElementById('_ico4');
	var _ico5d = document.getElementById('_ico5');
	var _ico1ds = _ico1d.style;
	var _ico2ds = _ico2d.style;
	var _ico3ds = _ico3d.style;
	var _ico4ds = _ico4d.style;
	var _ico5ds = _ico5d.style;
	
	_ico1ds.width = _ico2ds.width = _ico3ds.width = _ico4ds.width = _ico5ds.width = "100px";
	_ico1ds.height = _ico2ds.height = _ico3ds.height = _ico4ds.height = _ico5ds.height = "100px";
	_ico1ds.margin = _ico2ds.margin = _ico3ds.margin = _ico4ds.margin = _ico5ds.margin = "1px auto";
	_ico1ds.background = "transparent url('"+imgPath+"browser_ie.gif') no-repeat scroll left top";
	_ico2ds.background = "transparent url('"+imgPath+"browser_firefox.gif') no-repeat scroll left top";
	_ico3ds.background = "transparent url('"+imgPath+"browser_safari.gif') no-repeat scroll left top";
	_ico4ds.background = "transparent url('"+imgPath+"browser_opera.gif') no-repeat scroll left top";
	_ico5ds.background = "transparent url('"+imgPath+"browser_chrome.gif') no-repeat scroll left top";
	_lit1.appendChild(document.createTextNode(br1));
	_lit2.appendChild(document.createTextNode(br2));
	_lit3.appendChild(document.createTextNode(br3));
	_lit4.appendChild(document.createTextNode(br4));
	_lit5.appendChild(document.createTextNode(br5));
	
	var _lit1d = document.getElementById('_lit1');
	var _lit2d = document.getElementById('_lit2');
	var _lit3d = document.getElementById('_lit3');
	var _lit4d = document.getElementById('_lit4');
	var _lit5d = document.getElementById('_lit5');
	var _lit1ds = _lit1d.style;
	var _lit2ds = _lit2d.style;
	var _lit3ds = _lit3d.style;
	var _lit4ds = _lit4d.style;
	var _lit5ds = _lit5d.style;
	
	_lit1ds.color = _lit2ds.color = _lit3ds.color = _lit4ds.color = _lit5ds.color = "#808080";
	_lit1ds.fontSize = _lit2ds.fontSize = _lit3ds.fontSize = _lit4ds.fontSize = _lit5ds.fontSize = "0.8em";
	_lit1ds.height = _lit2ds.height = _lit3ds.height = _lit4ds.height = _lit5ds.height = "18px";
	_lit1ds.lineHeight = _lit2ds.lineHeight = _lit3ds.lineHeight = _lit4ds.lineHeight = _lit5ds.lineHeight = "17px";
	_lit1ds.margin = _lit2ds.margin = _lit3ds.margin = _lit4ds.margin = _lit5ds.margin = "1px auto";
	_lit1ds.width = _lit2ds.width = _lit3ds.width = _lit4ds.width = _lit5ds.width = "118px";
	_lit1ds.textAlign = _lit2ds.textAlign = _lit3ds.textAlign = _lit4ds.textAlign = _lit5ds.textAlign = "center";
	
}
