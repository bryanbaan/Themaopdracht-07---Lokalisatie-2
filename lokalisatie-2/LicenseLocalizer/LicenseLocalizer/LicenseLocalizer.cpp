// LicenseLocalizer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <iostream>
#include "LicenseLocalizer.h"

using namespace std;


int _tmain(int argc, _TCHAR* argv[])
{


	BlobDetection bd;
	Image img("wow.bmp");

	bd.Invoke(img);

	return 0;
}

