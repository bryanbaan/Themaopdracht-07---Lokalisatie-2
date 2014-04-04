#ifndef BlobCheck_H
#define BlobCheck_H
#include "Image.h"
#include "exectimer.h"
#include <iostream>
#include <list>

class BlobCheck {
private:
	BaseTimer* bt;
public:
	BlobCheck();
	~BlobCheck();
	void CheckIfBlobIsLicensePlate(std::list<blob> &blobobjects);
};

#endif