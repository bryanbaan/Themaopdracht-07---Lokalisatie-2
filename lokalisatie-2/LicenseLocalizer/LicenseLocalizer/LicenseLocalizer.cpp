// LicenseLocalizer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <iostream>
#include "LicenseLocalizer.h"
#include "MedianDifferenceAlgorithm.h"

using namespace std;


int _tmain(int argc, _TCHAR* argv[])
{
	BlobDetection bd;
	Image img("license_plate_6.jpg");

	MedianDifferenceAlgorithm::doAlgorithm(img);
	img.SaveImageToFile("mediandifference-");

	bd.Invoke(img);

	return 0;
}

