// LicenseLocalizer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <iostream>
#include "LicenseLocalizer.h"

using namespace std;


int _tmain(int argc, _TCHAR* argv[])
{
	string inputFileLocation;
	string outputFileLocation;

	cout << "Please specify the path to the input file: \n";

	cin >> inputFileLocation;
	
	cout << "Please specify the path for the output file: \n";

	cin >> outputFileLocation;

	Image img;
	img.LoadImageFromFile("test.bmp");

	BlobDetection bd;

	std::list<Blob> blobs = bd.Invoke(img);

	img.SaveImageToFile("new");

	return 0;
}

