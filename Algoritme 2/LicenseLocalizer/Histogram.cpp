#include "stdafx.h"
#include "Histogram.h"
#include <fstream>

Histogram::Histogram(Image & image) {
	int width = image.GetWidth();
	int height = image.GetHeight();

	size = height;
	values = new int[size];

	for (int i = 0; i < size; i++) {
		values[i] = 0;
	}

	Pixel * pixel = (Pixel *)image.GetDataPointer();

	int arrayPos;
	for (int y = 0; y < height; y++) {
		arrayPos = y * width;

		int counter = 0;
		for (int x = 0; x < width - 6; x++){
			if (pixel[arrayPos + x].R == 255) {
				values[y]++;
				counter = 0;
			}

			/*if (pixel[arrayPos + x].R == 255) {
			counter++;
			}
			else {
			if (counter > 0 && counter <= 1) {
			values[y]++;
			}

			counter = 0;
			}
			*/
		}
	}

	int distance = 10;

	int max = 0;
	int maxPosition = 0;
	int minPosLeft = 0;
	int minPosRight = 0;
	int min = 30;

	/*for (int i = 0; i < size; i++) {
	if (values[i] > max) {
	max = values[i];
	maxPosition = i;
	}
	}

	int minPosLeft = 0;
	int half = max * 0.25;

	for (int i = maxPosition; i > distance; i--) {
	if (values[i] <= half) {
	if (values[i - distance] >= values[i]) {
	minPosLeft = i;
	break;
	}
	}
	}

	int minPosRight = 0;

	for (int i = maxPosition; i < (height - distance); i++) {
	if (values[i] <= half) {
	if (values[i + distance] >= values[i]) {
	minPosRight = i;
	break;
	}
	}
	}
	*/

	for (int i = 0; i < size; i++) {
		if (values[i] > max) {
			max = values[i];
			maxPosition = i;
		}
		if (values[i] < min){
			min = values[i];
		}
	}

	for (int i = maxPosition; i > distance; i--) {
		if (values[i] == min) {
			minPosLeft = i;
			break;
		}
	}

	for (int i = maxPosition; i < (height - distance); i++) {
		if (values[i] == min) {
			minPosRight = i;
			break;
		}
	}

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

	// DONE

	delete[] values;
	size = width;
	values = new int[size];

	for (int i = 0; i < size; i++) {
		values[i] = 0;
	}

	for (int x = 0; x < width; x++) {
		int counter = 0;
		for (int y = minPosLeft; y < minPosRight; y++) {
			arrayPos = y * width + x;

			if (pixel[arrayPos].R == 255) {
				values[x]++;

				counter = 0;
			}

			/*if (pixel[arrayPos].R == 255) {
			counter++;
			}
			else {
			if (counter == 1)  {
			values[y]++;
			}

			counter = 0;
			}*/
		}
	}
	min = 30;
	int minValue = 0;

	max = 0;
	for (int i = 0; i < size; i++) {
		if (values[i] > max) {
			max = values[i];
			maxPosition = i;
		}
		if (values[i] < min){
			min = values[i];
		}
	}

	for (int i = maxPosition; i > distance; i--) {
		if (values[i] == min) {
			minPosLeft = i;
			break;
		}
	}

	for (int i = maxPosition; i < (width - distance); i++) {
		if (values[i] == min) {
			minPosRight = i;
			break;
		}
	}

	for (int y = 0; y < height; y++) {
		int pos = y * width + minPosLeft;
		pixel[pos].R = 0;
		pixel[pos].G = 255;
		pixel[pos].B = 0;
	}


	for (int y = 0; y < height; y++) {
		int pos = y * width + minPosRight;
		pixel[pos].R = 0;
		pixel[pos].G = 255;
		pixel[pos].B = 0;
	}

	std::cout << "maxPos: " << maxPosition << std::endl;
	//std::cin.get();
}

Histogram::~Histogram() {
	delete[] values;
}

void Histogram::SaveToCSV(std::string filename) {
	std::ofstream output(filename);

	if (output.is_open()) {
		output << "sep=,\n";

		for (int i = 0; i < size; i++) {
			output << i << ',' << values[i] << std::endl;
		}

		output.close();
	}
}