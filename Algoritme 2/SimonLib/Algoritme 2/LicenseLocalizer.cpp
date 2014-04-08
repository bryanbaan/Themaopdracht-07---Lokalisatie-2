#include "LicenseLocalizer.h"
#include "Algorithms\YellowColorFilter.h"
#include "Algorithms\BinarizeImage.h"
#include "Algorithms\IntensityHistogram.h"
#include "Algorithms\HighPassFilter.h"

LicensePosition LicenseLocalizer::getLicensePlatePosition(ImageRGB & image) {
	YellowColorFilter yellowColorFilter;
	yellowColorFilter.filterImage(image);

	HighPassFilter highPassFilter;
	highPassFilter.filterImage(image);

	BinarizeImage imageBinarizer;
	imageBinarizer.binarizeImage(image);

	IntensityHistogram intensityHistogram;
	intensityHistogram.getLicensePosition(image, true);

	saveImg(image, "output.jpg");

	return LicensePosition(0, 0, 0, 0);
}