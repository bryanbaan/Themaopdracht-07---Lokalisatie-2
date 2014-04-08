/*
*
*	Author: Mike Schaap
*/

#ifndef BlobDetection_H
#define BlobDetection_H

#include <string>
#include <iostream>

#include "Blob.h"
#include <list>

#include "Image.h"

#include "Point.h"

//Shift values

class BlobDetection {
private:
	

public:
	BlobDetection();
	std::vector<Blob> Invoke(Image &img, int minBlobSize);
};

#endif