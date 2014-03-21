#include "Histogram.h"

//AUTHOR Bryan Baan & Chanan van Ooijen
using namespace std;
Histogram::Histogram() {
	bt = new BaseTimer();
}

Histogram::~Histogram() {
	delete bt;
}

void Histogram::CreateNormalizedHistogramCOLOR(Image &sourceImage, int binnr) {
	int HEIGHT = sourceImage.GetHeight();
	int WIDTH = sourceImage.GetWidth();
	int totalPixels = 0;
	float normalize;
	int red = 0;
	int green = 0;
	int blue = 0;

	ofstream histogramRed;
	ofstream histogramGreen;
	ofstream histogramBlue;

	int* redArray;
	int* blueArray;
	int* greenArray;
	redArray = (int *)malloc(sizeof(int)* binnr);
	greenArray = (int *)malloc(sizeof(int)* binnr);
	blueArray = (int *)malloc(sizeof(int)* binnr);

	histogramRed.open("../Histogrammen/histogram_RED.csv", ios::out);
	histogramGreen.open("../Histogrammen/histogram_GREEN.csv", ios::out);
	histogramBlue.open("../Histogrammen/histogram_BLUE.csv", ios::out);

	for (int i = 0; i < binnr; i++){
		redArray[i] = 0;
		greenArray[i] = 0;
		blueArray[i] = 0;
	}

	for (int i = 0; i < WIDTH; i++) {
		//cout << WIDTH << endl;
		for (int j = 0; j < HEIGHT; j++) {
			//cout << HEIGHT << endl;
			red = sourceImage.GetPixelRed(i, j);
			redArray[(int)((red * binnr) / 256)] ++;
		}
	}
	for (int i = 0; i < WIDTH; i++) {
		//cout << WIDTH << endl;
		for (int j = 0; j < HEIGHT; j++) {
			//cout << HEIGHT << endl;
			blue = sourceImage.GetPixelBlue(i, j);
			blueArray[(int)((blue * binnr) / 256)] ++;
		}
	}
	for (int i = 0; i < WIDTH; i++) {
		//cout << WIDTH << endl;
		for (int j = 0; j < HEIGHT; j++) {
			//cout << HEIGHT << endl;
			green = sourceImage.GetPixelGreen(i, j);
			greenArray[(int)((green * binnr) / 256)] ++;
		}
	}

	for (int i = 0; i < binnr; i++){
		totalPixels += redArray[i];
	}

	for (int i = 0; i < binnr; i++){
		normalize = redArray[i] / float(totalPixels);
		histogramRed << i << ',' << normalize << endl;
	}
	for (int i = 0; i < binnr; i++){
		normalize = blueArray[i] / float(totalPixels);
		histogramGreen << i << ',' << normalize << endl;
	}
	for (int i = 0; i < binnr; i++){
		normalize = greenArray[i] / float(totalPixels);
		histogramBlue << i << ',' << normalize << endl;
	}
}

void Histogram::CreateNormalizedHistogramGRAY(Image &sourceImage, int binnr) {
	int HEIGHT = sourceImage.GetHeight();
	int WIDTH = sourceImage.GetWidth();
	int totalPixels = 0;
	float normalize;
	int red = 0;

	ofstream histogramGray;

	int* grayArray;
	grayArray = (int *)malloc(sizeof(int)* binnr);
	
	string binnumber = "../Histogrammen/histogram_GRAY_" + std::to_string(binnr);
	string output = binnumber + ".csv";

	histogramGray.open(output, ios::out);

	for (int i = 0; i < binnr; i++){
		grayArray[i] = 0;
	}

	for (int i = 0; i < WIDTH; i++) {
		//cout << WIDTH << endl;
		for (int j = 0; j < HEIGHT; j++) {
			//cout << HEIGHT << endl;
			red = sourceImage.GetPixelRed(i, j);
			grayArray[(int)((red * binnr) / 256)] ++;
		}
	}

	for (int i = 0; i < binnr; i++){
		totalPixels += grayArray[i];
	}

	for (int i = 0; i < binnr; i++){
		normalize = grayArray[i] / float(totalPixels);
		histogramGray << i << "," << normalize << endl;
	}
}