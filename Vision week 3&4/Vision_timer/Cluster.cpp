#include "Cluster.h"
#include <stdlib.h>
#include <ctime>
#include <iostream>
using namespace std;

//AUTHOR Bryan Baan & Chanan van Ooijen
Cluster::Cluster() {
	bt = new BaseTimer();
}


Cluster::~Cluster() {
	delete bt;
}

void Cluster::CreateK_MeansGrayImage(Image &sourceImage, Image &destinationImage, int k, int maxIterations) {
	bt->reset();
	bt->start();
	int HEIGHT = sourceImage.GetHeight();
	int WIDTH = sourceImage.GetWidth();
	int totalPixels = HEIGHT * WIDTH;
	srand((unsigned int)time(0));
	int x;
	int y;
	int condition = 0;
	int zones = k;
	//Temp always gets ++'d, so we'll start at -1 to make it [0] and usable for our arrays
	int temp = -1;
	int mean = 0;
	float tempDistance = 0.0f;
	float previousDistance = 0.0f;

	int* meanArray;
	meanArray = (int*)malloc(sizeof(int)* zones);
	int* amountArray;
	amountArray = (int*)malloc(sizeof(int)* zones);
	float pixel[3] = { 0, 0, 0 };

	for (int i = 0; i < zones; i++) {
		meanArray[i] = 0;
		amountArray[i] = 0;
	}


	int** pixelArray = new int*[WIDTH];
	for (int i = 0; i < WIDTH; i++) {
		pixelArray[i] = new int[HEIGHT];
	}
	int** pixelArrayColor = new int*[zones];
	for (int i = 0; i < zones; i++) {
		//This new integer has 3 values (R,G,B)
		pixelArrayColor[i] = new int[3];
	}

	bool stop = true;

	//To define the clustercenters for the first time
	//Debug info: This for loop is correct.
	for (int i = 0; i < zones; i++) {
		x = rand() % WIDTH;
		y = rand() % HEIGHT;
		//cout << x << "," << y << endl;
		pixelArrayColor[i][0] = sourceImage.GetPixelRed(x, y);
		pixelArrayColor[i][1] = sourceImage.GetPixelGreen(x, y);
		pixelArrayColor[i][2] = sourceImage.GetPixelBlue(x, y);
	}

	while (condition < maxIterations) {
		for (int x = 0; x < WIDTH; x++) {
			for (int y = 0; y < HEIGHT; y++) {
				pixel[0] = sourceImage.GetPixelRed(x, y);
				pixel[1] = sourceImage.GetPixelGreen(x, y);
				pixel[2] = sourceImage.GetPixelBlue(x, y);
				previousDistance = 1e99;
				//Checking distance to every clustercenter and saving the closest distanced center
				for (int k = 0; k < zones; k++) {
					tempDistance = sqrt(pow(pixelArrayColor[k][0] - pixel[0], 2) + pow(pixelArrayColor[k][1] - pixel[1], 2) + pow(pixelArrayColor[k][2] - pixel[2], 2));
					if (tempDistance < previousDistance) {
						previousDistance = tempDistance;
						temp = k;
					}
					if (previousDistance < 0) {
						previousDistance = previousDistance *-1;
					}
				}
				amountArray[temp]++;
				meanArray[temp] += sourceImage.GetPixelRed(x, y);
				pixelArray[x][y] = temp;
			}

		}

		//Meaning the value inside the meanArray.
		for (int x = 0; x < zones; x++) {
			if (amountArray[x] != 0){
				meanArray[x] = meanArray[x] / amountArray[x];
			}
		}

		//Setting the mean to all the correct pixels
		for (int x = 0; x < WIDTH; x++) {
			for (int y = 0; y < HEIGHT; y++) {
				//Find what pixels belongs to what zone, and thus what pixel will be set to what mean value.
				//meanArray[pixelArray[x][y] - 1] = the colorvalue that needs to be stored in the pixel now.
				destinationImage.SetPixel(x, y, meanArray[pixelArray[x][y] - 1] << redPixelShift | meanArray[pixelArray[x][y] - 1] << greenPixelShift | meanArray[pixelArray[x][y] - 1] << bluePixelShift);
			}
		}
		condition++;
	}
	free(meanArray);
	free(amountArray);

	bt->stop();
	cout << "Time for the Gray cluster function: " << bt->elapsedMicroSeconds() << " Microseconds (" << bt->elapsedMilliSeconds() << "ms)" << endl;
}

