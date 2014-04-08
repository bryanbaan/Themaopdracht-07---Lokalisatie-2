#ifndef LICENSELOCALIZER_H
#define LICENSELOCALIZER_H

#include <ImageLib.h>
#include "LicensePosition.h"
#include <vector>

using namespace ImageLib;

class LicenseLocalizer {
public:
	LicensePosition getLicensePlatePosition(ImageRGB & image);
};

#endif;