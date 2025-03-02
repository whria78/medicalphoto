<?php 

/*******************************************************************************************/
/*
/*    Designed by 'AS Designing'
/*    Web: http://www.asdesigning.com
/*    Email: info@asdesigning.com
/*
/*******************************************************************************************/

defined( '_JEXEC' ) or die( 'Restricted access' );

/* The following line loads the MooTools JavaScript Library */
JHTML::_('behavior.framework', true);

/* The following line gets the application object for things like displaying the site name */
$app = JFactory::getApplication();

?>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="<?php echo $this->language; ?>" lang="<?php echo $this->language; ?>" >

<head>
<jdoc:include type="head" />
<link rel="stylesheet" href="<?php echo $this->baseurl ?>/templates/system/css/general.css" type="text/css" />
<link rel="stylesheet" href="<?php echo $this->baseurl ?>/templates/system/css/system.css" type="text/css" />

<link rel="stylesheet" href="<?php echo $this->baseurl ?>/templates/<?php echo $this->template ?>/css/template.css" type="text/css" />
<link rel="stylesheet" href="<?php echo $this->baseurl ?>/templates/<?php echo $this->template ?>/css/joomla.css" type="text/css" />
<link rel="stylesheet" href="<?php echo $this->baseurl ?>/templates/<?php echo $this->template ?>/css/slideshow.css" type="text/css" media="all" />

<script type="text/javascript" src="templates/<?php echo $this->template ?>/scripts/general.js"></script>
<script type="text/javascript" src="templates/<?php echo $this->template ?>/scripts/jquery.js"></script>
<script type="text/javascript" src="templates/<?php echo $this->template ?>/scripts/fading.js"></script>


<?php 

include 'ie6warning.php';
include 'params.php';

?>

</head>

