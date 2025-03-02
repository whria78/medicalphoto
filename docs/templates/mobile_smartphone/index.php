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

//load language file (to allow users to rename template)
MobileJoomla::loadLanguageFile('tpl_mobile_smartphone');

$MobileJoomla = MobileJoomla::getInstance();

$base = $this->baseurl.'/templates/'.$this->template;
$home = $this->baseurl.'/';

$MobileJoomla_Device =& MobileJoomla::getDevice();
if($MobileJoomla_Device['markup'] != $MobileJoomla_Device['default_markup'])
	$home .= '?device='.$MobileJoomla_Device['markup'];

$MobileJoomla->showXMLheader();
$MobileJoomla->showDocType();
?>
<html<?php echo $MobileJoomla->getXmlnsString(); ?>>
<head>
<?php $MobileJoomla->showHead(); ?>
	<meta name="viewport" content="width=device-width, initial-scale=1, minimum-scale=1, maximum-scale=1, user-scalable=no" />
	<meta name="HandheldFriendly" content="True" />
	<meta name="MobileOptimized" content="<?php echo $MobileJoomla_Device['screenwidth']; ?>" />
	<meta http-equiv="cleartype" content="on" />
	<meta name="format-detection" content="telephone=no" />
	<meta name="format-detection" content="address=no" />
	<style type="text/css" media="screen">@import "<?php echo $base;?>/resources/styles/reset.css";</style>
	<style type="text/css" media="screen">@import "<?php echo $base;?>/resources/styles/baseStyles.css";</style>
	<style type="text/css" media="screen">@import "<?php echo $base;?>/css/mj_xhtml.css";</style>
<?php
	if(@filesize(JPATH_SITE.DS.'templates'.DS.$this->template.DS.'css'.DS.'custom.css'))
	{
		if($MobileJoomla->getParam('embedcss', false))
		{
			echo "<style>\n";
			@readfile(JPATH_SITE.DS.'templates'.DS.$this->template.DS.'css'.DS.'custom.css');
			echo "</style>\n";
		}
		else
		{
?>
	<style type="text/css" media="screen">@import "<?php echo $base;?>/css/custom.css";</style>
<?php
		}
	}
?>
	<script type="text/javascript" src="<?php echo $base;?>/resources/scripts/templates.js"></script>
	<script src="<?php echo $base;?>/mj_xhtml.js" type="text/javascript" charset="utf-8"></script>
</head>
<body>
<div id="wrap">
	<div id="header">
<?php
		$modulepos = $MobileJoomla->getPosition('header');
		if($modulepos && $this->countModules($modulepos) > 0):
			?><div id="<?php echo $modulepos; ?>"><?php $MobileJoomla->loadModules($modulepos); ?></div><?php
		endif;
?>
	</div>
<?php
	$modulepos = $MobileJoomla->getPosition('header2');
	if($modulepos && $this->countModules($modulepos) > 0):
		?><div id="<?php echo $modulepos; ?>"><?php $MobileJoomla->loadModules($modulepos); ?></div><?php
	endif;

	$MobileJoomla->showMessage();

	$modulepos = $MobileJoomla->getPosition('header3');
	if($modulepos && $this->countModules($modulepos) > 0):
		?><div id="<?php echo $modulepos; ?>"><?php $MobileJoomla->loadModules($modulepos); ?></div><?php
	endif;
?>
	<div id="content">
<?php
		$modulepos = $MobileJoomla->getPosition('middle');
		if($modulepos && $this->countModules($modulepos) > 0):
			?><div id="<?php echo $modulepos; ?>"><?php $MobileJoomla->loadModules($modulepos); ?></div><?php
		endif;

		$MobileJoomla->showComponent();

		$modulepos = $MobileJoomla->getPosition('middle2');
		if($modulepos && $this->countModules($modulepos) > 0):
			?><div id="<?php echo $modulepos; ?>"><?php $MobileJoomla->loadModules($modulepos); ?></div><?php
		endif;
		$modulepos = $MobileJoomla->getPosition('middle3');
		if($modulepos && $this->countModules($modulepos) > 0):
			?><div id="<?php echo $modulepos; ?>"><?php $MobileJoomla->loadModules($modulepos); ?></div><?php
		endif;

?>
		<div class="top">
			<a href="#header"><?php echo JText::_('TPL_MOBILE_SMARTPHONE__BACK_TO_THE_TOP'); ?></a>
		</div>
<?php
		if(!$MobileJoomla->isHome())
		{
?>
			<div class="home">
				<a href="<?php echo $home; ?>"><?php echo JText::_('TPL_MOBILE_SMARTPHONE__HOME'); ?></a>
			</div>
<?php
		}
?>
	</div>
	<div id="footer">
<?php
		$modulepos = $MobileJoomla->getPosition('footer');
		if($modulepos && $this->countModules($modulepos) > 0):
			?><div id="<?php echo $modulepos; ?>"><?php $MobileJoomla->loadModules($modulepos); ?></div><?php
		endif;
		$modulepos = $MobileJoomla->getPosition('footer2');
		if($modulepos && $this->countModules($modulepos) > 0):
			?><div id="<?php echo $modulepos; ?>"><?php $MobileJoomla->loadModules($modulepos); ?></div><?php
		endif;

		$MobileJoomla->showFooter();

		$modulepos = $MobileJoomla->getPosition('footer3');
		if($modulepos && $this->countModules($modulepos) > 0):
			?><div id="<?php echo $modulepos; ?>"><?php $MobileJoomla->loadModules($modulepos); ?></div><?php
		endif;
?>
	</div>
<?php
	$dispatcher = JDispatcher::getInstance(); 
	$results = $dispatcher->trigger( 'onMobileJoomlaAdCheck', array() );
	if(in_array('f3da4a6dd8f15c9170572d18838c841e', array_map('md5', $results)))
	{
		// The user has installed plug-in to remove ads
	}
	else
	{
?>
<div class="mj-sponsor-placement">
<script type="text/javascript">
//<!--
/* <![CDATA[ */
document.write('<script src'+'="http'+('https:'==document.location.protocol?'s':'')+'://ads.mobilejoomla.com/ad.js?domain='+encodeURIComponent(window.location.hostname)+'" type="text/javascript"><'+'/script>');
/* ]]> */
//-->
</script>
</div>
<?php
	}
?>
</div>
</body>
</html>