void Cluster::CreateK_MeansColorImage(Image &sourceImage, Image &destinationImage, int k, int maxIterations) {

	//Starting the timer
	bt->reset();
	bt->start();

	int HEIGHT = sourceImage.GetHeight();
	int WIDTH = sourceImage.GetWidth();
	int totalPixels = HEIGHT * WIDTH;
	srand((unsigned int)time(0));
	int x;
	int y;
	int condition = 0;
	int zones = k;
	//Temp always gets ++'d at least once, so we'll start at -1 to make it [0] and usable for our arrays
	int temp = -1;
	int deltaX = 0;
	int deltaY = 0;
	int closestPixel = 0;
	int mean = 0;
	int noZonesChanged = 0;
	float root = 0.0f;
	float tempDistance = 0.0f;
	float previousDistance = 0.0f;

	int* meanArrayRed;
	meanArrayRed = (int*)malloc(sizeof(int)* zones);
	int* meanArrayGreen;
	meanArrayGreen = (int*)malloc(sizeof(int)* zones);
	int* meanArrayBlue;
	meanArrayBlue = (int*)malloc(sizeof(int)* zones);
	int* amountArray;
	amountArray = (int*)malloc(sizeof(int)* zones);
	float pixel[3] = { 0, 0, 0 };

	for (int i = 0; i < zones; i++) {
		meanArrayRed[i] = 0;
		meanArrayGreen[i] = 0;
		meanArrayBlue[i] = 0;
		amountArray[i] = 0;
	}


	int** pixelArray = new int*[WIDTH];
	for (int i = 0; i < WIDTH; i++) {
		pixelArray[i] = new int[HEIGHT];
	}

	int** pixelArrayColor = new int*[zones];
	for (int i = 0; i < zones; i++) {
		//This new integer has 3 values (R,G,B)
		pixelArrayColor[i] = new int[3];
	}

	bool stop = true;

	//To define the clustercenters for the first time
	//Debug info: This for loop is correct.
	for (int i = 0; i < zones; i++) {
		x = rand() % WIDTH;
		y = rand() % HEIGHT;
		cout << x << "," << y << endl;
		pixelArrayColor[i][0] = sourceImage.GetPixelRed(x, y);
		pixelArrayColor[i][1] = sourceImage.GetPixelGreen(x, y);
		pixelArrayColor[i][2] = sourceImage.GetPixelBlue(x, y);
	}

	while (condition < maxIterations) {
		for (int x = 0; x < WIDTH; x++) {
			for (int y = 0; y < HEIGHT; y++) {
				pixel[0] = sourceImage.GetPixelRed(x, y);
				pixel[1] = sourceImage.GetPixelGreen(x, y);
				pixel[2] = sourceImage.GetPixelBlue(x, y);
				//Checking distance to every clustercenter and saving the closest distanced center
				previousDistance = 1e99;
				for (int k = 0; k < zones; k++) {
					tempDistance = sqrt(pow(pixelArrayColor[k][0] - pixel[0], 2) + pow(pixelArrayColor[k][1] - pixel[1], 2) + pow(pixelArrayColor[k][2] - pixel[2], 2));
					if (tempDistance < previousDistance) {
						previousDistance = tempDistance;
						temp = k;
					}
					if (previousDistance < 0) {
						previousDistance = previousDistance *-1;
					}
				}
				amountArray[temp]++;
				meanArrayRed[temp] += sourceImage.GetPixelRed(x, y);
				meanArrayGreen[temp] += sourceImage.GetPixelGreen(x, y);
				meanArrayBlue[temp] += sourceImage.GetPixelBlue(x, y);

				pixelArray[x][y] = temp;

			}

		}

		//Meaning the value inside the meanArray.
		for (int x = 0; x < zones; x++) {
			if (amountArray[x] != 0){
				meanArrayRed[x] = meanArrayRed[x] / amountArray[x];
				meanArrayGreen[x] = meanArrayGreen[x] / amountArray[x];
				meanArrayBlue[x] = meanArrayBlue[x] / amountArray[x];
 			}
		}

		//Setting the mean to all the correct pixels
		for (int x = 0; x < WIDTH; x++) {
			for (int y = 0; y < HEIGHT; y++) {
				//Find what pixels belongs to what zone, and thus what pixel will be set to what mean value.
				//meanArray[pixelArray[x][y] - 1] = the colorvalue that needs to be stored in the pixel now.
				destinationImage.SetPixel(x, y, meanArrayRed[pixelArray[x][y] - 1] << redPixelShift | meanArrayGreen[pixelArray[x][y] - 1] << greenPixelShift | meanArrayBlue[pixelArray[x][y] - 1] << bluePixelShift);
			}
		}

		for (int k = 0; k < zones; k++) {
			if ((pixelArrayColor[k][0] == meanArrayRed[k]) && (pixelArrayColor[k][0] == meanArrayRed[k]) && (pixelArrayColor[k][0] == meanArrayRed[k])){
				noZonesChanged++;
			}
			pixelArrayColor[k][0] = meanArrayRed[k];
			pixelArrayColor[k][1] = meanArrayGreen[k];
			pixelArrayColor[k][2] = meanArrayBlue[k];
			
			
		}
		for (int i = 0; i < zones; i++) {
			meanArrayRed[i] = 0;
			meanArrayGreen[i] = 0;
			meanArrayBlue[i] = 0;
			amountArray[i] = 0;
		}

		condition++;
		if (noZonesChanged == k) {
			condition = maxIterations;
		}
		noZonesChanged = 0;
		
	}

	/*
	for (int k = 0; k < zones; k++) {
		cout << "Clustercenter " << k << " was: " << pixelArrayColor[k][0] << endl;
		cout << "Clustercenter " << k << " was: " << pixelArrayColor[k][1] << endl;
		cout << "Clustercenter " << k << " was: " << pixelArrayColor[k][2] << endl;
	}
	*/
	free(meanArrayRed);
	free(meanArrayGreen);
	free(meanArrayBlue);
	free(amountArray);

	bt->stop();
	cout << "Time for the Color cluster function: " << bt->elapsedMicroSeconds() << " Microseconds (" << bt->elapsedMilliSeconds() << "ms)" << endl;
}
