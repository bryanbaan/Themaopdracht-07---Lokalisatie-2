#ifndef BlobCheck_H
#define BlobCheck_H
#include "Image.h"
#include "exectimer.h"
#include <iostream>

class BlobCheck {
private:
	BaseTimer* bt;
public:
	BlobCheck();
	~BlobCheck();
	void CheckIfBlobIsLicensePlate(Blob &blobobjects);
};

#endif