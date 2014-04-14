#include "IntensityHistogram.h"
#include <iostream>
#include <fstream>

LicensePosition IntensityHistogram::getLicensePosition(ImageRGB & image, bool generateCSV) {
	// Image size.
	int width = image.width();
	int height = image.height();

	// To hold the top left position of the number plate.
	int topLeftX;
	int topLeftY;

	// To hold the top right position of the number plate.
	int topRightX;
	int topRightY;

	// To hold the bottom left position of the number plate.
	int bottomLeftX;
	int bottomLeftY;

	// To hold the bottom right position of the number plate.
	int bottomRightX;
	int bottomRightY;

	// The size of the vertical histogram.
	int histogramSize = height;

	// To hold the histogram values.
	int * histogram = new int[histogramSize];

	// Set all histogram values to zero.
	for (int i = 0; i < histogramSize; i++) {
		histogram[i] = 0;
	}

	// Increment the amount of white pixels for every horizontal row in the image.
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			// Get the pixel.
			Rgb<unsigned char &> pixelRGB = image.at(x, y);

			// Only increment if the pixel is white.
			if (pixelRGB.red == 255) {
				histogram[y]++;
			}
		}
	}

	// To hold the left side of the peak in the histogram(the top position of the license plate).
	int minPosLeft = 0;
	// To hold the right side of the peak in the histogram(the bottom position of the license plate).
	int minPosRight = 0;

	// Find the peak which will most likely be the license plate.
	findPeakRange(minPosLeft, minPosRight, histogram, histogramSize);

	// y holds the top position of the number plate.
	int y = minPosLeft;
	// Draw a red horizontal line on the top position of the number plate.
	for (int x = 0; x < width; x++) {
		Rgb<unsigned char &> pixelRGB = image.at(x, y);

		pixelRGB.red = 255;
		pixelRGB.green = 0;
		pixelRGB.blue = 0;
	}

	// y holds the bottom position of the number plate.
	y = minPosRight;
	// Draw a red horizontal line on the top position of the number plate.
	for (int x = 0; x < width; x++) {
		Rgb<unsigned char &> pixelRGB = image.at(x, y);

		pixelRGB.red = 255;
		pixelRGB.green = 0;
		pixelRGB.blue = 0;
	}

	// Set the number plate positions.
	topLeftY = minPosLeft;
	topRightY = minPosLeft;
	bottomLeftY = minPosRight;
	bottomRightY = minPosRight;

	// Delete the vertical histogram.
	delete[] histogram;

	// Now create a horizontal histogram.
	histogramSize = width;
	histogram = new int[histogramSize];

	// Set every histogram value to zero.
	for (int i = 0; i < histogramSize; i++) {
		histogram[i] = 0;
	}

	// Increment the amount of white pixels for every vertical row between the top and bottom position of the number plate.
	for (int x = 0; x < width; x++) {
		for (int y = minPosLeft; y < minPosRight; y++) {
			Rgb<unsigned char &> pixelRGB = image.at(x, y);

			// Only increment if the pixel is white.
			if (pixelRGB.red == 255) {
				histogram[x]++;
			}
		}
	}

	// Find the peak which will most likely be the license plate.
	findPeakRange(minPosLeft, minPosRight, histogram, histogramSize);
	
	// x holds the left position of the number plate.
	int x = minPosLeft;
	// Draw a green vertical line on the left position of the number plate.
	for (int y = 0; y < height; y++) {
		Rgb<unsigned char &> pixelRGB = image.at(x, y);

		pixelRGB.red = 0;
		pixelRGB.green = 255;
		pixelRGB.blue = 0;
	}

	// x holds the right position of the number plate.
	x = minPosRight;
	// Draw a green vertical line on the right position of the number plate.
	for (int y = 0; y < height; y++) {
		Rgb<unsigned char &> pixelRGB = image.at(x, y);

		pixelRGB.red = 0;
		pixelRGB.green = 255;
		pixelRGB.blue = 0;
	}

	// Set the number plate positions.
	topLeftX = minPosLeft;
	topRightX = minPosRight;
	bottomLeftX = minPosLeft;
	bottomRightX = minPosRight;
	
	// Delete histogram.
	delete[] histogram;

	// Return positions.
	return LicensePosition(topLeftX, topLeftY, topRightX, topRightY, bottomLeftX, bottomLeftY, bottomRightX, bottomRightY);
}

void IntensityHistogram::findPeakRange(int &leftSide, int &rightSide, int * values, int histogramSize) {
	// maxValue holds the top value of the peak.
	int maxValue = 0;
	// maxPosition holds the top position of the peak.
	int maxPosition = 0;

	// Hold the minimum value of the peak.
	int minValue = MAXIMUMMINVALUE;

	// Find the maximum and minimum value.
	for (int i = 0; i < histogramSize; i++) {
		if (values[i] > maxValue) {
			maxValue = values[i];
			maxPosition = i;
		}
		if (values[i] < minValue){
			minValue = values[i];
		}
	}

	// Find the left side of the peak.
	for (int i = maxPosition; i > 0; i--) {
		if (values[i] == minValue) {
			leftSide = i;
			break;
		}
	}

	// Find the right side of the peak.
	for (int i = maxPosition; i < (histogramSize); i++) {
		if (values[i] == minValue) {
			rightSide = i;
			break;
		}
	}
}

void IntensityHistogram::saveToCSV(std::string filename, int * histogram, int arraySize) {
	// Open a file.
	std::ofstream output(filename);

	if (output.is_open()) {
		// Set delimiter to a comma.
		output << "sep=,\n";

		// Write every histogram value to a file.
		for (int i = 0; i < arraySize; i++) {
			output << i << ',' << histogram[i] << std::endl;
		}

		// Close the file.
		output.close();
	}
}