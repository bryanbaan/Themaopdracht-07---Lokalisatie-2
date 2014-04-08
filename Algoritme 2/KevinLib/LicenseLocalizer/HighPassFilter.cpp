#include "stdafx.h"
#include "HighPassFilter.h"

void HighPassFilter::doAlgorithm(Image & image) {
	// Create a copy of the source.
	Image source(image);

	// The high-pass filter that will be applied.
	int filter[3][3] = {{-1, -1, -1}, 
						{-1,  8, -1}, 
						{-1, -1, -1}};

	// Image width.
	int width = image.GetWidth();

	int beginY = 1;
	int beginX = 1;

	int endY = image.GetHeight() - 1;
	int endX = width - 1;

	Pixel * sourceData = (Pixel*)source.GetDataPointer();
	Pixel * destData = (Pixel*)image.GetDataPointer();

	int arrayPos, pos;
	for (int y = beginY; y < endY; y++) {
		for (int x = beginX; x < endX; x++) {
			arrayPos = y * width + x;

			int newValue = 0;

			for (int my = -1; my <= 1; my++) {
				for (int mx = -1; mx <= 1; mx++) {
					pos = (arrayPos + (my * width)) + mx;

					newValue += sourceData[pos].R * filter[my + 1][mx + 1];
				}
			}

			newValue /= 9;

			destData[arrayPos].R = newValue;
			destData[arrayPos].G = newValue;
			destData[arrayPos].B = newValue;
		}
	}
}