<?php
/**
 * @version		$Id: default_form.php 20196 2011-01-09 02:40:25Z ian $
 * @package		Joomla.Site
 * @subpackage	com_search
 * @copyright	Copyright (C) 2005 - 2011 Open Source Matters, Inc. All rights reserved.
 * @license		GNU General Public License version 2 or later; see LICENSE.txt
 */

// no direct access
defined('_JEXEC') or die;
?>

<form id="searchForm" action="<?php echo JRoute::_('index.php?option=com_search');?>" method="post">

	<fieldset class="word">
		<label for="search-searchword">
			<?php echo JText::_('COM_SEARCH_SEARCH_KEYWORD'); ?>
		</label>
		<input type="text" name="searchword" id="search-searchword" size="30" maxlength="20" value="<?php echo $this->escape($this->searchword); ?>" class="inputbox" />
	</fieldset>

	<div class="searchintro<?php echo $this->params->get('pageclass_sfx'); ?>">
		<?php if (!empty($this->searchword)):?>
		<p><?php echo JText::plural('COM_SEARCH_SEARCH_KEYWORD_N_RESULTS', $this->total);?></p>
		<?php endif;?>
	</div>

	<fieldset class="phrases">
		<legend><?php echo JText::_('COM_SEARCH_FOR');?>
		</legend>
			<div class="phrases-box">
			<?php echo $this->lists['searchphrase']; ?>
			</div>
			<div class="clear"></div>
			<div class="ordering-box">
			<label for="ordering" class="ordering">
				<?php echo JText::_('COM_SEARCH_ORDERING');?>
			</label>
			<?php echo $this->lists['ordering'];?>
			</div>
	</fieldset>

	<?php if ($this->params->get('search_areas', 1)) : ?>
		<fieldset class="only">
		<legend><?php echo JText::_('COM_SEARCH_SEARCH_ONLY');?></legend>
		<div class="searchonly-box">
			<?php foreach ($this->searchareas['search'] as $val => $txt) :
				$checked = is_array($this->searchareas['active']) && in_array($val, $this->searchareas['active']) ? 'checked="checked"' : '';
			?>
			<input type="checkbox" name="areas[]" value="<?php echo $val;?>" id="area-<?php echo $val;?>" <?php echo $checked;?> />
			<label for="area-<?php echo $val;?>">
				<?php echo JText::_($txt); ?>
			</label>
			<div class="clear"></div>
			<?php endforeach; ?>
		</div>
		</fieldset>
	<?php endif; ?>

<?php if ($this->total > 0) : ?>

	<div class="form-limit">
		<label for="limit">
			<?php echo JText::_('JGLOBAL_DISPLAY_NUM'); ?>
		</label>
		<?php echo $this->pagination->getLimitBox(); ?>
	</div>
<p class="counter">
		<?php echo $this->pagination->getPagesCounter(); ?>
	</p>

<?php endif; ?>
	<div>
		<button name="Search" onclick="this.form.submit()" class="button"><?php echo JText::_('COM_SEARCH_SEARCH');?></button>
		<input type="hidden" name="task" value="search" />
	</div>
	<div class="clear"></div>
</form>
