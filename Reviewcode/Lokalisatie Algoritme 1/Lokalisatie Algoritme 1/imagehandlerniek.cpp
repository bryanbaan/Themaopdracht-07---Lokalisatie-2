#include "imagehandlerniek.h"
#include <corona.h>
#include <iostream>

imagehandlerniek::imagehandlerniek(void)
{
}

std::vector<byte> imagehandlerniek::loadimg(char* filename) {
	corona::Image* image = corona::OpenImage( filename, corona::PF_R8G8B8A8);
	if (!image) 
	{
		std::cout << "File: " << filename << " not found\n";
	}

	width  = image->getWidth();
	int height = image->getHeight();
	int numofpixels = width*height;

	void* pixels = image->getPixels();
	byte* p = (byte*)pixels;

	std::vector<byte> imgvec;
	
	for (int i = 0; i < ((width * height)*4); i++) {
		imgvec.push_back(*p);
		*p++;
	}
	return imgvec;
}

void imagehandlerniek::saveimg(std::vector<byte> vec, char* naam, int width, int height) {
	corona::Image* newimage = corona::CreateImage(width, height, corona::PF_R8G8B8A8);
	void* pixel2 = newimage->getPixels();
	byte* p2 = (byte*)pixel2;

	//arimage kopieren in nieuwe image
	for (int i = 0; i < ((width * height)*4); i++) {
		*p2++ = vec[i];
	}

	corona::SaveImage(naam, corona::FF_PNG, newimage);
}