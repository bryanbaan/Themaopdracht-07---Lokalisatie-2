#include "Filter.h"

//AUTHOR Bryan Baan & Chanan van Ooijen
Filter::Filter() {
	bt = new BaseTimer();
}


Filter::~Filter() {
	delete bt;
}

//Variable median filter method.
void Filter::CreateMedianFilterImage(Image &sourceImage, Image &destinationImage, int size) {
	//Starting the timer
	bt->reset();
	bt->start();

	//Used for variable median filtering
	int medianSize = size;
	int doubleSize = size*size;
	int halfSize = size / 2;
	//std::cout << halfSize << " " << doubleSize << " " << medianSize << std::endl;

	int median = 0;
	int temp = 0;

	//Initializing the array, where all the pixelvalues will be stored.
	int* window;
	window = (int *)malloc(sizeof(int)* doubleSize); // = arraysize 9

	//Two for lusses to walk through the image.
	//The second set of for lusses are for the median filtering.
	int k = 0;
	for (int x = halfSize; x < sourceImage.GetWidth() - halfSize; x++) {
		for (int y = halfSize; y < sourceImage.GetHeight() - halfSize; y++) {
			for (int newX = (x - halfSize); newX <= (x + halfSize); newX++) {
				for (int newY = (y - halfSize); newY <= (y + halfSize); newY++) {
					window[k] = sourceImage.GetPixelRed(newX, newY);
					k++;
				}
			}
			
			//This for lus is for the comparison for determination of the median.
			for (int index = 0; index < doubleSize; index++) {
				temp = window[index];
				//Biggest value will be the highest number in the array
				while ((index - 1 >= 0) && (temp < window[index - 1])) {
					window[index] = window[index - 1];
					index--;
				}
				window[index] = temp;
			}
			median = window[doubleSize / 2];
			destinationImage.SetPixel(x, y, median << redPixelShift | median << greenPixelShift | median << bluePixelShift);

			k = 0;
			temp = 0;
		}
	}
	//These 4 following sets of for lusses are used to create a black stroke at the edge of the image so it will
	//not cause any harm in further image processing.

	//Topleft to bottomleft stroke
	for (int x = 0; x < halfSize; x++) {
		for (int y = 0; y < sourceImage.GetHeight(); y++){
			destinationImage.SetPixel(x, y, 0 << redPixelShift | 0 << greenPixelShift | 0 << bluePixelShift);
		}
	}
	//Topright to bottomright stroke
	for (int x = sourceImage.GetWidth() - halfSize; x < sourceImage.GetWidth(); x++) {
		for (int y = 0; y < sourceImage.GetHeight(); y++){
			destinationImage.SetPixel(x, y, 0 << redPixelShift | 0 << greenPixelShift | 0 << bluePixelShift);
		}
	}
	//Topright to topleft stroke
	for (int y = 0; y < halfSize; y++) {
		for (int x = 0; x < sourceImage.GetWidth(); x++){
			destinationImage.SetPixel(x, y, 0 << redPixelShift | 0 << greenPixelShift | 0 << bluePixelShift);
		}
	}
	//Bottomright to bottomleft
	for (int y = sourceImage.GetHeight() - halfSize; y < sourceImage.GetHeight(); y++) {
		for (int x = 0; x < sourceImage.GetWidth(); x++){
			destinationImage.SetPixel(x, y, 0 << redPixelShift | 0 << greenPixelShift | 0 << bluePixelShift);
		}
	}
	bt->stop();
	std::cout << "Time for the Median filter function: " << bt->elapsedMicroSeconds() << " Microseconds (" << bt->elapsedMilliSeconds() << "ms)" << std::endl;
}

