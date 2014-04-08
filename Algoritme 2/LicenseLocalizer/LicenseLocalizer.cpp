// LicenseLocalizer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <iostream>
#include "LicenseLocalizer.h"
#include "MedianDifferenceAlgorithm.h"
#include "GrayScale.h"
#include "DynamicMedian.h"
#include "SobelFilter.h"
#include "Threshold.h"
#include "Histogram.h"
#include "HighPassFilter.h"
#include "OtsuThresholdFilter.h"
#include "RobertsCrossEdgeDetection.h"

using namespace std;


int _tmain(int argc, _TCHAR* argv[])
{
	Image img("kenteken.jpg");
	Threshold threshold;
	
	//DynamicMedian median(3);
	//median.DoMedian(img);

	MedianDifferenceAlgorithm::doAlgorithm(img);
	//img.SaveImageToFile("filter-");

	HighPassFilter::doAlgorithm(img);
	//img.SaveImageToFile("high-");

	threshold.CreateThresholdImage(img);

	//img.SaveImageToFile("thresh-");

	Histogram histogram(img);
	histogram.SaveToCSV("output.csv");

	img.SaveImageToFile("final-");

	/*
	GrayScale gs;
	gs.CreateGrayScaleImage(img);

	
	DynamicMedian median(11);
	median.DoMedian(img);


	OtsuThresholdFilter::doAlgorithm(img);
	RobertsCrossEdgeDetection::doAlgorithm(img);

	img.SaveImageToFile("grayscaled-");


	img.SaveImageToFile("mediandifference-");
		
	SobelFilter sobel;
	sobel.CreateSobelImage(img);

	Threshold threshold;
	threshold.CreateThresholdImage(img);

	HighPassFilter::doAlgorithm(img);
	threshold.CreateThresholdImage(img);


	Histogram histogram(img);
	histogram.SaveToCSV("output.csv");
	
	img.SaveImageToFile("grayscale-");*/

	return 0;
}

