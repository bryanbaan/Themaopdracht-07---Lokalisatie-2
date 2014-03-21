#ifndef GrayScale_H
#define GrayScale_H
#include "Image.h"
#include "exectimer.h"
#include <iostream>

class GrayScale {
private:
	BaseTimer* bt;
public:
	GrayScale();
	~GrayScale();
	void CreateGrayScaleImage(Image &sourceImage, Image &destinationImage);
};

#endif