#ifndef GRAYSCALEIMAGE_H 
#define GRAYSCALEIMAGE_H

#include <ImageLib.h>

using namespace ImageLib;

class GrayscaleImage {
public:
	ImageGray convertToGrayscale(ImageRGB & image);
};

#endif