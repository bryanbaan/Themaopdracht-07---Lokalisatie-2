/*
*
*	Author: Mike Schaap
*/


#include "stdafx.h"
#include "BlobCheck.h"
#include <vector>
#define MINIMALPIXELAMOUNT 500
//#define redPixel 24
//#define greenPixel 16
//#define bluePixel 8
//#define alphaPixel 0

BlobCheck::BlobCheck() {
}


BlobCheck::~BlobCheck() {
}

std::vector<Blob> BlobCheck::CheckIfBlobIsLicensePlate(std::vector<Blob> &blobobjects, Image &sourceImage) {
	
	std::vector<Blob> validBlobs;
	int index = 0;
	int listSize = blobobjects.size();
	int HEIGHT = sourceImage.GetHeight();
	int WEIGHT = sourceImage.GetWidth();
	int PlatePixelAmount = MINIMALPIXELAMOUNT;


	for (std::vector<Blob>::iterator it = blobobjects.begin(); it != blobobjects.end(); ++it) {
		int mass = it->getMass();
		//is aantal pixels groot genoeg om kenteken te zijn
		if (mass > PlatePixelAmount) {
			//zo , doe die algoritme met hoeken en pythagoras
			
			Point topLeft = it->getCornerPoints()[0];
			Point topRight = it->getCornerPoints()[1];
			Point bottomRight = it->getCornerPoints()[2];
			Point bottomLeft = it->getCornerPoints()[3];

			int pythagorasHorizontal = topRight.getX() - topLeft.getX();
			int pythagorasVertical = topRight.getY() - topLeft.getY();

			int length = sqrt(pow(pythagorasHorizontal, 2) + pow(pythagorasVertical, 2));

			pythagorasHorizontal = bottomRight.getX() - topRight.getX();
			pythagorasVertical = bottomRight.getY() - topRight.getY();

			int length2 = sqrt(pow(pythagorasHorizontal, 2) + pow(pythagorasVertical, 2));

			int height;
			int width;
			// lengte * lengte2 is nu de oppervlakte van een mogelijk kenteken

			//oppervlakteMogelijkKenteken = lengte*lengte2

			length < length2 ? height = length : width = length;

			if (width >(height*2.5) && width < (height * 5)) {
				validBlobs.insert(validBlobs.begin(), *it);
			}

			//lengte / lengte2 moet groter zijn dan 2,5 
		}
		index++;
	}
	return validBlobs;
}
