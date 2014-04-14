#include "BinarizeImage.h"

void BinarizeImage::binarizeImage(ImageRGB & image, int threshold) {
	// Image size to loop trough the image.
	int width = image.width();
	int height = image.height();

	// Grayscale the image.
	ImageGray grayImage(width, height);

	// For every pixel in the image.
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			// Get the pixel at position x,y.
			Rgb<unsigned char &> pixelRGB = image.at(x, y);

			int value = 0;

			// If the pixel color is larger than the given threshold(default = 127), make the pixel white.
			if (pixelRGB.red > threshold) {
				value = 255;
			}

			// Set the pixel.
			pixelRGB.red = value;
			pixelRGB.green = value;
			pixelRGB.blue = value;
		}
	}
}