<?php
/**
 * Mobile Joomla!
 * http://www.mobilejoomla.com
 *
 * @version		1.2.8
 * @license		GNU/GPL v2 - http://www.gnu.org/licenses/gpl-2.0.html
 * @copyright	(C) 2008-2013 Kuneri Ltd.
 * @date		November 2013
 */
defined('_JEXEC') or die('Restricted access');

defined('_MJ') or die('Incorrect usage of Mobile Joomla.');

$MobileJoomla = MobileJoomla::getInstance();

$modulepos = $MobileJoomla->getPosition('header');
if($modulepos)
	$MobileJoomla->loadModules($modulepos);
$modulepos = $MobileJoomla->getPosition('header2');
if($modulepos)
	$MobileJoomla->loadModules($modulepos);

$MobileJoomla->showMessage();

$modulepos = $MobileJoomla->getPosition('header3');
if($modulepos)
	$MobileJoomla->loadModules($modulepos);


$modulepos = $MobileJoomla->getPosition('middle');
if($modulepos)
	$MobileJoomla->loadModules($modulepos);

$MobileJoomla->showComponent();

$modulepos = $MobileJoomla->getPosition('middle2');
if($modulepos)
	$MobileJoomla->loadModules($modulepos);
$modulepos = $MobileJoomla->getPosition('middle3');
if($modulepos)
	$MobileJoomla->loadModules($modulepos);


$modulepos = $MobileJoomla->getPosition('footer');
if($modulepos)
	$MobileJoomla->loadModules($modulepos);
$modulepos = $MobileJoomla->getPosition('footer2');
if($modulepos)
	$MobileJoomla->loadModules($modulepos);

$MobileJoomla->showFooter();

$modulepos = $MobileJoomla->getPosition('footer3');
if($modulepos)
	$MobileJoomla->loadModules($modulepos);


$modulepos = $MobileJoomla->getPosition('cards');
if($modulepos)
	$MobileJoomla->loadModules($modulepos);
