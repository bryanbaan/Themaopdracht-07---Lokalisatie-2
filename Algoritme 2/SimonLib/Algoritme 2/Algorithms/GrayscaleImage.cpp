#include "GrayscaleImage.h"
#include <iostream>

ImageGray GrayscaleImage::convertToGrayscale(ImageRGB & image) {
	// Image size.
	int width = image.width();
	int height = image.height();

	// The destination image.
	ImageGray grayImage(width, height);

	// For every pixel in the image.
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			// Get the pixel at position x,y.
			Rgb<unsigned char &> pixelRGB = image.at(x, y);
			unsigned char& pixelGray = grayImage.at(x, y);

			// Convert RGB to grayscale.
			pixelGray = pixelRGB.red * 0.114 + pixelRGB.green * 0.587 + pixelRGB.blue * 0.299;
		}
	}
	
	// Return the gray image.
	return grayImage;
}