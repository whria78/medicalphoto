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

$MobileJoomla->showDocType();
?>
<html>
<head>
	<meta name="CHTML">
	<meta http-equiv="Content-Type" content="<?php echo $MobileJoomla->getContentString(); ?>">
<?php $MobileJoomla->showHead(); ?>
</head>
<body>
<?php

$modulepos = $MobileJoomla->getPosition('header');
if($modulepos && $this->countModules($modulepos) > 0)
	$MobileJoomla->loadModules($modulepos);
$modulepos = $MobileJoomla->getPosition('header2');
if($modulepos && $this->countModules($modulepos) > 0)
	$MobileJoomla->loadModules($modulepos);

$MobileJoomla->showMessage();

$modulepos = $MobileJoomla->getPosition('header3');
if($modulepos && $this->countModules($modulepos) > 0)
	$MobileJoomla->loadModules($modulepos);


$modulepos = $MobileJoomla->getPosition('middle');
if($modulepos && $this->countModules($modulepos) > 0)
	$MobileJoomla->loadModules($modulepos);

$MobileJoomla->showComponent();

$modulepos = $MobileJoomla->getPosition('middle2');
if($modulepos && $this->countModules($modulepos) > 0)
	$MobileJoomla->loadModules($modulepos);
$modulepos = $MobileJoomla->getPosition('middle3');
if($modulepos && $this->countModules($modulepos) > 0)
	$MobileJoomla->loadModules($modulepos);


$modulepos = $MobileJoomla->getPosition('footer');
if($modulepos && $this->countModules($modulepos) > 0)
	$MobileJoomla->loadModules($modulepos);
$modulepos = $MobileJoomla->getPosition('footer2');
if($modulepos && $this->countModules($modulepos) > 0)
	$MobileJoomla->loadModules($modulepos);

$MobileJoomla->showFooter();

$modulepos = $MobileJoomla->getPosition('footer3');
if($modulepos && $this->countModules($modulepos) > 0)
	$MobileJoomla->loadModules($modulepos);

?>
</body>
</html>