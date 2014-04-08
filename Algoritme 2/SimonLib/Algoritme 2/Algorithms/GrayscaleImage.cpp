#include "GrayscaleImage.h"
#include <iostream>
using std::vector;

ImageGray GrayscaleImage::convertToGrayscale(ImageRGB & image) {
	int width = image.width();
	int height = image.height();

	ImageGray grayImage(width, height);

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			Rgb<unsigned char &> pixelRGB = image.at(x, y);
			unsigned char& pixelGray = grayImage.at(x, y);

			pixelGray = pixelRGB.red * 0.114 + pixelRGB.green * 0.587 + pixelRGB.blue * 0.299;
		}
	}
	
	return grayImage;
}