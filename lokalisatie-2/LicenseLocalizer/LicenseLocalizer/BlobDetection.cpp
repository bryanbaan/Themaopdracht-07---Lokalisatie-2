#include "stdafx.h"
#include "BlobDetection.h"

BlobDetection::BlobDetection() {

	Point firstPoint(0, -1);
	Point secondPoint(-1, -1);
	Point thirdPoint(-1, 0);
	Point fourthPoint(-1, 1);

	_checkPointListSize = 4;

	_checkPoints[_checkPointListSize];

	_checkPoints[0] = firstPoint;
	_checkPoints[1] = secondPoint;
	_checkPoints[2] = thirdPoint;
	_checkPoints[3] = fourthPoint;
}

std::list<Blob> BlobDetection::Invoke(Image &img) {
	
	std::list<Blob> blobList;

	int height = img.GetHeight();
	int width = img.GetWidth();
	int blobIndex = 0;

	bool neighbourFound = false;

	for(int y = 0; y< height; y++) {
		for(int x = 0; x < width; x++) {
			if(img.GetPixelBlue(x,y) == 255 && img.GetPixelGreen(x,y) == 255 && img.GetPixelRed(x,y) == 255) {

				//For every pixel check pixels around it.
				for(int listIndex = 0; listIndex < _checkPointListSize; listIndex++) {

					int _x = x + _checkPoints[listIndex].getX();
					int _y = y + _checkPoints[listIndex].getY();

					int green = img.GetPixelGreen(_x, _y);
					int blue = img.GetPixelBlue(_x, _y);
					int red = img.GetPixelRed(_x, _y);

					if(green == 255 && blue == 255 && red == 255) {
						neighbourFound =  true;
						img.SetPixel(x,y, img.GetPixel(_x, _y));
					}

					if(neighbourFound == false) {
						//label the found blob
						int ran = rand()%200 + 50;

						img.SetPixelBlue(x, y, ran);
						img.SetPixelGreen(x, y, ran);
						img.SetPixelRed(x, y, ran);

						blobIndex++;
					}
					neighbourFound = false;
				}
			}
		}
		
	}
	return blobList;

}