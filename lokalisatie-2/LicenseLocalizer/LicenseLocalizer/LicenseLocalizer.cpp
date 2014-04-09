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

	Threshold th;
	BlobDetection bd;

	inputFile = "license_plate_";
	//stringstream ss;
	for (test = 1; test <= 23; test++) {
		string final_plate =  inputFile + to_string(test) + ".jpg";
		Image inputImage(final_plate);

		clock_t start = clock();
		th.doAlgorithm(inputImage);
		inputImage.SaveImageToFile("th");
		clock_t end = clock();
		std::cout << "blob detection took: " << ((end - start) / (double)CLOCKS_PER_SEC) << "\n";
		 std::vector<Blob> blobs = bd.Invoke(inputImage, (inputImage.GetHeight() * inputImage.GetWidth()) * 0.0015);

		std::cout << "blobs found: " << blobs.size() << "\n";

		 for (std::vector<Blob>::iterator it = blobs.begin(); it != blobs.end(); it++) {
			 std::cout << "ratio: "<< it->getRatio() << "\n";
			if (it->getRatio() >=2 && it->getRatio() <= 5) { 
				for (int y = it->_smallestY; y < it->_biggestY; y++) {
					for (int x = it->_smallestX; x < it->_biggestX; x++) {
						inputImage.SetPixel(x, y, 255 << 24 | 0 << 16 | 0 << 8);
					}
				}
				Point* cornerPoints = it->getCornerPoints();
				std::cout << "Upper left corner: x=" << cornerPoints[0].getX() << " y=" << cornerPoints[0].getY() << "\n";
				std::cout << "Upper right corner: x=" << cornerPoints[1].getX() << " y=" << cornerPoints[1].getY() << "\n";
				std::cout << "Lower left corner: x=" << cornerPoints[2].getX() << " y=" << cornerPoints[2].getY() << "\n";
				std::cout << "Lower right corner: x=" << cornerPoints[3].getX() << " y=" << cornerPoints[3].getY() << "\n";
			}
		} 
			
		inputImage.SaveImageToFile("v1");	
	}
	std::cin.get();
	return 0;
}

