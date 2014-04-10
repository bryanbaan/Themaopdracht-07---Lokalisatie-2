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

	for (int test = 1; test <= 18; test++) {
		string final_plate =  "c:\\test\\" + inputFile + to_string(test) + ".jpg";
		string save_final_plate = "c:\\test\\changed_" + inputFile + to_string(test) + ".bmp";

		ImageLib::ImageRGB input (*ImageLib::loadImg(final_plate));

		ycf.filterImage(input);

		int minBlobSize = (input.width() * input.height()) * 0.0015;

		std::vector<Blob> possibleBlobs = bd.Invoke(input, minBlobSize);

		for (std::vector<Blob>::iterator it = possibleBlobs.begin(); it != possibleBlobs.end(); ++it) {
			std::vector<int> points = it->getCornerPoints();
			input.at(points[0], points[1]).red = 255;
			input.at(points[0], points[1]).green = 0;
			input.at(points[0], points[1]).blue = 0;

			input.at(points[2], points[3]).red = 255;
			input.at(points[2], points[3]).green = 0;
			input.at(points[2], points[3]).blue = 0;

			input.at(points[4], points[5]).red = 255;
			input.at(points[4], points[5]).green = 0;
			input.at(points[4], points[5]).blue = 0;

			input.at(points[6], points[7]).red = 255;
			input.at(points[6], points[7]).green = 0;
			input.at(points[6], points[7]).blue = 0;
		}

		ImageLib::saveImg(input, save_final_plate);
		
		//Clear vector memory
		std::vector<Blob>().swap(possibleBlobs); 
		//std::vector<Blob>().swap(licensePlates);
	}
	std::cout << "Program finished";
	std::cin.get();
	return 0;
}

