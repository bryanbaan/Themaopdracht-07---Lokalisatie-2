#include <iostream>
#include <ImageLib.h>
#include <algorithm>
#include <iterator>
#include "LicenseLocalizer.h"
#include "Algorithms/BinarizeImage.h"
#include <vector>

using namespace std;
using namespace ImageLib;

int main() {
	ImageRGB img = *loadImg("C:\\test\\license_plate_6.jpg");

	LicenseLocalizer licenseLocalizer;
	LicensePosition licensePosition = licenseLocalizer.getLicensePlatePosition(img);

	std::cout << "Top left: x" << licensePosition.getTopLeft()[0] << " y" << licensePosition.getTopLeft()[1] << std::endl;
	std::cout << "Top right: x" << licensePosition.getTopRight()[0] << " y" << licensePosition.getTopRight()[1] << std::endl;
	std::cout << "Bottom left: x" << licensePosition.getBottomLeft()[0] << " y" << licensePosition.getBottomLeft()[1] << std::endl;
	std::cout << "Bottom right: x" << licensePosition.getBottomRight()[0] << " y" << licensePosition.getBottomRight()[1] << std::endl;
	cin.get();

	return 0;
}