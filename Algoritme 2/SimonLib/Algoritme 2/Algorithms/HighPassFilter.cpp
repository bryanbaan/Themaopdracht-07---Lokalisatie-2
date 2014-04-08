#include "HighPassFilter.h"
#include <iostream>
using std::vector;

void HighPassFilter::filterImage(ImageRGB &image) {
	//Create a copy of the source
	ImageRGB source(image);

	//The high-pass filter that will be applied.
	int filter[3][3] = {	{ -1, -1, -1 },
							{ -1, 8, -1 },
							{ -1, -1, -1 } };

	//Image width.
	int width = image.width();

	int beginY = 1;
	int beginX = 1;
	int endY = image.height() - 1;
	int endX = width - 1;

	for (int y = beginY; y < endY; y++) {
		for (int x = beginX; x < endX; x++) {
			int newValue = 0;
			for (int my = -1; my <= 1; my++) {
				for (int mx = -1; mx <= 1; mx++) {
					Rgb<unsigned char &> pixelRGB = source.at(mx + x, my + y);
					newValue += pixelRGB.red * filter[my + 1][mx + 1];
				}
			}

			newValue /= 9;

			image.at(x, y).red = newValue;
			image.at(x, y).green = newValue;
			image.at(x, y).blue = newValue;
		}
	}
							
}