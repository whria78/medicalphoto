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

function modChrome_wml($module, &$params, &$attribs)
{
	if(!empty($module->content))
	{
		if($module->showtitle)
		{
			?><p><strong><?php echo $module->title; ?></strong></p><?php
		}
		echo '<p>'.$module->content.'<br /></p>';
	}
}

function modChrome_wmlcards($module, &$params, &$attribs)
{
	if(!empty($module->content))
	{
		echo '<card name="'.$module->module."\">\n";
		if($module->showtitle)
		{
			?><p><strong><?php echo $module->title; ?></strong></p><?php
		}
		echo '<p>'.$module->content."</p></card>\n";
	}
}
