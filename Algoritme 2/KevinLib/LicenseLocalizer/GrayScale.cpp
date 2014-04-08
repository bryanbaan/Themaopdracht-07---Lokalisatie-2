#include "stdafx.h"
#include "GrayScale.h"
#include "MedianDifferenceAlgorithm.h"
#include "DynamicMedian.h"
#include <algorithm>

void GrayScale::CreateGrayScaleImage(Image &image) {
	/*
	int size = image.GetWidth() * image.GetHeight();

	Pixel * pixel = (Pixel *)image.GetDataPointer();

	int grayValue;
	for (int i = 0; i < size; i++) {
		grayValue = pixel->B * 0.114 + pixel->G * 0.587 + pixel->R * 0.299;

		pixel->B = grayValue;
		pixel->G = grayValue;
		pixel->R = grayValue;

		pixel++;
	}
	*/
	//Calculate intensity on HSV-> value only.
	int size = image.GetWidth() * image.GetHeight();

	Pixel * pixel = (Pixel *)image.GetDataPointer();

	float h, s, v;
	for (int i = 0; i < size; i++) {
		MedianDifferenceAlgorithm::RGB2HSV(pixel->R, pixel->G, pixel->B, h, s, v);

		pixel->B = v;
		pixel->G = v;
		pixel->R = v;

		pixel++;
	}


}

