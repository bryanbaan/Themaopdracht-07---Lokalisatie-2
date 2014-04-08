#include "stdafx.h"
#include "Threshold.h"

//AUTHOR Mitchell Werensteijn

void Threshold::CreateThresholdImage(Image &destinationImage) {
	// To be used on a grayscaled image.

	int size = destinationImage.GetWidth() * destinationImage.GetHeight();

	Pixel * pixel = (Pixel*) destinationImage.GetDataPointer();

	int value;
	for (int i = 0; i < size; i++) {
		if (pixel->R > 127) {
			value = 255;
		}
		else {
			value = 0;
		}

		pixel->B = value;
		pixel->G = value;
		pixel->R = value;

		pixel++;
	}
}



