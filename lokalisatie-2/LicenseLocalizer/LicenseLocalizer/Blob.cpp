/*
*
*	Author: Mike Schaap
*/

#include "stdafx.h"
#include "Blob.h"

Blob::Blob() {
	_pixelCount = 0;
	_smallestX = -1;
	_biggestX = -1;
	_smallestY = -1;
	_biggestY = -1;
}

Blob::Blob(int mass, int minY, int maxY, int minX, int maxX)  {
	_pixelCount = mass;
	_smallestX = minX;
	_biggestX = maxX;
	_smallestY = minY;
	_biggestY = maxY;
}

void Blob::addPixel(int x, int y) {
	if(x < _smallestX || _smallestX == -1) {
		_smallestX = x;
	}

	if(x > _biggestX || _biggestX == -1) {
		_biggestX = x;
	}

	if(y < _smallestY || _smallestY == -1) {
		_smallestY = y;
	}

	if(y > _biggestY || _biggestY == -1) {
		_biggestY = y;
	}

	_pixelCount++;

	_pixels.insert(_pixels.begin(), Point(y,x));
}

Point* Blob::getCornerPoints() {
	Point *cornerPoints = new Point[4];

	cornerPoints[0] = Point(_smallestY, _smallestX);
	cornerPoints[1] = Point(_smallestY, _biggestX);
	cornerPoints[2] = Point(_biggestY, _smallestX);
	cornerPoints[3] = Point(_biggestY, _biggestX);

	return cornerPoints;
}