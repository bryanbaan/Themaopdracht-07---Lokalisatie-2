#include "stdafx.h"
#include "Histogram.h"
#include <fstream>

Histogram::Histogram(Image & image) {
	int width = image.GetWidth();
	int height = image.GetHeight();

	arraySize = height;
	values = new int[arraySize];

	for (int i = 0; i < arraySize; i++) {
		values[i] = 0;
	}

	Pixel * pixel = (Pixel *)image.GetDataPointer();
	
	/////////////////////SELECT ROWS///////////////////////////
	
	for (int y = 0; y < height; y++) {
		arrayPos = y * width;
		for (int x = 0; x < width; x++){
			if (pixel[arrayPos + x].R == 255) {
				values[y]++;
			}
		}
	}
	
	getPeakRange(minPosLeft, minPosRight, values, arraySize);

	int y = minPosLeft * width;
	for (int x = 0; x < width; x++) {
		pixel[y + x].R = 255;
		pixel[y + x].G = 0;
		pixel[y + x].B = 0;
	}

	y = minPosRight * width;
	for (int x = 0; x < width; x++) {
		pixel[y + x].R = 255;
		pixel[y + x].G = 0;
		pixel[y + x].B = 0;
	}

	///////////////////SELECT ROWS////////////////////

	//////////////////SELECT COLUMNS/////////////////
	delete[] values;
	arraySize = width;
	values = new int[arraySize];

	for (int i = 0; i < arraySize; i++) {
		values[i] = 0;
	}

	for (int x = 0; x < width; x++) {
		for (int y = minPosLeft; y < minPosRight; y++) {
			arrayPos = y * width + x;
			if (pixel[arrayPos].R == 255) {
				values[x]++;
			}
		}
	}

	getPeakRange(minPosLeft, minPosRight, values, arraySize);

	for (int y = 0; y < height; y++) {
		drawingPos = y * width + minPosLeft;
		pixel[drawingPos].R = 0;
		pixel[drawingPos].G = 255;
		pixel[drawingPos].B = 0;
	}


	for (int y = 0; y < height; y++) {
		drawingPos = y * width + minPosRight;
		pixel[drawingPos].R = 0;
		pixel[drawingPos].G = 255;
		pixel[drawingPos].B = 0;
	}

	//////////////////SELECT COLUMNS/////////////////
}

Histogram::~Histogram() {
	delete[] values;
}

void Histogram::getPeakRange(int &leftSide, int &rightSide, int * values, int histogramSize) {
	int maxValue = 0;
	int minValue = MAXIMUMMINVALUE;
	int maxPosition = 0;
	
	for (int i = 0; i < histogramSize; i++) {
		if (values[i] > maxValue) {
			maxValue = values[i];
			maxPosition = i;
		}
		if (values[i] < minValue){
			minValue = values[i];
		}
	}

	for (int i = maxPosition; i > 0; i--) {
		if (values[i] == minValue) {
			leftSide = i;
			break;
		}
	}

	for (int i = maxPosition; i < (histogramSize); i++) {
		if (values[i] == minValue) {
			rightSide = i;
			break;
		}
	}
}

void Histogram::SaveToCSV(std::string filename) {
	std::ofstream output(filename);

	if (output.is_open()) {
		output << "sep=,\n";

		for (int i = 0; i < arraySize; i++) {
			output << i << ',' << values[i] << std::endl;
		}

		output.close();
	}
}