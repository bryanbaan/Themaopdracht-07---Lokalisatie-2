#include <iostream>
#include <ImageLib.h>
#include "LicenseLocalizer.h"
#include "Algorithms/BinarizeImage.h"

using namespace std;
using namespace ImageLib;

int main() {
	ImageRGB img = *loadImg("C:\\test\\license_plate_2.jpg");

	/*BinarizeImage imageBinarizer;
	imageBinarizer.binarizeImage(img);

	IntensityHistogram intensityHistogram(img);
	intensityHistogram.SaveToCSV("output.csv");

	saveImg(img, "test.jpg");*/

	LicenseLocalizer licenseLocalizer;
	LicensePosition licensePosition = licenseLocalizer.getLicensePlatePosition(img);

	return 0;
}