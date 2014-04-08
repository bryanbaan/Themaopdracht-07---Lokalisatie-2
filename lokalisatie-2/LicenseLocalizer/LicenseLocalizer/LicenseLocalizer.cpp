// LicenseLocalizer.cpp : Defines the entry point for the console application.
//

/*
*
*	Author: Mike Schaap
*/


#include "stdafx.h"
#include "LicenseLocalizer.h"
#include <ctime>

using namespace std;


int _tmain(int argc, _TCHAR* argv[])
{
	string inputFile;
	int test = 1;

	//cout << "Please specify input file:" << "\n";
	//cin >> inputFile;

	inputFile = "license_plate_";
	//stringstream ss;
	clock_t start = clock();
	for (test = 1; test <= 18; test++) {
		string final_plate =  inputFile + to_string(test) + ".jpg";
		//std::cout << final_plate << std::endl;
		Image inputImage(final_plate);
		Image original(inputImage);
		Threshold th;
		BlobDetection bd;

		//Perform Threshold
		th.doAlgorithm(inputImage);
		bd.Invoke(inputImage, (inputImage.GetHeight() * inputImage.GetWidth()) * 0.002);

		inputImage.SaveImageToFile("v1");		
	}
	clock_t end = clock();
	std::cout << "blob detection took: " << ((end - start) / (double)CLOCKS_PER_SEC) << "\n";
	std::cin.get();
	return 0;
}

