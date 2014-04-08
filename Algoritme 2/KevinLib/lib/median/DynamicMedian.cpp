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

HBITMAP DynamicMedian::DoMedian(HBITMAP bitmap) {
	HBITMAP sourceBitmap = bitmap;

	HDC sourceDC = GetDC(NULL);
	HDC sourceDCMem = CreateCompatibleDC(sourceDC);

	HDC destDC = GetDC(NULL);
	HDC destDCMem = CreateCompatibleDC(destDC);

	SelectObject(sourceDCMem, sourceBitmap);

	BITMAPINFO bmpInfo = {0};
	bmpInfo.bmiHeader.biSize = sizeof(bmpInfo.bmiHeader);
	// Get the BITMAPINFO structure from the bitmap
	if(0 == GetDIBits(sourceDCMem, sourceBitmap, 0, 0, NULL, &bmpInfo, DIB_RGB_COLORS))
	{
		printf("Error retrieving bitmapinfo");
	}

	bmpInfo.bmiHeader.biSize = sizeof(bmpInfo.bmiHeader);
	bmpInfo.bmiHeader.biBitCount = 32;
	bmpInfo.bmiHeader.biCompression = BI_RGB;
	bmpInfo.bmiHeader.biHeight = abs(bmpInfo.bmiHeader.biHeight);

	HBITMAP destinationHBitmap = CreateCompatibleBitmap(sourceDCMem,bmpInfo.bmiHeader.biWidth, bmpInfo.bmiHeader.biHeight);
	SelectObject(sourceDCMem, destinationHBitmap);


	int imageBytes = bmpInfo.bmiHeader.biHeight * (bmpInfo.bmiHeader.biWidth * 4);
    BYTE *pSourceBits = (BYTE *)malloc(imageBytes);

	if(0 == GetDIBits(sourceDCMem, sourceBitmap, 0 , bmpInfo.bmiHeader.biHeight, pSourceBits, &bmpInfo, DIB_RGB_COLORS)) {
		printf("Error retrieving source bitmap bits");
	}

	BYTE *pDestBits = (BYTE *)malloc(imageBytes);

	if(0 == GetDIBits(destDCMem, destinationHBitmap, 0 , bmpInfo.bmiHeader.biHeight, pDestBits, &bmpInfo, DIB_RGB_COLORS)) {
		printf("Error retrieving destination bitmap bits");
	}

	//bitmap info

	int height = bmpInfo.bmiHeader.biHeight;
	int width = bmpInfo.bmiHeader.biWidth * (bmpInfo.bmiHeader.biBitCount / 8);

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

	int beginX = (halfMask * 4);
	int endX = width - ( halfMask * 4);

	//Used for calculator pointer position
	int calc = 0;
	int calc1 = 0;


	bool firstline = true;

	for(int y = beginY; y < endY; y++) {
		for(int x = beginX; x < endX; x += 4) {
			calc = (y* width) + x;
			if(firstline == true){
				clearColorValues();
				for(int my = maskBeginY; my <= maskEndY; my++) {
					for(int mx = maskBeginX; mx <= maskEndX; mx++) {
						calc1 = (calc + (my * width)) + (mx * 4);
						addColorValues(pSourceBits[calc1], pSourceBits[calc1 + 1], pSourceBits[calc1 + 2]);
					}
				}
				firstline = false;
			} else {
				for(int my = maskBeginY; my <= maskEndY; my++) {
					for(int mx = maskBeginX; mx <= maskEndX; mx += maskWidth -1) {
						calc1 = (calc + (my * width)) + (mx * 4);
						if(mx < 0) {
							removeColorValues(pSourceBits[calc1], pSourceBits[calc1 + 1], pSourceBits[calc1 + 2]);
						}else if(mx > 0){
							addColorValues(pSourceBits[calc1], pSourceBits[calc1 + 1], pSourceBits[calc1 + 2]);
						}
					}
				}
			}

			pDestBits[calc]		=	getBlueMedian();
			pDestBits[calc + 1]	=	getGreenMedian();
			pDestBits[calc + 2]	=	getRedMedian();
		}
		firstline = true;
	}

	if(0 == SetDIBits(destDCMem, destinationHBitmap, 0, bmpInfo.bmiHeader.biHeight, pDestBits, &bmpInfo, DIB_RGB_COLORS)) {
		printf("Error writing pixels");
	}

	//Clear memory

	//Delete bitmaps
	DeleteObject(sourceBitmap);
	//DeleteObject(destinationHBitmap);

	DeleteDC(sourceDC);
	DeleteDC(sourceDCMem);
	//DeleteDC(destDC);
	//DeleteDC(destDCMem);

	return destinationHBitmap;
}