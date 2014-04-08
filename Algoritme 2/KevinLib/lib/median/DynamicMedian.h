#include <Windows.h>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <iterator>

/*
 * Version: 1.0
 * Author: Mike Schaap & Wouter Veen
 * Team: 15
 */

class DynamicMedian {
	
public:
	DynamicMedian(int medianWidth);
	HBITMAP DoMedian(HBITMAP bitmap);
private:
	//Variables
	int red[256];
	int green[256];
	int blue[256];

	int middle;
	int maskWidth;
	int maskSize;
	int lastGreenMedian;

	//Functions
	void clearColorValues();
	void addColorValues(int v1, int v2, int v3);
	void removeColorValues(int v1, int v2, int v3);
	int getRedMedian();
	int getGreenMedian();
	int getBlueMedian();
};