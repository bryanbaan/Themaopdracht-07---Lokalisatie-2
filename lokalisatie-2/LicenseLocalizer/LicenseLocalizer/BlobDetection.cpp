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
	int labelIndex = 1;

	int index = 0;
	int neighboorLabelsFound = 0;

	int blobCnt = 0;
	
	for(int y = 0; y < height; y++) {
		for(int x = 0; x < width; x++) {
			//Only check blue. Saves time and if blue = 0 it's black, if blue is 255 it's white. Simple as that
			index = 0;
			int color = img.GetPixelRed(x,y);
			if(color > 0) {
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
					index++;
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
			smallestNeighbourLabel = 0;
		}
	}

	for(int x = 0; x < labelIndex; x++) {
		if(labelTable[x] == x) {
			blobCnt++;
		}

	}


	int* labelToBlob = new int[labelIndex];
	for(int x = 0; x < labelIndex; x++) {
		labelToBlob[x] = 0;
	}

	int blobIndex = 1;
	int tmp = 0;

	for(int x = 0; x < labelIndex; x++) {
		if(labelTable[x] == x) {
			labelToBlob[x] = blobIndex++;
		}else {
			tmp = labelTable[x];
			while(labelTable[tmp] != tmp) {
				tmp = labelTable[tmp];
			}
			labelToBlob[x] = labelToBlob[tmp];
		}
	}

	
	int **blobArray = new int*[blobCnt + 2];
	for(int i = 0; i < blobCnt + 2; i++) {
		blobArray[i] = new int[5];
		blobArray[i][0] = 0; //mass
		blobArray[i][1] = width; //min x
		blobArray[i][2] = 0; //max x
		blobArray[i][3] = height; //min y
		blobArray[i][4] = 0; //max y
	}

	int i  = 0;
	int ID = 0;
	for(int y = 0; y < height; y++) {
		for(int x = 0; x < width; x++) {
			i = labelMap[y][x];
			if(i > 0 ) {
				ID = labelToBlob[i];
				blobArray[ID][0]++;
				if(x < blobArray[ID][1]) {
					blobArray[ID][1] = x;
				}
				if(x > blobArray[ID][2]){
					blobArray[ID][2] = x;
				}
				if(y < blobArray[ID][3]) {
					blobArray[ID][3] = y;
				}
				if(y > blobArray[ID][4]) {
					blobArray[ID][4] = y; 
				}
			}
		}
	}

	for(int x = 0; x < blobCnt +2; x++) {
		if(blobArray[x][0] > 0) {
			blobList.insert(blobList.begin(), Blob(blobArray[x][0], blobArray[x][3], blobArray[x][4], blobArray[x][1], blobArray[x][2]));
		}
	}

	Blob ls;

	for(std::vector<Blob>::iterator ix = blobList.begin(); ix != blobList.end(); ix++) {

		if(ix->getMass() > 10000) {
			ls = *ix;
		}
	}

	for( int yy = 0; yy < height; yy++) {
		for(int xx = 0; xx < width; xx++) {
			if(yy < ls._smallestY || yy > ls._biggestY || xx < ls._smallestX || xx > ls._biggestX ) {
					img.SetPixel(xx,yy, 0 <<24 | 0 << 16 | 0 << 8);
			}
		}
	}



	img.SaveImageToFile("changed");
	return blobList;

}