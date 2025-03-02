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

function modChrome_chtml($module, &$params, &$attribs)
{
	/** @var JParameter $params */
	if(!empty($module->content))
	{
		?><div class="moduletable<?php echo htmlspecialchars($params->get('moduleclass_sfx')); ?>"><?php
		if($module->showtitle)
		{
			?><h3><?php echo $module->title; ?></h3><?php
		}
		echo $module->content;
		?></div><?php
	}
}
