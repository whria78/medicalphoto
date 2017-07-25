#include "stdafx.h"
#include "imageprocess.h"

void ImageProcess::MakeThumbnail(CxImage& image,config& config_)
{
	RGBQUAD border;
	border.rgbBlue=0;
	border.rgbGreen=0;
	border.rgbRed=0;

	int height=config_.GetInt(THUMB_HEIGHT);
	int width=config_.GetInt(THUMB_WIDTH);
	int iHeight=image.GetHeight();
	int iWidth=image.GetWidth();

	int top=0;
	int left=0;

	if (iHeight>0 && iWidth>0 && height>0 && width>0)
	{
		if (width*iHeight <= height*iWidth)
		{
			int old_height=height;
			height=iHeight*width/iWidth;
			top+=(old_height-height)/2;
		}
		else
		{
			int old_width=width;
			width=iWidth*height/iHeight;
			left+=(old_width-width)/2;
		}
		image.Thumbnail(width,height,border);
		image.Expand(left,top,left,top,border);
	}
}
