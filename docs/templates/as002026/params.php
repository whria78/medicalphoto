<?php 

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

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// setting slide fading

$speed = 1000;
$autoplay = 5000;

$slider = array('slide1.jpg','slide2.jpg','slide3.jpg');

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// logo type
$logotype = 0;
$logoimg = 'companyname.png';
$logotxt = '';
$slogan = '';

$leftsidelogo = "1";

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// fontsize
$fontsize = '12px';

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// show left column

$showLeftCol = (bool) $this->countModules('position-0');
$showLeftCol += (bool) $this->countModules('position-7'); 
$showLeftCol += (bool) $this->countModules('position-4'); 
$showLeftCol += (bool) $this->countModules('position-9');
$showLeftCol += (bool) $this->countModules('whosonlineload'); 

$colMainWidth = 'style="width:670px"';
if (!$showLeftCol)
{
    $colMainWidth = 'style="width:960px"';
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// show custom top box

$showCustomTop = (bool) $this->countModules('position-3'); 
$showCustomTop += (bool) $this->countModules('position-6'); 
$showCustomTop += (bool) $this->countModules('position-8'); 

$customTopWidth = 'style="width:100%; background-image: none"';
if($showCustomTop == 1)
{
	$customTopWidth = 'style="width:690px; background-image: none"';
}
if($showCustomTop == 2)
{
	$customTopWidth = 'style="width:330px; background-image: none"';
}
else if($showCustomTop == 3)
{
	$customTopWidth = 'style="width:203px; background-image: none"';
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// show custom bottom box

$showCustomBottom = (bool) $this->countModules('position-15'); 
$showCustomBottom += (bool) $this->countModules('position-16'); 

$customBottomWidth = "";
if($showCustomBottom == 1)
{
	if($showLeftCol)
		$customBottomWidth = 'style="width:670px; background-image: none"';
	else
		$customBottomWidth = 'style="width:960px; background-image: none"';
}
else if($showCustomBottom == 2)
{
	if($showLeftCol)
		$customBottomWidth = 'style="width:325px; background-image: none"';
	else	
		$customBottomWidth = 'style="width:470px; background-image: none"';
}


?>
