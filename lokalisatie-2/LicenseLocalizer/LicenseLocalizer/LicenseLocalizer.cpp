// LicenseLocalizer.cpp : Defines the entry point for the console application.
//

/*
*
*	Author: Mike Schaap
*/


#include "stdafx.h"
#include "LicenseLocalizer.h"

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
	th.doAlgorithm(inputImage);

	std::vector<Blob> blobsFound = bd.Invoke(inputImage);

	//std::vector<Blob> validBlobs = bc.CheckIfBlobIsLicensePlate(blobsFound, inputImage);

	//iterate over bloblist and give all blobs a blue color


	//remove all created objects from the memory
	delete &inputImage;
	delete &original;
	delete &th;
	delete &bd;
	delete &bc;

	for (std::vector<Blob>::iterator it = blobsFound.begin(); it != blobsFound.end(); ++it) {
		delete &it;
	}
	
	delete &blobsFound;

	//for (std::vector<Blob>::iterator it = validBlobs.begin(); it != validBlobs.end(); ++it) {
	//	delete &it;
	//}

	//delete &validBlobs;

	return 0;
}

