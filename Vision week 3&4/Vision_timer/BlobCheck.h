#ifndef BlobCheck_H
#define BlobCheck_H
#include "Image.h"
#include "exectimer.h"
#include <iostream>
#include <list>
#include "Blob.h"
#include "Point.h"

class BlobCheck {
private:
	BaseTimer* bt;
public:
	BlobCheck();
	~BlobCheck();
	int* CheckIfBlobIsLicensePlate(std::vector<Blob> &blobobjects, Image &sourceImage);
};

#endif