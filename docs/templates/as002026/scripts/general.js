/*******************************************************************************************/
/*
/*		This template/design is released under the Creative Commons Attribution 3.0 license. 
/*		This means that it can be used for private and commercial purposes, edited freely 
/*		or redistributed as long as you keep the link back to AS Designing. 
/*		For more info please see our terms of use: http://www.astemplates.com/terms.php
/*
/*		Designed by 'AS Designing'
/*		Web: http://www.asdesigning.com
/*		Email: info@asdesigning.com
/*
/*******************************************************************************************/

function goToURL(url) 
{ 
	window.location = url; 
}

function preloadImages() 
{ 
  var d=document; if(d.images){ if(!d.p) d.p=new Array();
    var i,j=d.p.length,a=preloadImages.arguments; for(i=0; i<a.length; i++)
    if (a[i].indexOf("#")!=0){ d.p[j]=new Image; d.p[j++].src=a[i];}}
}


function swapImgRestore() 
{
  var i,x,a=document.sr; 
	
	for(i=0;a&&i<a.length&&(x=a[i])&&x.oSrc;i++) 
		x.src=x.oSrc;
}


function findObj(n, d) 
{
  var p,i,x;  
  
  if(!d) d=document; 
  if((p=n.indexOf("?"))>0&&parent.frames.length) 
  {
    d=parent.frames[n.substring(p+1)].document; n=n.substring(0,p);
  }
  if(!(x=d[n])&&d.all) x=d.all[n]; for (i=0;!x&&i<d.forms.length;i++) x=d.forms[i][n];
  for(i=0;!x&&d.layers&&i<d.layers.length;i++) x=findObj(n,d.layers[i].document);
  if(!x && document.getElementById) x=document.getElementById(n); 
  return x;
}


function swapImage() 
{
  var i,j=0,x,a=swapImage.arguments; 
	
	document.sr=new Array; 
	for(i=0;i<(a.length-2);i+=3)
    if ((x=findObj(a[i]))!=null)
	  {
			document.sr[j++]=x; 
			if(!x.oSrc) 
				x.oSrc=x.src; 
			x.src=a[i+2];
		}
}
