#include "IntensityHistogram.h"
#include <iostream>
#include <fstream>

LicensePosition IntensityHistogram::getLicensePosition(ImageRGB & image, bool generateCSV) {
	int width = image.width();
	int height = image.height();

	int topLeftX;
	int topLeftY;

	int topRightX;
	int topRightY;

	int bottomLeftX;
	int bottomLeftY;

	int bottomRightX;
	int bottomRightY;

	int size = height;
	int * values = new int[size];

	for (int i = 0; i < size; i++) {
		values[i] = 0;
	}

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			Rgb<unsigned char &> pixelRGB = image.at(x, y);

			if (pixelRGB.red == 255) {
				values[y]++;
			}
		}
	}

	int minPosLeft = 0;
	int minPosRight = 0;

	findPeakRange(minPosLeft, minPosRight, values, size);

	int y = minPosLeft;
	for (int x = 0; x < width; x++) {
		Rgb<unsigned char &> pixelRGB = image.at(x, y);

		pixelRGB.red = 255;
		pixelRGB.green = 0;
		pixelRGB.blue = 0;
	}

	y = minPosRight;
	for (int x = 0; x < width; x++) {
		Rgb<unsigned char &> pixelRGB = image.at(x, y);

		pixelRGB.red = 255;
		pixelRGB.green = 0;
		pixelRGB.blue = 0;
	}

	topLeftY = minPosLeft;
	topRightY = minPosLeft;
	bottomLeftY = minPosRight;
	bottomRightY = minPosRight;

	delete[] values;
	size = width;
	values = new int[size];

	for (int i = 0; i < size; i++) {
		values[i] = 0;
	}

	for (int x = 0; x < width; x++) {
		for (int y = minPosLeft; y < minPosRight; y++) {
			Rgb<unsigned char &> pixelRGB = image.at(x, y);

			if (pixelRGB.red == 255) {
				values[x]++;
			}
		}
	}

	findPeakRange(minPosLeft, minPosRight, values, size);
	
	int x = minPosLeft;
	for (int y = 0; y < height; y++) {
		Rgb<unsigned char &> pixelRGB = image.at(x, y);

		pixelRGB.red = 0;
		pixelRGB.green = 255;
		pixelRGB.blue = 0;
	}

	x = minPosRight;
	for (int y = 0; y < height; y++) {
		Rgb<unsigned char &> pixelRGB = image.at(x, y);

		pixelRGB.red = 0;
		pixelRGB.green = 255;
		pixelRGB.blue = 0;
	}

	topLeftX = minPosLeft;
	topRightX = minPosRight;
	bottomLeftX = minPosLeft;
	bottomRightX = minPosRight;
	
	delete[] values;

	return LicensePosition(topLeftX, topLeftY, topRightX, topRightY, bottomLeftX, bottomLeftY, bottomRightX, bottomRightY);
}

void IntensityHistogram::findPeakRange(int &leftSide, int &rightSide, int * values, int histogramSize) {
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

void IntensityHistogram::saveToCSV(std::string filename, int * histogram, int arraySize) {
	std::ofstream output(filename);

	if (output.is_open()) {
		output << "sep=,\n";

		for (int i = 0; i < arraySize; i++) {
			output << i << ',' << histogram[i] << std::endl;
		}

		output.close();
	}
}