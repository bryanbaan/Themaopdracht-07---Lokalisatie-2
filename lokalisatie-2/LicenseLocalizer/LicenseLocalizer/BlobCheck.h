/*
*
*	Author: Mike Schaap
*/

#ifndef BlobCheck_H
#define BlobCheck_H
#include "Image.h"
#include <iostream>
#include <list>
#include "Blob.h"
#include "Point.h"

class BlobCheck {
private:

public:
	BlobCheck();
	~BlobCheck();
	std::vector<Blob> CheckIfBlobIsLicensePlate(std::vector<Blob> &blobobjects, Image &sourceImage);
};

#endif