/*
*
*	Author: Mike Schaap
*/

#ifndef Threshold_H
#define Threshold_H
#include "stdafx.h"
#include "Image.h"
#include <iostream>
#include <math.h>
#include <algorithm>

class Threshold {
public:
	Threshold();
	void CreateThresholdImage(Image &destinationImage);
	void doAlgorithm(Image & image);
	void RGB2HSV(float r, float g, float b, float & h, float & s, float & v);
	void RGB2HSV2(float r, float g, float b, float &h, float &s, float &v);
};

#endif

