#include "Hough.h"
//#define redPixel 24
//#define greenPixel 16
//#define bluePixel 8
//#define alphaPixel 0


void Hough::Transform(Image &sourceImage, Image &destinationImage){
	int width = sourceImage.GetWidth();
	int height = sourceImage.GetHeight();

	//Create the accu  
	double hough_h = ((sqrt(2.0) * (double)(height>width ? height : width)) / 2.0);
	int accumulatedHeight = hough_h * 2.0; // -r -> +r  
	int accumulatedWidth = 180;

	int* accumulatedValue = (int*)calloc(accumulatedHeight * accumulatedWidth, sizeof(unsigned int));

	double center_x = width / 2;
	double center_y = height / 2;


	for (int y = 0; y<height; y++){
		for (int x = 0; x<width; x++){
			if (img_data[(y*w) + x] > 250){
				for (int t = 0; t<180; t++){
					double r = (((double)x - center_x) * cos((double)t * DEG2RAD)) + (((double)y - center_y) * sin((double)t * DEG2RAD));
					_accu[(int)((round(r + hough_h) * 180.0)) + t]++;
				}
			}
		}
	}

	return 0;
}