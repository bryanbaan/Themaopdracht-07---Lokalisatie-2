#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include "stdafx.h"
#include "Image.h"

#define MAXIMUMMINVALUE 30

class Histogram {
public:
	Histogram(Image & image);
	~Histogram();

	void getPeakRange(int &leftSide, int &rightSide, int * values, int histogramSize);
	void SaveToCSV(std::string filename);
private:
	int * values;
	int arraySize;
	int arrayPos;
	int drawingPos;
	int minPosRight;
	int minPosLeft;
};


#endif