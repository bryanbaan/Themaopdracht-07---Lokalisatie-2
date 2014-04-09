/*
*
*	Author: Mike Schaap
*/

#include "stdafx.h"
#include "BlobDetection.h"


BlobDetection::BlobDetection() {
}

std::vector<Blob> BlobDetection::Invoke(ImageLib::ImageRGB & image, int minBlobSize) {

	//Get the image height
	int height = image.height();

	//Get the image width
	int width = image.width();
	
	//Remember on which lines we found a (part) blob, so we don't have to check every line again.
	bool blobFoundOnRow = false;

	//Save all the lines on which we found a (part) blob
	std::vector<int> blobRows;

	//Map used to map every white pixels, r|g|b > 0, to a label
	std::vector< std::vector<int> > labelMap(height);

	//Make sure the default values are 0.
	for (int i = 0; i < height; i++) {
		labelMap[i] = std::vector<int>(width);
	}

	//Maximum amount of labels an image can containt. this is a estimation.
	int maxLabels = height * width / 2;

	//If to labels meet somewhere, we link the highest labels to the lowest label. So we can link all labels together
	std::vector<int> labelTable(maxLabels); 

	//We start labeling at 1. 0 means no label. (black(background) pixel)
	int labelIndex = 1;

	//used to find the labels of the surrounding pixels
	int labelA, labelB, labelC, labelD;

	//smallest neighboor label found. We use a huge value so we know for sure our if works
	int smallestLabel = maxLabels;
	
	//We don't want to check the edge(1px), since not all the surrounding pixels are there.
	int tmpHeight = height - 1;
	int tmpWidth = width - 1;

	//Check every pixel for color, if color is white check surrounding pixels if they already have a label. If a neighbour (or more) has a label, assign the lowest label
	// to the current pixel
	for (int y = 1; y < tmpHeight; y++)
	{
		for (int x = 1; x < tmpWidth; x++)
		{
			//Only check blue. Saves time and if blue = 0 it's black, if blue is 255 it's white. Simple as that
			if (image.at(x, y).red == 255)
			{
				if (blobFoundOnRow == false) blobFoundOnRow = true;
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
					//Found atleast one neighbour label
					labelMap[y][x] = smallestLabel;
					if (labelA > smallestLabel) labelTable[labelA] = smallestLabel;
					if (labelB > smallestLabel) labelTable[labelB] = smallestLabel;
					if (labelC > smallestLabel) labelTable[labelC] = smallestLabel;
					if (labelD > smallestLabel) labelTable[labelD] = smallestLabel;

				}
			}
		}
		//found blob on row
		if (blobFoundOnRow == true) {
			blobFoundOnRow = false;
			blobRows.insert(blobRows.end(), y);
		}
	}

	//Vector for assinging which labels belong to which blob
	std::vector<int> labelToBlob(labelIndex);

	int blobCount = 0;
	int tmp1;
	for(int i = 0; i < labelIndex; i++) {
		if (labelTable[i] != i) {
			tmp1 = labelTable[i];
			while (labelTable[tmp1] != tmp1) {
				tmp1 = labelTable[tmp1];
			}
			labelToBlob[i] = labelToBlob[tmp1];
			labelTable[i] = tmp1;
		}
		else {
			labelToBlob[i] = blobCount++;
		}
	}

	//Change al labels to blob id


	//Map used to map every white pixels, r|g|b > 0, to a label
	std::vector< std::vector<int> > blobMap(height);

	//Make sure the default values are 0.
	for (int i = 0; i < height; i++) {
		blobMap[i] = std::vector<int>(width);
	}

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			blobMap[y][x] = labelToBlob[labelMap[y][x]];
		}
	}


	std::vector< std::vector<int> > blobs(blobCount);
	for (int i = 0; i < blobCount; i++) {
		blobs[i] = std::vector<int>(6);
		blobs[i][0] = 0; //Blob ID
		blobs[i][1] = 0; //Mass (amount of pixels)
		blobs[i][2] = 20000; //Min Y
		blobs[i][3] = 0; //Max Y
		blobs[i][4] = 20000; //Min X
		blobs[i][5] = 0; //Max X
	}


	int originalLabel = 0;
	int blobId = 0;


	for (std::vector<int>::iterator it = blobRows.begin(); it != blobRows.end(); it++) {
		for (int x = 0; x < width; x++) {
			originalLabel = labelMap[*it][x];
			if(originalLabel > 0) {
				blobId = labelToBlob[originalLabel];
				blobs[blobId][0] = blobId;
				blobs[blobId][1]++;
				if (x < blobs[blobId][4]) blobs[blobId][4] = x;
				if (x > blobs[blobId][5]) blobs[blobId][5] = x;
				if (*it < blobs[blobId][2]) blobs[blobId][2] = *it;
				if (*it > blobs[blobId][3]) blobs[blobId][3] = *it;
			}
		}
	}

	std::vector<Blob> definiteBlobs;

	for (int i = 0; i < blobCount; i++) {
		if (blobs[i][1] > minBlobSize) {
			definiteBlobs.insert(definiteBlobs.end(), Blob(blobs[i][0], blobs[i][1], blobs[i][2], blobs[i][3], blobs[i][4], blobs[i][5]));
		}
	}

	std::vector<Blob> validBlobs;

	//check if blob of possible licenseplate
	for (std::vector<Blob>::iterator it = definiteBlobs.begin(); it != definiteBlobs.end(); ++it) {
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
			//Quick check if we can find characters of some sort in the blob
			if (edgeCounter >= 5) {
				validBlobs.insert(validBlobs.end(), *it);
			}
		}
	}

	std::cout << "blobs found: " << validBlobs.size() << std::endl;

	/* for (std::vector<Blob>::iterator it = validBlobs.begin(); it != validBlobs.end(); it++)  {
		std::vector<int> points = it->getCornerPoints();	
		int blobId = it->getLabel();
		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				int label = blobMap[y][x];
				if (label == blobId) {
					image.at(x, y).red = 255;
					image.at(x, y).green = 0;
					image.at(x, y).blue = 0;
				}
			}
		}
	} */

	for (std::vector<Blob>::iterator it = validBlobs.begin(); it != validBlobs.end(); it++)  {
		std::vector<int> points = it->getCornerPoints();
		int blobId = it->getLabel();
		int h = it->getHeight();

		bool labelFound = false;

		int cornerTLY = -1;
		int cornerTLX = -1;

		int cornerTRY = -1;
		int cornerTRX = -1;
	
		int cornerBLY = -1;
		int cornerBLX = -1;

		int cornerBRY = -1;
		int cornerBRX = -1;

		
		int minFlatRate = 2;

		int lastY = -1;
		int flatCnt = 0;

		//let's find the bottom left corner
		int halfX = points[3] - ((points[3] - points[1]) / 2);
		int halfY = points[0] + ((points[4] - points[0]) / 2);
		for (int x = halfX; x > points[1]; x--) {
			for (int y = points[0]; y < points[4] && labelFound == false; y++) {
				//We found the label we are looking for. 
				if (blobMap[y][x] == blobId) {
					labelFound = true;
					if (lastY == -1) lastY = y;
					if (y == lastY) {
						flatCnt++;
						if (flatCnt >= minFlatRate && y < halfY) {
							cornerTLY = y;
							cornerTLX = x;
						}
					}
					else {
						flatCnt = 0;
					}
					lastY = y;
				}
			}
			labelFound = false;
		}

		halfX = points[1] + ((points[3] - points[1]) / 2);
		halfY = points[0] + ((points[4] - points[0]) / 2);
		for (int x = halfX; x < points[3]; x++) {
			for (int y = points[0]; y < points[4] && labelFound == false; y++) {
				//We found the label we are looking for. 
				if (blobMap[y][x] == blobId) {
					labelFound = true;
					if (lastY == -1) lastY = y;
					if (y == lastY) {
						flatCnt++;
						if (flatCnt >= minFlatRate && y < halfY) {
							cornerTRY = y;
							cornerTRX = x;
						}
					}
					else {
						flatCnt = 0;
					}
					lastY = y;
				}
			}
			labelFound = false;
		}

			//let's find the bottom left corner
		halfX = points[3] - ((points[3] - points[1]) / 2);
		halfY = points[0] + ((points[4] - points[0]) / 2);
		for (int x = halfX; x > points[1]; x--) {
			for (int y = points[4]; y > points[0] && labelFound == false; y--) {
				//We found the label we are looking for. 
				if (blobMap[y][x] == blobId) {
					labelFound = true;
					if (lastY == -1) lastY = y;
					if (y == lastY) {
						flatCnt++;
						if (flatCnt >= minFlatRate && y > halfY) {
							cornerBLY = y;
							cornerBLX = x;
						}
					}
					else {
						flatCnt = 0;
					}
				lastY = y;
				}
			}
			labelFound = false;
		}

		halfX = points[1] + ((points[3] - points[1]) / 2);
		halfY = points[0] + ((points[4] - points[0]) / 2);
		for (int x = halfX; x < points[3]; x++) {
			for (int y = points[4]; y > points[0] && labelFound == false; y--) {
				//We found the label we are looking for. 
				if (blobMap[y][x] == blobId) {
					labelFound = true;
					if (lastY == -1) lastY = y;
					if (y == lastY) {
						flatCnt++;
						if (flatCnt >= minFlatRate && y > halfY) {
							cornerBRY = y;
							cornerBRX = x;
						}
					}
					else {
						flatCnt = 0;
					}
					lastY = y;
				}
			}
			labelFound = false;
		}


		image.at(cornerTLX, cornerTLY).red = 255;
		image.at(cornerTLX, cornerTLY).green = 0;
		image.at(cornerTLX, cornerTLY).blue = 0;

		image.at(cornerTRX, cornerTRY).red = 255;
		image.at(cornerTRX, cornerTRY).green = 0;
		image.at(cornerTRX, cornerTRY).blue = 0;

		image.at(cornerBLX, cornerBLY).red = 255;
		image.at(cornerBLX, cornerBLY).green = 0;
		image.at(cornerBLX, cornerBLY).blue = 0;

		image.at(cornerBRX, cornerBRY).red = 255;
		image.at(cornerBRX, cornerBRY).green = 0;
		image.at(cornerBRX, cornerBRY).blue = 0;
	}


	/*
	for (std::vector<Blob>::iterator it = validBlobs.begin(); it != validBlobs.end(); it++)  {
		std::vector<int> points = it->getCornerPoints();
		int blobId = it->getLabel();
		int h = it->getHeight();
		bool labelFound = false;
		int lastY = -1;

		int direction = 0; // 0 == gelijk , 1 == omhoog, 2 == omlaag

		int directionCount = 0;
		int highestY = 0;
		int curX = 0;

		int cornerY = -1;
			//let's find the bottom left corner
		int halfX = points[3] - ((points[3] - points[1]) / 2);
		for (int x = halfX; x > points[1]; x--) {
			for (int y = points[4]; y > points[0] && labelFound == false; y--) {
				//We found the label we are looking for. 
				if (blobMap[y][x] == blobId) {
					labelFound = true;
					if (lastY == -1) lastY = y;
					if (y < lastY) {
						if ((lastY - y) > 10) {
							image.at(x, y).green = 0;
							image.at(x, y).red = 255;
							image.at(x, y).blue = 0;
							cornerY = highestY;
						}
						else {
							image.at(x, y).green = 255;
							image.at(x, y).red = 0;
							image.at(x, y).blue = 0;
						}
					}
					else {
						image.at(x, y).green = 255;
						image.at(x, y).red = 0;
						image.at(x, y).blue = 0;
					}
					if (y > highestY) {
						highestY = y;
						curX = x;
					}
				}
			}
			labelFound = false;
		}
		if (cornerY == -1) {
			cornerY = highestY;
		}
		std::cout << "bot left corner y: " << cornerY << " x: " << curX << std::endl;
	}
	*/
	/* for (std::vector<Blob>::iterator it = validBlobs.begin(); it != validBlobs.end(); it++)  {
		std::vector<int> points = it->getCornerPoints();
		int blobId = it->getLabel();
		for (int y = points[0]; y < points[4]; y++)
		{
			for (int x = points[1]; x < points[3]; x++)
			{
				int label = blobMap[y][x];
				if (label == blobId) {
					image.at(x, y).red = 255;
					image.at(x, y).green = 0;
					image.at(x, y).blue = 0;
				}
			}
		}
	} */



	return definiteBlobs;
}