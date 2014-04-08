#ifndef ROBERTSCROSSEDGEDETECTION_H
#define ROBERTSCROSSEDGEDETECTION_H

// Author: Mitchell Werensteijn
// Source: http://www.robotics.technion.ac.il/courses/advanced_laboratory/lab7/arl_7_read.pdf

#include "stdafx.h"
#include "Image.h"

class RobertsCrossEdgeDetection {
public:
	static void doAlgorithm(Image & image) {
		Image sourceImage(image);

		int srcHeight = sourceImage.GetHeight();
		int srcWidth = sourceImage.GetWidth();

		Pixel * sourcePixel = (Pixel*) sourceImage.GetDataPointer();
		Pixel * pixel = (Pixel *)image.GetDataPointer();

		//The masks
		double kernelX[2][2] = {{1, 0},
								{0, -1}};
		double kernelY[2][2] = {{0, 1},
								{-1, 0}};


		int arrayPos, pos;
		//For each pixel, apply the masks and combine them.
		for (int x = 0; x < srcWidth - 1; x++){
			for (int y = 0; y < srcHeight - 1; y++){
				arrayPos = y * srcWidth + x;

				double magX = 0.0;
				double magY = 0.0;

				for (int ny = 0; ny < 2; ny++) {
					for (int nx = 0; nx < 2; nx++) {
						pos = arrayPos + (ny * srcWidth) + nx;

						magX += sourcePixel[pos].R * kernelX[ny + 1][nx + 1];
						magY += sourcePixel[pos].R * kernelY[ny + 1][nx + 1];
					}
				}

				if (magX < 0) { magX = 0; }
				else if (magX > 255) { magX = 255; }
				if (magY < 0) { magY = 0; }
				else if (magY > 255) { magY = 255; }

				//Combine the masks 
				double mag = sqrt(magX * magX + magY * magY);

				if (mag < 0) { mag = 0; }
				else if (mag > 255) { mag = 255; }

				int mg = (int)mag;

				pixel[arrayPos].R = mg;
				pixel[arrayPos].G = mg;
				pixel[arrayPos].B = mg;
			}
		}
	}
};

#endif