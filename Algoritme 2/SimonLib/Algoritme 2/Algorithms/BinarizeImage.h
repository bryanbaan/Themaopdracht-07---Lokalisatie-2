#ifndef BINARIZEIMAGE_H
#define BINARIZEIMAGE_H

#include <ImageLib.h>

using namespace ImageLib;

class BinarizeImage {
public:
	void binarizeImage(ImageRGB & image, int threshold = 127);
};

#endif

