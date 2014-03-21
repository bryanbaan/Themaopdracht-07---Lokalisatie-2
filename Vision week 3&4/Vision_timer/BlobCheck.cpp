#include "BlobCheck.h"
//#define redPixel 24
//#define greenPixel 16
//#define bluePixel 8
//#define alphaPixel 0

BlobCheck::BlobCheck() {
	bt = new BaseTimer();
}


BlobCheck::~BlobCheck() {
	delete bt;
}

void BlobCheck::CheckIfBlobIsLicensePlate(Blob &blobobjects) {
	bt->reset();
	bt->start();

	aantalpixelswatkentekenminimaalis = (HEIGHT * WEIGHT / 100)

	while (allBlobObjects && && boolean = true){

		//is aantal pixels groot genoeg om kenteken te zijn
		if (aantalPixels < aantalpixelswatkentekenminimaalis) {
			boolean = false
		}
			//zo ja, doe die algoritme met hoeken en pythagoras

		coordinate1 = pixelLinksboven  // kleinste x, grootste y
		coordinate2 = pixelrechtsboven // kleinste y, grootste x
		coordinate3 = pixelrechtsonder // grootste x, kleinste y
		coordinate4 = pixellinksonder  // grootste y, kleinste x

		aanliggendezijdePythagoros = X.coordinate2 - X.coordinate1;
		overstaandezijdePythagoros = Y.coordinate1 - Y.coordinate2;

		lengte = wortle(aanliggendezijdePythagorosKwadraat + overstaandezijdePythagorosKwadraat)

		xzijdePythagoros = X.coordinate3 - X.coordinate2;
		yzijdePythagoros = Y.coordinate3 - Y.coordinate2;

		lengte2 = wortle(xzijdePythagorosKwadraat + yzijdePythagorosKwadraat)

		// lengte * lengte2 is nu de oppervlakte van een mogelijk kenteken

		//oppervlakteMogelijkKenteken = lengte*lengte2

		lengte < lengte2 ? lengteIsHoogteVanMogelijkKenteken : lengteIsBreedteVanMogelijkKenteken

		(breedte >(hoogte*2.5) && breedte < (hoogte * 5)) {blob = mogelijke kandidaat}

		//lengte / lengte2 moet groter zijn dan 2,5 
		return hoekpuntcoordinaten


	}
	/*
	if (sourceImage.GetWidth() != destinationImage.GetWidth() && sourceImage.GetHeight() != destinationImage.GetHeight()) {
		std::cout << "Error images are not the same size" << std::endl;
		return;
	}

	int grayValue;

	for (int y = sourceImage.GetHeight() - 1; y >= 0; y--) {
		for (int x = sourceImage.GetWidth() - 1; x >= 0; x--) {
			grayValue = (int)((sourceImage.GetPixelRed(x, y) * 0.30) + (sourceImage.GetPixelGreen(x, y) * 0.59) + (sourceImage.GetPixelBlue(x, y) * 0.11));
			destinationImage.SetPixel(x, y, (grayValue << redPixelShift) | (grayValue << greenPixelShift) | (grayValue << bluePixelShift));
		}
	}

	bt->stop();
	std::cout << "Time for the Grayscale function: " << bt->elapsedMicroSeconds() << " Microseconds (" << bt->elapsedMilliSeconds() << "ms)" << std::endl;
	*/
}
