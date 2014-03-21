#include "noiser.h"
#include <stdlib.h>
#include <ctime>
#include <iostream>


void noiser::saltAndPepper(Image &sourceImage, Image &destinationImage, int salt) {
	int HEIGHT = sourceImage.GetHeight();
	int WIDTH = sourceImage.GetWidth();
	srand((unsigned int)time(0));
	int i;
	int j;
	int condition = 0;
	
	int red = 0;
	int green = 0;
	int blue = 0;
	int maxValue = 255;
	int minValue = 0;

	int redValue = 0;
	int greenValue = 0;
	int blueValue = 0;

	int salt_pepper = int(salt);
	while (condition <= (((HEIGHT * WIDTH) / 100)*salt_pepper))  {
		i = rand() % WIDTH;
		j = rand() % HEIGHT;
		red = sourceImage.GetPixelRed(i, j);
		green = sourceImage.GetPixelGreen(i, j);
		blue = sourceImage.GetPixelBlue(i, j);
		if (!(((red == green) == blue) == minValue) || !(((red == green) == blue) == maxValue)) {
			if (condition % 2 == 0) {
				red = green = blue = 0;
			}
			else {
				red = green = blue = 255;
			}
			destinationImage.SetPixel(i, j, red << redPixelShift | green << greenPixelShift | blue << bluePixelShift);
			condition++;
		}
	}
}
