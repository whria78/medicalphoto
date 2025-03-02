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

echo '<p><b>'.$this->error->get('code').' - '.$this->error->get('message').'</b></p>';

if($this->debug)
	echo '<p>'.$this->renderBacktrace().'</p>';

$MobileJoomla->showFooter();
