#ifndef HIGHPASSFILTER_H 
#define HIGHPASSFILTER_H

#include <ImageLib.h>

using namespace ImageLib;

class HighPassFilter {
public:
	void filterImage(ImageRGB & image);
};

#endif