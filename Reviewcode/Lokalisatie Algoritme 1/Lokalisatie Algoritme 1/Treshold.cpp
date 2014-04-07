#include "treshold.h"
#include <algorithm>
#include <iostream>
#include <time.h>
#include <vector>

/*
 * Version: 1.0
 * Author:  Niek Arends
 */

typedef unsigned char byte;

#define RED 211
#define GREEN 160
#define BLUE 15

Treshold::Treshold(void)
{
}

std::vector<byte> Treshold::threshholdyellow(std::vector<byte> oldvec, int width, int height) {
	std::vector<byte> newvec;
	int pos = 0;

	for(int y = 0; y < height; y++) 
	{
		for (int x = 0; x < width ; x++) 
		{
			pos = ((x+(y*width))*4);
			//If a pixel falls in the range of the colors defined above the color will be turned white
			//Otherwise it will be blackened
			if((oldvec[pos+2] <= BLUE+20)&&((oldvec[pos+1] >= GREEN-50)&&(oldvec[pos+1] <= GREEN+50)) && ((oldvec[pos] >= RED-20) && (oldvec[pos] <= RED + 20)))
			{
				newvec.push_back(255);
				newvec.push_back(255);
				newvec.push_back(255);
				newvec.push_back(255);
			}
			else
			{
				newvec.push_back(0);
				newvec.push_back(0);
				newvec.push_back(0);
				newvec.push_back(255);
			}
		}			
	}
	return newvec;
}

std::vector<int> Treshold::localizelicence(std::vector<byte> imgvec, int width, int height)
{
	std::vector<int> corners;
	
	corners = findtopleftcorner(imgvec, width, height);
	std::cout << "Topleft X:" <<corners[0] << "\tY:" << corners[1] << "\n";
	corners = findtoprightcorner(imgvec,width,height);
	std::cout << "Topright X:" <<corners[0] << "\tY:" << corners[1] << "\n";
	corners = findbottomleftcorner(imgvec,width,height);
	std::cout << "Bottomleft X:" <<corners[0] << "\tY:" << corners[1] << "\n";
	corners = findbottomrightcorner(imgvec, width, height);
	std::cout << "Bottomright X:" <<corners[0] << "\tY:" << corners[1] << "\n";
	return corners;
}

std::vector<int> Treshold::findtopleftcorner(std::vector<byte> img, int width, int height)
{
	int treshpercent = 80;
	int stepsize = 20;
	int count = 0;
	int pos;
	std::vector<int> corners;

	//The mask searches over the image untill it finds white pixels. When the mask hits white pixels it will
	//start taking smaller steps in case the corner is nearby. When the mask is filled with enough white pixels
	//The X and Y will be returned
	for(int x = 20; x < width-20; x+=stepsize)
	{
		for(int y = 20; y < height-20; y+=stepsize)
		{
			for(int w = 0; w < 20; w++)
			{
				for(int v = 0; v<20; v++) 
				{
					pos = ((x+(y*width))*4)+((w+(v*width))*4);
					if(img[pos]==255){count++;}
					if(count != 0)
					{
						stepsize=1;
					}
					else 
					{
						stepsize =20;
					}
				}
			}
			if(count >= treshpercent)
			{
				corners.push_back(x);
				corners.push_back(y);
				return corners;
			}
			count = 0;
		}
	}
}


std::vector<int> Treshold::findtoprightcorner(std::vector<byte> img, int width, int height)
{
	int treshpercent = 80;
	int stepsize = 20;
	int count = 0;
	int pos;
	std::vector<int> corners;

	for(int x = width-20 ; x > 20 ; x-=stepsize)
	{
		for(int y = 20; y < height-20; y+=stepsize)
		{
			for(int w = -20; w < 0; w++)
			{
				for(int v = 0; v<20; v++) 
				{
					pos = ((x+(y*width))*4)+((w+(v*width))*4);
					if(img[pos]==255){count++;}
					if(count != 0)
					{
						stepsize=1;
					}
					else 
					{
						stepsize =20;
					}
				}
			}
			if(count >= treshpercent)
			{
				corners.push_back(x);
				corners.push_back(y);
				return corners;
			}
			count = 0;
		}
	}
}

std::vector<int> Treshold::findbottomleftcorner(std::vector<byte> img, int width, int height)
{
	int treshpercent = 80;
	int stepsize = 20;
	int count = 0;
	int pos;
	std::vector<int> corners;

	for(int x = 20; x < width-20; x+=stepsize)
	{
		for(int y = height-20; y > 20; y-=stepsize)
		{
			for(int w = 0; w < 20; w++)
			{
				for(int v = 0; v<20; v++) 
				{
					pos = ((x+(y*width))*4)+((w+(v*width))*4);
					if(img[pos]==255){count++;}
					if(count != 0)
					{
						stepsize=1;
					}
					else 
					{
						stepsize =20;
					}
				}
			}
			if(count >= treshpercent)
			{
				corners.push_back(x);
				corners.push_back(y);
				return corners;
			}
			count = 0;
		}
	}
}

std::vector<int> Treshold::findbottomrightcorner(std::vector<byte> img, int width, int height)
{
	int treshpercent = 80;
	int stepsize = 20;
	int count = 0;
	int pos;
	std::vector<int> corners;

	for(int x = width-20; x > 20; x-=stepsize)
	{
		for(int y = height-20; y > 20; y -=stepsize)
		{
			for(int w = 0; w < 20; w++)
			{
				for(int v = 0; v<20; v++) 
				{
					pos = ((x+(y*width))*4)+((w+(v*width))*4);
					if(img[pos]==255){count++;}
					if(count != 0)
					{
						stepsize=1;
					}
					else 
					{
						stepsize =20;
					}
				}
			}
			if(count >= treshpercent)
			{
				corners.push_back(x);
				corners.push_back(y);
				return corners;
			}

			count = 0;
		}
	}
}