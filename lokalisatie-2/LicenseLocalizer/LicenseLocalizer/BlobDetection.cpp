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

	std::vector<int> labelCount(labelIndex);

	int tmp1;
	for(int i = 0; i < labelIndex; i++) {
		if (labelTable[i] != i) {
			tmp1 = labelTable[i];
			while (labelTable[tmp1] != tmp1) {
				tmp1 = labelTable[tmp1];
			}
			labelTable[i] = labelTable[tmp1];
		}
	}

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			if (labelMap[y][x] > 0) {
				labelCount[labelTable[labelMap[y][x]]]++;
			}
		}
	}

	int biggestlabel = 0;
	int biggestLabelCount = 0;

	for (int i = 0; i < labelIndex; i++) {
		if (labelCount[i] > biggestLabelCount) {
			biggestLabelCount = labelCount[i];
			biggestlabel = i;
		}
	}

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			if (labelTable[labelMap[y][x]] == biggestlabel) {
				//img.SetPixel(x, y, 255 << 24 | 0 << 16 | 0 << 8);
			}
		}
	}

	return blobList;
}