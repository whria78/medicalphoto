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
$MobileJoomla_Device =& MobileJoomla::getDevice();

$MobileJoomla->showXMLheader();
$MobileJoomla->showDocType();
?>
<html<?php echo $MobileJoomla->getXmlnsString(); ?>>
<head>
<meta http-equiv="Content-Type" content="<?php echo $MobileJoomla->getContentString(); ?>" />
<title><?php echo $this->title; ?></title>
<meta name="viewport" content="width=device-width, initial-scale=1, minimum-scale=1, maximum-scale=1, user-scalable=no" />
<meta name="HandheldFriendly" content="True" />
<meta name="MobileOptimized" content="<?php echo $MobileJoomla_Device['screenwidth']; ?>" />
<meta http-equiv="cleartype" content="on" />
<meta name="format-detection" content="telephone=no" />
<meta name="format-detection" content="address=no" />
</head>
<body>
	<p><b><?php echo $this->error->get('code'); ?> - <?php echo $this->error->get('message'); ?></b></p>
	<?php if($this->debug) echo '<p>'.$this->renderBacktrace().'</p>'; ?>
</body>
</html>