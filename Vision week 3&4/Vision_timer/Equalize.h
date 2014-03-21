#ifndef Equalize_H
#define Equalize_H
#include "Image.h"
#include "exectimer.h"
#include <iostream>
#include <fstream>


class Equalize {
private:
	BaseTimer* bt;
public:
	Equalize();
	~Equalize();
	void CreateEqualizedImage(Image &sourceImage, Image &destinationImage);
};

#endif