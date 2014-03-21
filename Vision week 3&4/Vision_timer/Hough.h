#ifndef Hough_H
#define Hough_H
#include "Image.h"
#include "exectimer.h"
#include <iostream>

class Hough {
private:
	BaseTimer* bt;
public:
	Hough();
	~Hough();
	void Transform(Image &sourceImage, Image &destinationImage);
};

#endif