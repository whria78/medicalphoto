<?if( $sg == 'banner' ):?>
<div style="width:137px;text-align:center;margin:0 auto;">
<br />
<table style="width:137px;text-align:center;" cellpadding="0" cellspacing="0">
	<tr>
		<td><font class="sgf1">Designed by:</font></td>
	</tr>
</table>
<table style="width:137px;height:16px;text-align:center;border:none;" cellpadding="0" cellspacing="0">
	<tr>
		<td><img src="templates/<?php echo $this->template ?>/images/banner_01.jpg" style="width:28px;height:16px;" alt="SiteGround web hosting" title="SiteGround web hosting" /></td>
		<td width="2" height="16"></td>
		<td style="background:url(templates/<?php echo $this->template ?>/images/banner_02.jpg);width:107px;height:16px;text-align:center;">
			<a href="http://www.siteground.com/joomla-hosting/joomla-templates.htm" style="font-size: 10px; font-family: Verdana,Arial,Helvetica,sans-serif; color: #333333;text-decoration:none;">Joomla Templates</a>
		</td>
	</tr>
</table>
</div>  
<?else:?>
 	<?php echo $mainframe->getCfg('sitename') ;?>, Powered by <a href="http://joomla.org/" class="sgfooter" target="_blank">Joomla!</a> and designed by SiteGround <a href="http://www.siteground.com/" target="_blank" class="sgfooter">web hosting</a>
 <?endif;?>
