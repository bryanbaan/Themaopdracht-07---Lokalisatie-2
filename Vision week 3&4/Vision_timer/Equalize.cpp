#include "Equalize.h"
//#define redPixel 24
//#define greenPixel 16
//#define bluePixel 8
//#define alphaPixel 0
using namespace std;
Equalize::Equalize() {
	bt = new BaseTimer();
}


Equalize::~Equalize() {
	delete bt;
}

//This method creates an image with equalized grayvalues. (removes foggyness on pictures)
void Equalize::CreateEqualizedImage(Image &sourceImage, Image &destinationImage) {
	bt->reset();
	bt->start();

	int height = sourceImage.GetHeight();
	int width = sourceImage.GetWidth();
	int totalPixels = height * width;
	int pixelValue = 0;

	float alpha = 255 / float(totalPixels);
	float equalized_histogram_array[256];
	float histogram_array[256];

	//The next three for lusses are the creation of the histogram_to_be_equalized.
	for (int i = 0; i < 256; i++){
		histogram_array[i] = 0;
	}
	for (int i = 0; i < width; i++) {
		//cout << WIDTH << endl;
		for (int j = 0; j < height; j++) {
			//cout << HEIGHT << endl;
			pixelValue = sourceImage.GetPixelRed(i, j);
			histogram_array[pixelValue] ++;
		}
	}

	equalized_histogram_array[0] = histogram_array[0] * alpha;

	//This is where the equalization of the normal values will be done.
	for (int i = 1; i < 256; i++){
		equalized_histogram_array[i] = equalized_histogram_array[i - 1] + (histogram_array[i] * alpha);
	}

	

	
	//Here the equalized values will be printed.
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			pixelValue = sourceImage.GetPixelRed(i, j);
			destinationImage.SetPixel(i, j, ((int)equalized_histogram_array[pixelValue] << redPixelShift) | ((int)equalized_histogram_array[pixelValue] << greenPixelShift) | ((int)equalized_histogram_array[pixelValue] << bluePixelShift));
		}
	}

	bt->stop();
	std::cout << "Time for the Equalize function: " << bt->elapsedMicroSeconds() << " Microseconds (" << bt->elapsedMilliSeconds() << "ms)" << std::endl;
}
