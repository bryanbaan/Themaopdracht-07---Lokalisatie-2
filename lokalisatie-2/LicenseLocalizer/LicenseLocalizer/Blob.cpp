/*
*
*	Author: Mike Schaap
*/

#include "stdafx.h"
#include "Blob.h"

Blob::Blob(int label, int mass, int minY, int maxY, int minX, int maxX)  {
	_label = label;
	_pixelCount = mass;
	_smallestX = minX;
	_biggestX = maxX;
	_smallestY = minY;
	_biggestY = maxY;
}