/*
*
*	Author: Mike Schaap
*/


#include "stdafx.h"
#include "BlobDetection.h"
#include <iostream>

BlobDetection::BlobDetection() {
}

std::vector<Blob> BlobDetection::Invoke(Image &img) {
	std::vector<Blob> blobList;

	std::vector<Point> checkPoints;
	std::vector<Point>::iterator it = checkPoints.begin();
	checkPoints.insert(checkPoints.begin(), Point(0,-1));
	checkPoints.insert(checkPoints.begin(), Point(-1, -1));
	checkPoints.insert(checkPoints.begin(), Point(-1, 0));
	checkPoints.insert(checkPoints.begin(), Point(-1, 1));

	int height = img.GetHeight();
	int width = img.GetWidth();
	int pixelAmount = height * width;

	int **labelMap = new int*[height];
	for(int i = 0; i < height; ++i) {
		labelMap[i] = new int[width];
		for(int z = 0; z < width; z++) {
			labelMap[i][z] = 0;
		}
	}

	int *labelTable = new int[pixelAmount];

	for(int a = 0; a<pixelAmount; a++) {
		labelTable[a] = 0;
	}
	
	int tmpX = -1;
	int tmpY = -1;

	int maxNeighbours = checkPoints.size();
	int* neighbours = new int[maxNeighbours];
	int smallestNeighbourLabel = 0;
	int labelIndex = 0;

	int index = 0;
	int neighboorLabelsFound = 0;
	
	for(int y = 0; y < height; y++) {
		for(int x = 0; x < width; x++) {
			//Only check blue. Saves time and if blue = 0 it's black, if blue is 255 it's white. Simple as that
			index = 0;
			if(img.GetPixelBlue(x,y) == 255) {
				for(it = checkPoints.begin(); it != checkPoints.end(); it++) {
					tmpX =  x + it->getX();
					tmpY =  y + it->getY();
					if(tmpX > 0 && tmpY > 0){
						neighbours[index] = labelMap[tmpY][tmpX];
						if(neighbours[index] > 0 ){
							neighboorLabelsFound++;
							if(smallestNeighbourLabel == 0 || neighbours[index] < smallestNeighbourLabel) {
								smallestNeighbourLabel = neighbours[index];
							}
						}
					} else {
						neighbours[index] = 0;
					}
				}

				if(neighboorLabelsFound > 1) {
					for(int i = 0; i < maxNeighbours; i++) {
						if(neighbours[i] > 0) {
							if(neighbours[i] > smallestNeighbourLabel) {
								labelTable[neighbours[i]] = smallestNeighbourLabel;
							}
						}
					}
					labelMap[y][x] = smallestNeighbourLabel;
				} else if (neighboorLabelsFound == 1) {
					labelMap[y][x] = smallestNeighbourLabel;
				}
				else {
					labelMap[y][x] = labelIndex;
					labelTable[labelIndex] = labelIndex;
					labelIndex++;
				}
			}
			neighboorLabelsFound = 0;
		}
	}
	int blobCnt = 0;

	for(int i = 0; i < labelIndex; i++) {
		if(labelTable[i] == i) {
			blobCnt++;
		}
	}

	//int* labelToBlob = new int[labelIndex];
	//for(int x = 0; x < labelIndex; x++) {
	//	labelToBlob[x] = 0;
	//}




	for(int yy= 0; yy< height; yy++) {
		for(int xx =0; xx < width; xx++){ 
			if(labelMap[yy][xx] > 0) {
				img.SetPixel(xx,yy, 255 << 24 | 0 << 16 | 0 << 8);
			}
		}
	}

	img.SaveImageToFile("changed");

	/*


	int labelTableSize = height* width;

	int *labelTable = new int[labelTableSize];

	int labelIndex = 0;


	bool neighbourFound = false;
	int smallestNeighbourLabel = 0;

	for(int y = 0; y< height; y++) {
		for(int x = 0; x < width; x++) {
			if(img.GetPixelBlue(x,y) == 255 && img.GetPixelGreen(x,y) == 255 && img.GetPixelRed(x,y) == 255) {


				//For every pixel check pixels around it.
				std::vector<int> foundLabels;

				for(int listIndex = 0; listIndex < 4; listIndex++) {
					int _x = x + _checkPoints[listIndex].getX();
					int _y = y + _checkPoints[listIndex].getY();
					if(_x > 0 && _y > 0 && ary[_y][_x] > 0) {
						neighbourFound = true;
						foundLabels.insert(foundLabels.begin(), ary[_y][_x]);
					}
				}
				if(neighbourFound == false) {
					labelTable[labelIndex] = labelIndex;
					ary[y][x] = labelIndex;
					labelIndex++;
				} else {
					for(std::vector<int>::iterator it = foundLabels.begin(); it != foundLabels.end(); ++it) {
						if(*it < smallestNeighbourLabel || smallestNeighbourLabel == 0) {
							smallestNeighbourLabel = *it;
						}
					}
					for(std::vector<int>::iterator it = foundLabels.begin(); it != foundLabels.end(); ++it) {
						if(*it != smallestNeighbourLabel) {
							labelTable[*it] = smallestNeighbourLabel;
						}
					}
					ary[y][x] = smallestNeighbourLabel;
				}
				neighbourFound = false;
				smallestNeighbourLabel = 0;
			}
		}
	}

	int blobIndex = 0;

	int* labelToBlob = new int[labelIndex];

	int added = 0;

	for(int li = 0; li < labelIndex; li++) {
		if(labelTable[li] != li) {
			int tmpIndex = labelTable[li];
			while(tmpIndex != labelTable[li]) {
				tmpIndex = labelTable[tmpIndex];
			}
			labelToBlob[li] = tmpIndex;
			added++;
		} else {
			labelToBlob[li] = blobIndex++;
		}
	}

	Blob *blobArray = new Blob[blobIndex];

	for(int l = 0; l < blobIndex; l++) {
		blobArray[l] = Blob();
	}

	for(int yy = 0; yy < height-1; yy++) {
		for(int xx = 0; xx < width-1; xx++) {
			if(ary[yy][xx] > 0) {
				int ui = labelToBlob[ary[yy][xx]];
				if(ui < blobIndex) {
					blobArray[ui].addPixel(yy,xx);
				} 
			}
		}
	}

	std::vector<Blob> potentialBlobs;

	for(int h = 0; h < blobIndex; h++ ) {
		if(blobArray[h].getMass() > 9000) {
			potentialBlobs.insert(potentialBlobs.begin(), blobArray[h]);
		}
	}

	std::vector<Point> points = potentialBlobs[0].getPoints();

	for(std::vector<Point>::iterator it = points.begin(); it != points.end(); ++it) {
		img.SetPixel(it->getX(), it->getY(), 0 << 24 | 255 << 16| 0 << 8);
	}

	*/

	//newImg.SaveImageToFile("ppp_");

	img.SaveImageToFile("changed");
	return blobList;

}