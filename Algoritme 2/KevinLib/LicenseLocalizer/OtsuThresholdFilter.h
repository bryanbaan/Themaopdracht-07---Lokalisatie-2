#ifndef OTSUTHRESHOLDFILTER_H
#define OTSUTHRESHOLDFILTER_H

#include "stdafx.h"
#include "Image.h"

// Author: Mitchell Werensteijn
// Source: http://www.codeproject.com/Articles/38319/Famous-Otsu-Thresholding-in-C

class OtsuThresholdFilter {
public:
	static void doAlgorithm(Image & image) {
		int threshold = getOtsuThreshold(image) * 1.3; // keer 1.3 of niet :S?
		int size = image.GetWidth() * image.GetHeight();

		Pixel * pixel = (Pixel*) image.GetDataPointer();

		int value;
		for (int i = 0; i < size; i++) {
			if (pixel->R > threshold) {
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

	static int getOtsuThreshold(Image & image) {
		// The threshold which will be returned.
		unsigned char threshold = 0;
		float * vet = new float[256];

		// Initialize histogram.
		int * hist = new int[256];
		// Initialize every histogram value to zero.
		for (int i = 0; i < 256; i++) {
			hist[i] = 0;
		}
		
		// Image size, to loop through image.
		int size = image.GetWidth() * image.GetHeight() * 4;

		// Data pointer to the RGBA data.
		unsigned char * dataPointer = (unsigned char *) image.GetDataPointer();

		// Generate Histogram.
		for (int i = 1; i < size; i += 4) {
			hist[dataPointer[i]]++;
		}

		float p1, p2, p12;

		// loop through all possible threshold values and maximize between class variance
		for (int i = 1; i != 255; i++)
		{
			p1 = Px(0, i, hist);
			p2 = Px(i + 1, 255, hist);
			
			p12 = p1 * p2;

			if (p12 == 0) {
				p12 = 1;
			}

			float diff = (Mx(0, i, hist) * p2) - (Mx(i + 1, 255, hist) * p1);
			vet[i] = (float)diff * diff / p12;
		}


		threshold = (unsigned char) findMax(vet, 256);

		delete[] vet;
		delete[] hist;

		return threshold;
	}

	// function is used to compute the q values in the equation
	static float Px(int init, int end, int * hist)
	{
		int sum = 0;
		int i;
		for (i = init; i <= end; i++) {
			sum += hist[i];
		}

		return (float)sum;
	}

	// function is used to compute the mean values in the equation (mu)
	static float Mx(int init, int end, int * hist)
	{
		int sum = 0;
		int i;
		for (i = init; i <= end; i++) {
			sum += i * hist[i];
		}

		return (float)sum;
	}

	// finds the maximum element in a vector
	static int findMax(float * vec, int n)
	{
		float maxVec = 0;
		int idx = 0;
		int i;

		for (i = 1; i < n - 1; i++)
		{
			if (vec[i] > maxVec)
			{
				maxVec = vec[i];
				idx = i;
			}
		}

		return idx;
	}
};

#endif