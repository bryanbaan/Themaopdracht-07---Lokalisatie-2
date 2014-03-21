#include "exectimer.h"
#include <iostream>
#include <stdio.h>
#include <string>
#include "Image.h"
#include "GrayScale.h"
#include "ColorChannelToImage.h"
#include "Histogram.h"
#include "Equalize.h"
#include "Filter.h"
#include "noiser.h"
#include "Cluster.h"
#include "Threshold.h"
#include "BlobCheck.h"

int main(int argc, char** argv) {
	/*=========================     Program parameters     =========================*/

//	std::string inputName = "LenaNoise.jpg";
//	std::string inputName = "Lena.bmp";
//	std::string inputName = "flower.jpg";
//	std::string inputName = "Knikker.bmp";
//	std::string inputName = "TestImage.bmp";
//	std::string inputName = "Busjes.jpg";
//	std::string inputName = "BusjesGroot.jpg";
//	std::string inputName = "meepo.bmp";
	std::string inputName = "Waterfall.jpg";

	

	bool grayOn = true;
	

	/*=========================     Program parameters     =========================*/

	/*
	Read the chosen file
	*/
	if(argv[1] != nullptr) {
		inputName = argv[1];
		std::cout << "File is: " << inputName << "\n\n";
	} else {
		std::cout << "File is: " << inputName << "\n\n";
	}

	//Load the image in the Image class
	Image originalImage(inputName);

	//Filter image with grayscale
	if(grayOn) {

		//Create an Image object called grayImage (which is a copy of originalImage) and converts to gray values
		Image grayImage(originalImage);
		GrayScale gray;
		gray.CreateGrayScaleImage(originalImage, grayImage);
		grayImage.SaveImageToFile("grey_");
		std::cout << std::endl;

		//Creates a Histogram object called hist and makes a histogram from an image and binnumbers 
		Histogram hist;
		hist.CreateNormalizedHistogramGRAY(originalImage, 10);
		hist.CreateNormalizedHistogramGRAY(originalImage, 256);
		hist.CreateNormalizedHistogramCOLOR(grayImage, 10);

		//Creates an Image object called saltAndPepperImage (which is a copy of grayImage) and add salt&pepper-noise
		Image saltAndPepperImage(grayImage);
		noiser noise;
		noise.saltAndPepper(grayImage, saltAndPepperImage, 10);
		saltAndPepperImage.SaveImageToFile("noise_");

		//Creates an Image object called equalizedImage (which is a copy of grayImage) and will equalize the grayImage
		Image equalizedImage(grayImage);
		Equalize equalized;
		equalized.CreateEqualizedImage(grayImage, equalizedImage);
		equalizedImage.SaveImageToFile("equalized_");

		//Creates an Image object called redChannelImage (which is a copy of originalImage) and set blue and green channel to 0 for every pixel (red channel stays untouched)
		Image redChannelImage(originalImage);
		ColorChannelToImage Channel;
		Channel.CreateRedChannelImage(originalImage, redChannelImage);
		redChannelImage.SaveImageToFile("R_");

		//Creates an Image object called greenChannelImage (which is a copy of originalImage) and set blue and red channel to 0 for every pixel (green channel stays untouched)
		Image greenChannelImage(originalImage);
		Channel.CreateGreenChannelImage(originalImage, greenChannelImage);
		greenChannelImage.SaveImageToFile("G_");
		
		//Creates an Image object called blueChannelImage (which is a copy of originalImage) and set red and green channel to 0 for every pixel (blue channel stays untouched)
		Image blueChannelImage(originalImage);
		Channel.CreateBlueChannelImage(originalImage, blueChannelImage);
		blueChannelImage.SaveImageToFile("B_");

		//Creates an Image object called medianFilterImage (which is a copy of saltAndPepperImage) and apply the median filter
		Image medianFilterImage(originalImage);
		Filter filter;
		filter.CreateMedianFilterImage(saltAndPepperImage, medianFilterImage, 3);
		medianFilterImage.SaveImageToFile("median_");

		//Creates an Image object called medianFilterImage (which is a copy of saltAndPepperImage) and apply the minimum filter
		Image minimumFilterImage(originalImage);
		filter.CreateMinimumFilterImage(saltAndPepperImage, minimumFilterImage, 3);
		minimumFilterImage.SaveImageToFile("minimum_");

		//Creates an Image object called medianFilterImage (which is a copy of saltAndPepperImage) and apply the maximum filter
		Image maximumFilterImage(originalImage);
		filter.CreateMaximumFilterImage(saltAndPepperImage, maximumFilterImage, 3);
		maximumFilterImage.SaveImageToFile("maximum_");
		
		Image clusteredGrayImage(originalImage);
		Cluster c;
		c.CreateK_MeansGrayImage(originalImage, clusteredGrayImage, 5, 1);
		clusteredGrayImage.SaveImageToFile("clusterGRAY_");
		
		Image clusteredColorImage(originalImage);
		c.CreateK_MeansColorImage(originalImage, clusteredColorImage, 20, 25);
		clusteredColorImage.SaveImageToFile("clusterCOLOR_");

		Image thresholdImage(grayImage);
		Threshold t;
		t.CreateThresholdImage(grayImage, thresholdImage);
		thresholdImage.SaveImageToFile("threshold_");

		BlobCheck b;
		b.CheckIfBlobIsLicensePlate(&blobobjects);
	}

	//Save the original image
	originalImage.SaveImageToFile("original_");
	std::cout << std::endl;

	//End program
	std::cout << "Program ended, Press a key to continue\n";
	std::cin.ignore();
	return 0;
}


