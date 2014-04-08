#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include "stdafx.h"
#include "Image.h"

class Histogram {
public:
	Histogram(Image & image);
	~Histogram();

	void SaveToCSV(std::string filename);
private:
	int * values;
	int size;
};


#endif