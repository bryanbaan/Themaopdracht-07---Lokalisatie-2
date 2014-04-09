/*
*
*	Author: Mike Schaap
*/


#include "stdafx.h"
#include "BlobCheck.h"


BlobCheck::BlobCheck() {
}


BlobCheck::~BlobCheck() {
}

std::vector<Blob> BlobCheck::CheckIfBlobIsLicensePlate(std::vector<Blob> &blobobjects, ImageLib::ImageRGB &image) {
	
	std::vector<Blob> validBlobs;
	//check if blob of possible licenseplate
	for (std::vector<Blob>::iterator it = blobobjects.begin(); it != blobobjects.end(); ++it) {
		double ratio = it->getRatio();
		if (ratio >= 2.1 && ratio <= 5.5) {
			int edgeCounter = 0;
			int lastColor = 255;
			std::vector<int> points = it->getCornerPoints();
			int y = (it->getHeight() / 2) + points[0];
			for (int x = points[1]; x < points[3]; x++){
				if (image.at(x, y).red != lastColor){
					edgeCounter++;
					lastColor = image.at(x, y).red;
				}
			}
			std::cout << "Edge's: " << edgeCounter << std::endl;
			//std::cout << "fill: " << (it->getGroundSurface / it->getMass) << std::en
			//std::cout << "Blob pixels: " << it->getMass() << " groundsurface: " << it->getGroundSurface() << std::endl;
			//float test = ((float(it->getMass()) / float(it->getGroundSurface())) * 100.0f);
			//std::cout << "Total percentage: " << test << std::endl;
			if (edgeCounter >= 5)
				validBlobs.insert(validBlobs.end(), *it);
		}
	}
	return validBlobs;
}
