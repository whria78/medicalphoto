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

?>
<?php if(!$is_submenu) : ?>
<div class="menu<?php echo htmlspecialchars($params->get('class_sfx')); ?>">
<?php endif; ?>
<ul class="<?php echo $params->get('layout') . $params->get('class_prefix') . htmlspecialchars($params->get('class_sfx')); ?>">
<?php
foreach($menu as $item)
{
	if($params->get('type')=='submenu')
		$is_active = false;
	else
		$is_active = ($item->id == $active_id);

	if($item->type == 'separator')
		$outline = array('<span>', '</span>');
	else
	{
		$target = $item->browserNav > 0 ? ' target="_blank"' : '';
		$outline = array('<a href="'.$item->flink.'"'.$target.'>', '</a>');
	}

	$text = $item->title;
	$img  = $item->menu_image ? '<img src="'.$item->menu_image.'" />' : '';
	switch($params->get('format'))
	{
	case 0: break;
	case 1: $text = $img; break;
	case 2: $text = $img.$text; break;
	case 3: $text = $text.$img; break;
	case 4: $text = $img.'<br />'.$text; break;
	case 5: $text = $text.'<br />'.$img; break;
	}

	$class = array();
	if($is_active)
		$class[] = 'current';
	if($item->type != 'separator')
		$class[] = 'arrow';

	if(count($class)==0)
		$class = '';
	else
		$class = ' class="'.implode(' ',$class).'"';
?>
<li<?php echo $class; ?>>
<?php echo $outline[0] . $text . $outline[1]; ?>
</li>
<?php
	if($is_active && count($submenu))
		JMobileMenuHelper::renderSubmenu($submenu, $params);
}
?>
</ul>
<?php if( ($is_vertical xor $is_submenu) || ((!$is_vertical) && (!$is_submenu) && !$params->get('has_submenu')) ) : ?>
</div>
<div class="clear"></div>
<?php endif; ?>