//Variable minimum filter method.
void Filter::CreateMinimumFilterImage(Image &sourceImage, Image &destinationImage, int size) {
	//Starting the timer
	bt->reset();
	bt->start();

	//Used for variable minimum filtering
	int medianSize = size;
	int doubleSize = size*size;
	int halfSize = size / 2;
	//std::cout << halfSize << " " << doubleSize << " " << medianSize << std::endl;

	int median = 0;
	int temp = 0;

	//Initializing the array, where all the pixelvalues will be stored.
	int* window;
	window = (int *)malloc(sizeof(int)* doubleSize); // = arraysize 9

	//Two for lusses to walk through the image.
	//The second set of for lusses are for the median filtering.
	int k = 0;

	for (int x = halfSize; x < sourceImage.GetWidth() - halfSize; x++) {
		for (int y = halfSize; y < sourceImage.GetHeight() - halfSize; y++) {
			for (int newX = (x - halfSize); newX <= (x + halfSize); newX++) {
				for (int newY = (y - halfSize); newY <= (y + halfSize); newY++) {
					window[k] = sourceImage.GetPixelRed(newX, newY);
					k++;
				}
			}

			//This for lus is for the comparison for determination of the median.
			for (int index = 0; index < doubleSize; index++) {
				temp = window[index];
				//Biggest value will be the highest number in the array
				while ((index - 1 >= 0) && (temp < window[index - 1])) {
					window[index] = window[index - 1];
					index--;
				}
				window[index] = temp;
			}
			median = window[doubleSize - doubleSize];
			destinationImage.SetPixel(x, y, median << redPixelShift | median << greenPixelShift | median << bluePixelShift);

			k = 0;
			temp = 0;
		}
	}
	//These 4 following sets of for lusses are used to create a black stroke at the edge of the image so it will
	//not cause any harm in further image processing.

	for (int x = 0; x < halfSize; x++) {
		for (int y = 0; y < sourceImage.GetHeight(); y++){
			destinationImage.SetPixel(x, y, 0 << redPixelShift | 0 << greenPixelShift | 0 << bluePixelShift);
		}
	}
	for (int x = sourceImage.GetWidth() - halfSize; x < sourceImage.GetWidth(); x++) {
		for (int y = 0; y < sourceImage.GetHeight(); y++){
			destinationImage.SetPixel(x, y, 0 << redPixelShift | 0 << greenPixelShift | 0 << bluePixelShift);
		}
	}for (int y = 0; y < halfSize; y++) {
		for (int x = 0; x < sourceImage.GetWidth(); x++){
			destinationImage.SetPixel(x, y, 0 << redPixelShift | 0 << greenPixelShift | 0 << bluePixelShift);
		}
	}
	for (int y = sourceImage.GetHeight() - 5; y < sourceImage.GetHeight(); y++) {
		for (int x = 0; x < sourceImage.GetWidth(); x++){
			destinationImage.SetPixel(x, y, 0 << redPixelShift | 0 << greenPixelShift | 0 << bluePixelShift);
		}
	}
	bt->stop();
	std::cout << "Time for the Minimum filter function: " << bt->elapsedMicroSeconds() << " Microseconds (" << bt->elapsedMilliSeconds() << "ms)" << std::endl;
}

//Variable maximum filter method.
void Filter::CreateMaximumFilterImage(Image &sourceImage, Image &destinationImage, int size) {
	//Starting the timer
	bt->reset();
	bt->start();

	//Used for variable maximum filtering
	int medianSize = size;
	int doubleSize = size*size;
	int halfSize = size / 2;
	//std::cout << halfSize << " " << doubleSize << " " << medianSize << std::endl;

	int median = 0;
	int temp = 0;

	//Initializing the array, where all the pixelvalues will be stored.
	int* window;
	window = (int *)malloc(sizeof(int)* doubleSize); // = arraysize 9

	//Two for lusses to walk through the image.
	//The second set of for lusses are for the median filtering.
	int k = 0;

	for (int x = halfSize; x < sourceImage.GetWidth() - halfSize; x++) {
		for (int y = halfSize; y < sourceImage.GetHeight() - halfSize; y++) {
			for (int newX = (x - halfSize); newX <= (x + halfSize); newX++) {
				for (int newY = (y - halfSize); newY <= (y + halfSize); newY++) {
					window[k] = sourceImage.GetPixelRed(newX, newY);
					k++;
				}
			}

			//This for lus is for the comparison for determination of the maximum.
			for (int index = 0; index < doubleSize; index++) {
				temp = window[index];
				//Biggest value will be the highest number in the array
				while ((index - 1 >= 0) && (temp < window[index - 1])) {
					window[index] = window[index - 1];
					index--;
				}
				window[index] = temp;
			}
			median = window[doubleSize - 1];
			destinationImage.SetPixel(x, y, median << redPixelShift | median << greenPixelShift | median << bluePixelShift);

			k = 0;
			temp = 0;
		}
	}
	//These 4 following sets of for lusses are used to create a black stroke at the edge of the image so it will
	//not cause any harm in further image processing.

	for (int x = 0; x < halfSize; x++) {
		for (int y = 0; y < sourceImage.GetHeight(); y++){
			destinationImage.SetPixel(x, y, 0 << redPixelShift | 0 << greenPixelShift | 0 << bluePixelShift);
		}
	}
	for (int x = sourceImage.GetWidth() - halfSize; x < sourceImage.GetWidth(); x++) {
		for (int y = 0; y < sourceImage.GetHeight(); y++){
			destinationImage.SetPixel(x, y, 0 << redPixelShift | 0 << greenPixelShift | 0 << bluePixelShift);
		}
	}for (int y = 0; y < halfSize; y++) {
		for (int x = 0; x < sourceImage.GetWidth(); x++){
			destinationImage.SetPixel(x, y, 0 << redPixelShift | 0 << greenPixelShift | 0 << bluePixelShift);
		}
	}
	for (int y = sourceImage.GetHeight() - 5; y < sourceImage.GetHeight(); y++) {
		for (int x = 0; x < sourceImage.GetWidth(); x++){
			destinationImage.SetPixel(x, y, 0 << redPixelShift | 0 << greenPixelShift | 0 << bluePixelShift);
		}
	}
	bt->stop();
	std::cout << "Time for the Maximum filter function: " << bt->elapsedMicroSeconds() << " Microseconds (" << bt->elapsedMilliSeconds() << "ms)" << std::endl;
}