<body <?php echo 'style="font-size: ' . $fontsize . ';"'; ?>>
  <div id="wrapper<?php echo $leftsidelogo; ?>">
    <!-- HEADER ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~  -->
  
    <div id="general">

      <!-- HEADER ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->
      <div id="header">

        <div class="headercolleft">
          <?php if(!$this->countModules('position-18')): ?>
          <div id="slideshow">
            <div id="fading">
              <ul>
              <?php
              for($i=0; $i<count($slider); $i++)  
              {
                echo '<li><img src="templates/' . $this->template . '/images/sliderimages/' . $slider[$i] . '" width="310" height="480" alt="" /></li>';
              }
              ?>
              </ul>
            </div>
          </div>
          <script type="text/javascript">
             var $j = jQuery.noConflict(); 
               $j(function(){
               $j("#fading").faded({
                  speed:<?php echo $speed ?>,// 900,
                  crossfade: true,
                  autopagination: false,
                  autoplay: <?php echo $autoplay ?>,//default 5000,
                  autorestart: true
               });
             });
          </script>          
          <?php elseif($this->countModules('position-18')): ?>
          <div id="slideshow">
            <jdoc:include type="modules" name="position-18" />
          </div>        
          <?php endif; ?>
        </div>
        
        <div class="headercolright">
          <div id="mainmenu">
            <jdoc:include type="modules" name="position-1"/>
          </div>
          <div class="clear"></div>

          <div id="companyname">
            <?php if(!$logotype): ?>
            <a href="<?php echo $this->baseurl ?>"> 
              <img src="<?php echo $this->baseurl ?>/templates/<?php echo $this->template ?>/images/<?php echo $logoimg; ?>" alt="MedicalPhoto"/> 
            </a>
            <?php else: ?> 
              <div class="companyname">
                <?php echo $logotxt; ?>
                <div class="slogan">
                  <?php echo $slogan; ?>
                </div>                
              </div>
            <?php endif; ?>
          </div>
          <div class="clear"></div>

          <div id="customtop_container">
            <?php if($this->countModules('position-3')): ?>
            <div class="box1" <?php echo $customTopWidth; ?>>
              <div id="topleft">      
                <jdoc:include type="modules" name="position-3" style="xhtml" />
              </div>
            </div>
            <?php endif; ?>

            <?php if($this->countModules('position-3') && $this->countModules('position-6')): ?>
            <div class="separator_30_left"></div>
            <?php endif; ?>            

            <?php if($this->countModules('position-6')): ?>
            <div class="box2" <?php echo $customTopWidth; ?>>
              <div id="topcenter">
                <jdoc:include type="modules" name="position-6" style="xhtml" />
              </div>
            </div>
            <?php endif; ?>

            <?php if(($this->countModules('position-3')||$this->countModules('position-6')) && $this->countModules('position-8')): ?>
            <div class="separator_30_left"></div>
            <?php endif; ?>            

            <?php if($this->countModules('position-8')): ?>
            <div class="box3" <?php echo $customTopWidth; ?>>
              <div id="topright">
                <jdoc:include type="modules" name="position-8" style="xhtml" />
              </div>
            </div>
            <?php endif; ?>

            <div class="clear separator_30"></div>
          </div>
        </div>
  
      </div>
      <!-- END OF HEADER ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->

      <div class="clear"></div>
      
      <!-- CONTENT ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->
      <div id="content">
      
        <?php if($this->countModules('position-2')): ?>
        <div id="breadcrumb"> 
          <jdoc:include type="modules" name="position-2" />  
        </div>
        <?php endif; ?> 

        <!-- COLUMN LEFT ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->
        <?php if($showLeftCol): ?>
        <div id="colleft">
          <?php if($this->countModules('position-0')): ?>
          <div id="search">
            <jdoc:include type="modules" name="position-0" />
          </div>
          <?php endif; ?>
          
          <?php if($this->countModules('position-4')): ?>
          <div class="colleftcustom">
            <jdoc:include type="modules" name="position-4" style="xhtml"/>
          </div>
          <?php endif; ?>

          <?php if($this->countModules('position-7')): ?>
          <div id="menu">
            <jdoc:include type="modules" name="position-7" style="xhtml" />
          </div>
          <?php endif; ?>

          <?php if($this->countModules('whosonlineload')): ?>
          <div id="whosonline">
            <jdoc:include type="modules" name="whosonlineload" style="xhtml" />
          </div>
          <?php endif; ?>

          <?php if($this->countModules('position-9')): ?>
          <div class="colleftcustom">
            <jdoc:include type="modules" name="position-9" style="xhtml" />        
          </div>
          <?php endif; ?>
        </div>
        <?php endif; ?>
        <!-- END OF COLUMN LEFT ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->             
        

        <!-- COLUMN MAIN ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->          
        <div id="colmain" <?php echo $colMainWidth; ?> >
          <jdoc:include type="message" />
          <jdoc:include type="component"  />
          
          <?php if($this->countModules('position-10')): ?>
          <div class="customhtml">
            <jdoc:include type="modules" name="position-10" style="xhtml"/>
            <div class="clear"></div>
          </div>
          <?php endif; ?>
          <?php if($this->countModules('position-5')): ?>
          <div class="customhtml">
            <jdoc:include type="modules" name="position-5" style="xhtml"/>
            <div class="clear"></div>
          </div>
          <?php endif; ?>

          <div class="clear"></div>

          <?php if($showCustomBottom): ?>
          <div class="separator_30"></div>
          <div class="customhtml">
            <?php if($this->countModules('position-15')): ?>
            <div class="box1" <?php echo $customBottomWidth; ?>>
              <div class="txtbox_border">
                <div class="txtbox_custombottom">
                  <jdoc:include type="modules" name="position-15" style="xhtml" />
                </div>
              </div>
            </div>
            <?php endif; ?>
            <?php if($this->countModules('position-15') && $this->countModules('position-16')): ?>
            <div class="separator_20_left"></div>
            <?php endif; ?>
            <?php if($this->countModules('position-16')): ?>
            <div class="box2" <?php echo $customBottomWidth; ?>>
              <div class="txtbox_border">
                <div class="txtbox_custombottom">
                  <jdoc:include type="modules" name="position-16" style="xhtml" />
                </div>
              </div>
            </div>
            <?php endif; ?>
          </div>
          <div class="clear separator_20"></div>
          <?php endif; ?>
          
          <?php if($this->countModules('position-11')): ?>
          <div class="customhtml">
            <jdoc:include type="modules" name="position-11" style="xhtml"/>
          </div>
          <?php endif; ?>
          <div class="clear"></div>
          
        </div>
        <!-- END OF COLUMN MAIN ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->
    
        <div class="clear"></div>
      </div>
      
      <!-- END OF CONTENT ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->
    </div>
  
    <div class="clear"></div>
    <!-- FOOTER ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->
    <div id="footer">
      <div id="footercontent">
        <div id="footerleft" >
          <div class="txtbox1">
            <?php if($this->countModules('position-12')): ?>
            <div id="getintouch">
              <jdoc:include type="modules" name="position-12" style="xhtml" />
            </div>
            <?php endif; ?>
            
            <div id="footertrademark">
              <div id="trade">Copyright &copy; <?php echo date('Y'); ?> <?php echo $app->getCfg('sitename'); ?></div>
              
              <!-- DO NOT REMOVE OR CHANGE THE CONTENT BELOW, THIS TEMPLATE MAY NOT WORK PROPERLY -->
              <!-- FOR MORE INFO SEE OUR COPYRIGHT NOTICE FOR FREE WEBSITE TEMPLATES: http://astemplates.com/terms.php -->
              
              <div id="ascopy">
              <a href="http://www.asdesigning.com/" target="_blank" class="trademark" onmouseout="swapImgRestore()" 
                onmouseover="swapImage('trade','','<?php echo $this->baseurl ?>/templates/<?php echo $this->template ?>/images/asdesigning_on.png',1)">
                <img src="<?php echo $this->baseurl ?>/templates/<?php echo $this->template ?>/images/asdesigning_of.png" name="trade"  alt="AS Designing"/>
              </a>
              </div>

              <!-- DO NOT REMOVE OR CHANGE THE CONTENT ABOVE, THIS TEMPLATE MAY NOT WORK PROPERLY -->
              <!-- FOR MORE INFO SEE OUR COPYRIGHT NOTICE FOR FREE WEBSITE TEMPLATES: http://astemplates.com/terms.php -->
  
            </div>
          </div>
        </div>
  
        <?php if($this->countModules('position-13')): ?>
        <div class="separator_30_left"></div>
        <div id="footerright" >
          <div class="txtbox2">
            <div id="footermenu">
              <jdoc:include type="modules" name="position-13" style="xhtml" />
            </div>
          </div>
        </div>
        <?php endif; ?>
  
      </div>
    </div>
    <!-- END OF FOOTER ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->

  </div>

</body>
</html>
