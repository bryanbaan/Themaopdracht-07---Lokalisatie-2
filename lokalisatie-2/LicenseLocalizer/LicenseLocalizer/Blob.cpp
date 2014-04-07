#include "stdafx.h"
#include "Blob.h"

Blob::Blob() {
	_pixelCount = 0;
	_smallestX = -1;
	_biggestX = -1;
	_smallestY = -1;
	_biggestY = -1;
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