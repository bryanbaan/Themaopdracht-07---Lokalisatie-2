/* ========================================================================== */
/*                                                                            */
/*   noiser.h                                                                 */
/*   (c) 2013 Chanan van Ooijen & Bryan Baan                                  */
/*                                                                            */
/*   Description                                                              */
/*                                                                            */
/* ========================================================================== */
#include "Image.h"
#include "exectimer.h"
#include <iostream>
#include <fstream>

#pragma once
class noiser
{
public:

	//! This method has parameters an source image, an destination image and a int which represent percentage of salt&pepper-noise
	//
	//! This method will add the given percentage salt&pepper noise on the destination image
	void saltAndPepper(Image &sourceImage, Image &destinationImage, int salt);
};

