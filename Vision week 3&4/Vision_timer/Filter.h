#ifndef Filter_H
#define Filter_H
#include "Image.h"
#include "exectimer.h"
#include <iostream>

class Filter {
private:
	BaseTimer* bt;
public:
	Filter();
	~Filter();
	void CreateMedianFilterImage(Image &sourceImage, Image &destinationImage, int size);
	void CreateMinimumFilterImage(Image &sourceImage, Image &destinationImage, int size);
	void CreateMaximumFilterImage(Image &sourceImage, Image &destinationImage, int size);
};

#endif