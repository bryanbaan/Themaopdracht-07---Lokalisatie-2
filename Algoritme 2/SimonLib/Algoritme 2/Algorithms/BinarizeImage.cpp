#include "BinarizeImage.h"

void BinarizeImage::binarizeImage(ImageRGB & image, int threshold) {
	int width = image.width();
	int height = image.height();

	ImageGray grayImage(width, height);

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			Rgb<unsigned char &> pixelRGB = image.at(x, y);

			int value = 0;

			if (pixelRGB.red > threshold) {
				value = 255;
			}

			pixelRGB.red = value;
			pixelRGB.green = value;
			pixelRGB.blue = value;
		}
	}
}