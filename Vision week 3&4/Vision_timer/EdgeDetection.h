#ifndef EdgeDetection_H
#define EdgeDetection_H
#include "Image.h"
#include "exectimer.h"
#include <iostream>

class EdgeDetection {
private:
	BaseTimer* bt;
public:
	EdgeDetection();
	~EdgeDetection();
	void CreateEdgeDetectionImage(Image &sourceImage, Image &destinationImage);
};

#endif