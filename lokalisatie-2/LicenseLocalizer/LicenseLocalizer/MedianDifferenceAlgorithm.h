/*
*
*	Author: Mitchell werensteijn
*/

#ifndef MEDIANDIFFERENCEALGORITHM_H
#define MEDIANDIFFERENCEALGORITHM_H

#include "Image.h"

#include <math.h>

class MedianDifferenceAlgorithm {
public:
	static void doAlgorithm(Image & image) {
		// Create a median filter to 
		Image median(image);

		// DRAAI EEN MEDIAN FILTER!!!
		//MedianFilterAlgorithm mf(3);
		//mf.runAlgorithm(image);

		// Image size;
		int imageSize = image.GetWidth() * image.GetHeight();

		// Create pointers to access the data.
		unsigned int * medDataPtr = median.GetDataPointer();
		unsigned int * destDataPtr = image.GetDataPointer();

		// For every pixel in the image
		for (int i = 0; i < imageSize; i++) {
			// Get the RGB values
			int r = (medDataPtr[i] >> redPixelShift) & 0xFF;
			int g = (medDataPtr[i] >> greenPixelShift) & 0xFF;
			int b = (medDataPtr[i] >> bluePixelShift) & 0xFF; 

			// To save the Hue, Saturtation and Value
			float hue, saturtation, value;

			// Convert RGB to HSV.
			RGB2HSV(r, g, b, hue, saturtation, value);

			// If the color is yellow.
			if (hue >= 30 && hue <= 55 && saturtation >= 0.85) {
				// If the color is within our yellow range, make the output pixel white.
				destDataPtr[i] = ~0;
			} else {
				// Else make the pixel black.
				destDataPtr[i] = 0;
			}
		}
	}

	// Function to convert a RGB value to HSV format.
	// Source: http://en.literateprograms.org/RGB_to_HSV_color_space_conversion_%28C%29
	static void RGB2HSV(float r, float g, float b, float & h, float & s, float & v)
	{
		double min, max, delta;

		// Find the minimum RGB value.
		min = r < g ? r : g;
		min = min  < b ? min : b;

		// Find the maximum RGB value.
		max = r > g ? r : g;
		max = max  > b ? max : b;

		// Set the Value.
		v = max;             

		// Calculate Saturtation.
		delta = max - min;
		if (max > 0.0) {
			s = (delta / max);                  
		} else {
			s = 0.0;
			h = NAN;
			return ;
		}

		// Calculate Hue.
		if (r >= max) {
			// between yellow & magenta.
			h = (g - b) / delta;        
		} else {
			if (g >= max) {
				// between cyan & yellow.
				h = 2.0 + (b - r) / delta;  
			} else {
				// between magenta & cyan.
				h = 4.0 + (r - g) / delta; 
			}
		}

		// Degrees.
		h *= 60.0;                              

		if (h < 0.0) {
			h += 360.0;
		}
	}
};

#endif