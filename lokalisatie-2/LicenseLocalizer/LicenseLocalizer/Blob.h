/*
*
*	Author: Mike Schaap
*/

#ifndef Blob_H
#define Blob_H

#include <vector>

class Blob {

private:
	int _pixelCount;
	int _smallestY;
	int _biggestY;

	int _smallestX;
	int _biggestX;

public:
	Blob(int mass, int minY, int maxY, int minX, int maxX);

	int getGroundSurface(){return (getWidth() * getHeight());};
	double getRatio(){return (double((getWidth()+1)) / double((getHeight()+1)));};
	int getMass(){return _pixelCount;};

	int getWidth(){return (_biggestX - _smallestX);};
	int getHeight(){return (_biggestY - _smallestY);};

	std::vector<int> getCornerPoints(){ return std::vector<int>{_smallestY, _smallestX, _smallestY, _biggestX, _biggestY, _smallestX, _biggestY, _biggestX}; };

};

#endif