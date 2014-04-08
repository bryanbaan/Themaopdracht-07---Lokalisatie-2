#include "stdafx.h"
#include "DynamicMedian.h"

/*
 * Version: 1.0
 * Author: Mike Schaap & Wouter Veen
 * Team: 15
 */

DynamicMedian::DynamicMedian(int medianWidth) {
	//Set all array values to 0
	for(int i = 0; i < 256; i++) {
		red[i] = 0;
		green[i] = 0;
		blue[i] = 0;
	}

	maskWidth = medianWidth;
	maskSize = medianWidth * medianWidth;
	middle =  maskSize / 2 + 1;
	lastGreenMedian = -1;
}

void DynamicMedian::clearColorValues() {
	for(int cnt = 0; cnt < 256; cnt++) {
		blue[cnt] = 0;
		green[cnt] = 0;
		red[cnt] = 0;
	}
	lastGreenMedian = -1;
}


void DynamicMedian::addColorValues(int v1, int v2, int v3){
	blue[v1]++;
	green[v2]++;
	red[v3]++;
}

void DynamicMedian::removeColorValues(int v1, int v2, int v3){
	if(blue[v1] > 0) {
		blue[v1]--;
	}
	if(green[v2] > 0) {
		green[v2]--;
	}
	if(red[v3] > 0) {
		red[v3]--;
	}
}

int DynamicMedian::getRedMedian(){
	int mid = middle;
	for(int cnt = 0; cnt < 256; cnt++){
		mid -= red[cnt];
		if(mid <= 0)
			return cnt;
	}
	return 0;
}

int DynamicMedian::getGreenMedian(){
	int mid = middle;
	for(int cnt = 0; cnt < 256; cnt++){
		mid -= green[cnt];
		if(mid <= 0)
			return cnt;
	}
	return 0;
} 


int DynamicMedian::getBlueMedian(){
	int mid = middle;
	for(int cnt = 0; cnt < 256; cnt++){
		mid -= blue[cnt];
		if(mid <= 0)
			return cnt;
	}
	return 0;
}

void DynamicMedian::DoMedian(Image & bitmap) {
	Image sourceBitmap(bitmap);

	unsigned int * pSourceBits = sourceBitmap.GetDataPointer();
	unsigned int * pDestBits = bitmap.GetDataPointer();
	
	//bitmap info
	int height = bitmap.GetHeight();
	int width = bitmap.GetWidth();

	//Median configuration

	int halfMask = maskWidth / 2;
	maskSize = maskWidth * maskWidth;

	int maskBeginX = 0 - halfMask;
	int maskEndX = 0 + halfMask;

	int maskBeginY = 0 - halfMask;
	int maskEndY = 0 + halfMask;

	//Bitmap interation info

	int beginY = halfMask ;
	int endY = height - halfMask;

	int beginX = halfMask;
	int endX = width - halfMask;

	//Used for calculator pointer position
	int calc = 0;
	int calc1 = 0;


	bool firstline = true;

	int arrayPos, pos;
	for (int y = beginY; y < endY; y++) {
		for (int x = beginX; x < endX; x++) {
			arrayPos = y * width + x;

			if (firstline) {
				clearColorValues();

				for (int my = maskBeginY; my <= maskEndY; my++) {
					for (int mx = maskBeginX; mx <= maskEndX; mx++) {
						pos = (arrayPos + (my * width)) + mx;
						addColorValues(((pSourceBits[pos] >> redPixelShift) & 0xFF), ((pSourceBits[pos] >> greenPixelShift) & 0xFF), ((pSourceBits[pos] >> bluePixelShift) & 0xFF));
					}
				}

				firstline = false;
			}
			else {
				for (int my = maskBeginY; my <= maskEndY; my++) {
					for (int mx = maskBeginX; mx <= maskEndX; mx += maskWidth - 1) {
						pos = (arrayPos + (my * width)) + mx;

						if (mx < 0) {
							removeColorValues(((pSourceBits[pos] >> redPixelShift) & 0xFF), ((pSourceBits[pos] >> greenPixelShift) & 0xFF), ((pSourceBits[pos] >> bluePixelShift) & 0xFF));
						}
						else if(mx > 0) {
							addColorValues(((pSourceBits[pos] >> redPixelShift) & 0xFF), ((pSourceBits[pos] >> greenPixelShift) & 0xFF), ((pSourceBits[pos] >> bluePixelShift) & 0xFF));
						}
					}
				}
			}

			pDestBits[arrayPos] = ((getRedMedian() & 0xFF) << bluePixelShift) | ((getGreenMedian() & 0xFF) << greenPixelShift) | ((getBlueMedian() & 0xFF) << redPixelShift);
		}

		firstline = true;
	}
}