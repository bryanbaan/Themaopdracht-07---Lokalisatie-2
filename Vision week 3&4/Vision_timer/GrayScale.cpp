#include "GrayScale.h"
//#define redPixel 24
//#define greenPixel 16
//#define bluePixel 8
//#define alphaPixel 0

GrayScale::GrayScale() {
	bt = new BaseTimer();
}


GrayScale::~GrayScale() {
	delete bt;
}

void GrayScale::CreateGrayScaleImage(Image &sourceImage, Image &destinationImage) {
	bt->reset();
	bt->start();

	if(sourceImage.GetWidth() != destinationImage.GetWidth() && sourceImage.GetHeight() != destinationImage.GetHeight()) {
		std::cout << "Error images are not the same size" << std::endl;
		return;
	}

	int grayValue;

	for(int y = sourceImage.GetHeight() - 1; y >= 0; y--) {
		for(int x = sourceImage.GetWidth() - 1; x >= 0; x--) {
			grayValue = (int)((sourceImage.GetPixelRed(x, y) * 0.30) + (sourceImage.GetPixelGreen(x, y) * 0.59) + (sourceImage.GetPixelBlue(x, y) * 0.11));
			destinationImage.SetPixel(x, y, (grayValue << redPixelShift) | (grayValue << greenPixelShift) | (grayValue << bluePixelShift));
		}
	}

	bt->stop();
	std::cout << "Time for the Grayscale function: " << bt->elapsedMicroSeconds() << " Microseconds (" << bt->elapsedMilliSeconds() << "ms)" << std::endl;
}
