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
		string save_final_plate = "c:\\test\\changed_" + inputFile + to_string(test) + ".jpg";

		ImageLib::ImageRGB input (*ImageLib::loadImg(final_plate));

		ycf.filterImage(input);

		int minBlobSize = (input.width() * input.height()) * 0.0015;

		std::vector<Blob> possibleBlobs = bd.Invoke(input, minBlobSize);

		std::vector<Blob> licensePlates = bc.CheckIfBlobIsLicensePlate(possibleBlobs, input);

		std::cout << "Image: " << inputFile << test << "\n";
		std::cout << "Blobs found: " << possibleBlobs.size() << "\n\n";

		//Output licenseplate info
		for (std::vector<Blob>::iterator it = licensePlates.begin(); it != licensePlates.end(); ++it) {
			//if (it->getRatio() >= 2 && it->getRatio() <= 5) {

			std::vector<int> cornerPoints = it->getCornerPoints();


			//std::cout << "Upper left corner: y=" << cornerPoints[0] << " x=" << cornerPoints[1] << "\n";
			//std::cout << "Upper right corner: y=" << cornerPoints[2] << " x=" << cornerPoints[3] << "\n";
			//std::cout << "Lower left corner: y=" << cornerPoints[4] << " x=" << cornerPoints[5] << "\n";
			//std::cout << "Lower right corner: y=" << cornerPoints[6] << " x=" << cornerPoints[7] << "\n\'n";

			int minY = cornerPoints[0];
			int maxY = cornerPoints[4];

			int minX = cornerPoints[1];
			int maxX = cornerPoints[3];

			for (int y = minY; y < maxY; y++) {
				for (int x = minX; x < maxX; x++) {
					input.at(x, y).red = 255;
					input.at(x, y).green = 0;
					input.at(x, y).blue = 0;
				}
			}
		}
		//}

		ImageLib::saveImg(input, save_final_plate);
		
		//Clear vector memory
		std::vector<Blob>().swap(possibleBlobs); 
		std::vector<Blob>().swap(licensePlates);
	}
	std::cout << "Program finished";
	std::cin.get();
	return 0;
}

