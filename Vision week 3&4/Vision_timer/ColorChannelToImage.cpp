#include "ColorChannelToImage.h"
//#define redPixel 24
//#define greenPixel 16
//#define bluePixel 8
//#define alphaPixel 0

ColorChannelToImage::ColorChannelToImage() {
	bt = new BaseTimer();
}


ColorChannelToImage::~ColorChannelToImage() {
	delete bt;
}

void ColorChannelToImage::CreateRedChannelImage(Image &sourceImage, Image &destinationImage) {
	bt->reset();
	bt->start();

	if (sourceImage.GetWidth() != destinationImage.GetWidth() && sourceImage.GetHeight() != destinationImage.GetHeight()) {
		std::cout << "Error images are not the same size" << std::endl;
		return;
	}

	for (int y = sourceImage.GetHeight() - 1; y >= 0; y--) {
		for (int x = sourceImage.GetWidth() - 1; x >= 0; x--) {
			int redColor = sourceImage.GetPixelRed(x, y);
			destinationImage.SetPixel(x, y, (redColor << redPixelShift) | (0 << greenPixelShift) | (0 << bluePixelShift));
		}
	}

	bt->stop();
	std::cout << "Time for the RedChannel function: " << bt->elapsedMicroSeconds() << " Microseconds (" << bt->elapsedMilliSeconds() << "ms)" << std::endl;
}

void ColorChannelToImage::CreateGreenChannelImage(Image &sourceImage, Image &destinationImage) {
	bt->reset();
	bt->start();

	if (sourceImage.GetWidth() != destinationImage.GetWidth() && sourceImage.GetHeight() != destinationImage.GetHeight()) {
		std::cout << "Error images are not the same size" << std::endl;
		return;
	}

	for (int y = sourceImage.GetHeight() - 1; y >= 0; y--) {
		for (int x = sourceImage.GetWidth() - 1; x >= 0; x--) {
			int greenColor = sourceImage.GetPixelGreen(x, y);
			destinationImage.SetPixel(x, y, (0 << redPixelShift) | (greenColor << greenPixelShift) | (0 << bluePixelShift));
		}
	}

	bt->stop();
	std::cout << "Time for the GreenChannel function: " << bt->elapsedMicroSeconds() << " Microseconds (" << bt->elapsedMilliSeconds() << "ms)" << std::endl;
}

void ColorChannelToImage::CreateBlueChannelImage(Image &sourceImage, Image &destinationImage) {
	bt->reset();
	bt->start();

	if (sourceImage.GetWidth() != destinationImage.GetWidth() && sourceImage.GetHeight() != destinationImage.GetHeight()) {
		std::cout << "Error images are not the same size" << std::endl;
		return;
	}

	for (int y = sourceImage.GetHeight() - 1; y >= 0; y--) {
		for (int x = sourceImage.GetWidth() - 1; x >= 0; x--) {
			int blueColor = sourceImage.GetPixelBlue(x, y);
			destinationImage.SetPixel(x, y, (0 << redPixelShift) | (0 << greenPixelShift) | (blueColor << bluePixelShift));
		}
	}

	bt->stop();
	std::cout << "Time for the BlueChannel function: " << bt->elapsedMicroSeconds() << " Microseconds (" << bt->elapsedMilliSeconds() << "ms)" << std::endl;
}
