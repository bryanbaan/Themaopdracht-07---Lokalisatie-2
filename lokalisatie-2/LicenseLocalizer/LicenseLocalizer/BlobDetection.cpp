/*
*
*	Author: Mike Schaap
*/


#include "stdafx.h"
#include "BlobDetection.h"
#include <iostream>

BlobDetection::BlobDetection() {
}

std::vector<Blob> BlobDetection::Invoke(Image &img, int minBlobSize) {
	std::vector<Blob> blobList;

	int height = img.GetHeight();
	int width = img.GetWidth();

	std::vector< std::vector<int> > labelMap(height);

	for (int i = 0; i < height; i++) {
		labelMap[i] = std::vector<int>(width);
	}

	int maxLabels = height * width / 2;

	std::vector<int> labelTable(maxLabels); 

	int blobCnt = 0;

	//Labels used to check surrounding pixels
	int labelIndex = 1;
	int labelA, labelB, labelC, labelD;
	int smallestLabel = 25000000;

	for (int y = 1; y < height - 1; y++) 
	{
		for (int x = 1; x < width - 1; x++) 
		{
			//Only check blue. Saves time and if blue = 0 it's black, if blue is 255 it's white. Simple as that
			if (img.GetPixelRed(x, y) == 255) 
			{
				labelA = labelMap[y][x - 1];
				labelB = labelMap[y - 1][x - 1];
				labelC = labelMap[y - 1][x];
				labelD = labelMap[y - 1][x + 1];

				smallestLabel = 25000000;

				if (labelA != 0 && labelA < smallestLabel) smallestLabel = labelA;
				if (labelB != 0 && labelB < smallestLabel) smallestLabel = labelB;
				if (labelC != 0 && labelC < smallestLabel) smallestLabel = labelC;
				if (labelD != 0 && labelD < smallestLabel) smallestLabel = labelD;

				if (smallestLabel == 25000000) 
				{
					//No neighbours found
					labelMap[y][x] = labelIndex;
					labelTable[labelIndex] = labelIndex;
					labelIndex++;
				}
				else 
				{
					labelMap[y][x] = smallestLabel;
					if (labelA > smallestLabel) labelTable[labelA] = smallestLabel;
					if (labelB > smallestLabel) labelTable[labelB] = smallestLabel;
					if (labelC > smallestLabel) labelTable[labelC] = smallestLabel;
					if (labelD > smallestLabel) labelTable[labelD] = smallestLabel;

				}


			}
		}
	}	

	for(int x = 1; x < labelIndex; x++) {
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
		if (blobArray[x][0] > minBlobSize) {
			blobList.insert(blobList.begin(), Blob(blobArray[x][0], blobArray[x][3], blobArray[x][4], blobArray[x][1], blobArray[x][2]));
		}
	}
	return blobList;

}