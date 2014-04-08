#ifndef SobelFilter_H
#define SobelFilter_H
#include "stdafx.h"
#include "Image.h"
#include <iostream>

class SobelFilter {
public:
	void CreateSobelImage(Image &destinationImage);
};

#endif

