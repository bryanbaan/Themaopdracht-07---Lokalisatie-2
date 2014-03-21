#ifndef Cluster_H
#define Cluster_H
#include "Image.h"
#include "exectimer.h"
#include <iostream>

class Cluster {
private:
	BaseTimer* bt;
public:
	Cluster();
	~Cluster();
	void CreateK_MeansGrayImage(Image &sourceImage, Image &destinationImage, int clusters, int maxIterations);
	void CreateK_MeansColorImage(Image &sourceImage, Image &destinationImage, int clusters, int maxIterations);
};

#endif