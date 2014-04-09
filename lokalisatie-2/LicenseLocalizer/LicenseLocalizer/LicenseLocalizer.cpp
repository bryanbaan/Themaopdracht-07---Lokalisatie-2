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
	string inputFile = "license_plate_";

	YellowColorFilter ycf;
	BlobDetection bd;
	BlobCheck bc;

	for (int test = 1; test <= 23; test++) {
		string final_plate =  "c:\\test\\" + inputFile + to_string(test) + ".jpg";
		string save_final_plate = "c:\\test\\changed_" + inputFile + to_string(test) + ".bmp";

		ImageLib::ImageRGB input (*ImageLib::loadImg(final_plate));

		ycf.filterImage(input);

		int minBlobSize = (input.width() * input.height()) * 0.0015;

		std::vector<Blob> possibleBlobs = bd.Invoke(input, minBlobSize);

		//std::vector<Blob> licensePlates = bc.CheckIfBlobIsLicensePlate(possibleBlobs, input);

		//std::cout << "Image: " << inputFile << test << "\n";
		//std::cout << "Blobs found: " << possibleBlobs.size() << "\n\n";

		

		ImageLib::saveImg(input, save_final_plate);
		
		//Clear vector memory
		std::vector<Blob>().swap(possibleBlobs); 
		//std::vector<Blob>().swap(licensePlates);
	}
	std::cout << "Program finished";
	std::cin.get();
	return 0;
}

