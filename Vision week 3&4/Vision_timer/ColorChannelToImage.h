/* ========================================================================== */
/*                                                                            */
/*   ColorChannelToImage.h                                                    */
/*   (c) 2013 Chanan van Ooijen & Bryan Baan                                  */
/*                                                                            */
/*   Description                                                              */
/*                                                                            */
/* ========================================================================== */
#ifndef ColorChannelToImage_H
#define ColorChannelToImage_H
#include "Image.h"
#include "exectimer.h"
#include <iostream>

class ColorChannelToImage {
private:
	BaseTimer* bt;
public:
	ColorChannelToImage();
	~ColorChannelToImage();
	void CreateRedChannelImage(Image &sourceImage, Image &destinationImage);
	void CreateGreenChannelImage(Image &sourceImage, Image &destinationImage);
	void CreateBlueChannelImage(Image &sourceImage, Image &destinationImage);
};

#endif