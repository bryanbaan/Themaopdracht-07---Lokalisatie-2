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

	cout << "Please specify input file:" << "\n";
	cin >> inputFile;

	Image inputImage(inputFile);
	Image original(inputImage);
	Threshold th;
	BlobDetection bd;
	BlobCheck bc;

	//Perform Threshold
	clock_t start = clock();
	th.doAlgorithm(inputImage);

	
	bd.Invoke(inputImage, 500);
	clock_t end = clock();
	std::cout << "blob detection took: " << ((end - start) / (double)CLOCKS_PER_SEC) << "\n";

	//std::vector<Blob> validBlobs = bc.CheckIfBlobIsLicensePlate(blobsFound, inputImage);

	return 0;
}

