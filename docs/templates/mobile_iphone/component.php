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

$base = $this->baseurl.'/templates/'.$this->template;

?>
<!doctype html>
<html<?php echo $MobileJoomla->getXmlnsString(); ?>>
<head>
	<meta http-equiv="Content-Type" content="<?php echo $MobileJoomla->getContentString(); ?>"/>
	<meta name="viewport" content="width=device-width, initial-scale=1, minimum-scale=1, maximum-scale=1, user-scalable=no">
	<meta name="format-detection" content="telephone=no" />
	<meta name="format-detection" content="address=no" />
<?php $MobileJoomla->showHead(); ?>
	<style type="text/css" media="screen">@import "<?php echo $base;?>/jqtouch-src/jqtouch/jqtouch.min.css";</style>
	<style type="text/css" media="screen">@import "<?php echo $base;?>/jqtouch-src/themes/<?php echo $this->params->get('theme', 'apple'); ?>/theme.min.css";</style>
	<style type="text/css" media="screen">@import "<?php echo $base;?>/css/mj_iphone.css";</style>
<?php if(@filesize(JPATH_SITE.DS.'templates'.DS.$this->template.DS.'css'.DS.'custom.css')): ?>
	<style type="text/css" media="screen">@import "<?php echo $base;?>/css/custom.css";</style>
<?php endif; ?>
</head>
<body>
<div<?php echo ($MobileJoomla->isHome()) ? ' id="home"' : '';?> class="current">
<?php $MobileJoomla->showMessage(); ?>
<?php $MobileJoomla->showComponent(); ?>
</div>
</body>
</html>