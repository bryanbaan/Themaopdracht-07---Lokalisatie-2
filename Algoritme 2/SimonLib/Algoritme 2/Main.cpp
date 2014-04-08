#include <iostream>
#include <ImageLib.h>
#include "LicenseLocalizer.h"
#include "Algorithms/BinarizeImage.h"

using namespace std;
using namespace ImageLib;

int main() {
	ImageRGB img = *loadImg("C:\\test\\license_plate_2.jpg");

	LicenseLocalizer licenseLocalizer;
	LicensePosition licensePosition = licenseLocalizer.getLicensePlatePosition(img);

	return 0;
}