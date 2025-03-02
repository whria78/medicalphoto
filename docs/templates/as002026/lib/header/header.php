<?php

defined('_JEXEC') or die ('Restricted access');

jimport('joomla.html.html');
jimport('joomla.form.formfield');

class JFormFieldHeader extends JFormField
{
	protected $type = 'Header';

	function getInput()
	{
		return $this->fetchElement($this->element['name'], $this->value, $this->element, $this->name);
	}
	
	function fetchElement($name, $value, &$node, $control_name)
	{
		$options = array(JText::_($value));
		foreach ($node->children() as $option)
		{
			$options[] = $option->data();
		}
		
		return sprintf('<div style="float: left; width: 100%%; font-weight: bold; font-size: 120%%; color: #000; background-color: #FAFAFA; border: 1px; border-style: solid; border-color: #CCCCCC; padding: 5px 0; text-align: center;margin-bottom:15px;">%s</div>', call_user_func_array('sprintf', $options));
	}
}
?>
