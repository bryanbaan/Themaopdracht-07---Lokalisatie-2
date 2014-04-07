/* 
 * File: ImageProcessing.h
 * Image algorithms for 32 bit colour images.
 *
 * Autor: Jeroen Steendam & Rik Jacobs
 * Date : 8 februari 2014
 */
#include "ImageProcessing.h"

#include <cstring>
#include <algorithm>
#include <array>
#include <cstdlib>
#include <ctime>

#define RGB(r, g, b) (255 << 24 | r << 16 | g << 8 | b)
/*
 * Make image black.
 */
void __declspec(dllexport) __stdcall Algorithms::Black(__out void* data, int size)
{
	memset(data, 0, size);
}

/*
 * Invert the image colours.
 */
void __declspec(dllexport) __stdcall Algorithms::Invert(__in char* original_data, __out char* new_data, int size)
{
	for(int i = 0; i < size; i++)
		new_data[i] = ~original_data[i];
}

/*
 * Median filter using 3*3 mask
 */
void __declspec(dllexport) __stdcall Median_3(__in int* original_data, __out int* new_data, int width, int height)
{
	std::array<int, 9> r_mask = {0};
	std::array<int, 9>  g_mask = {0};
	std::array<int, 9>  b_mask = {0};
	for(int x = 1; x < width - 1; x++) {
		for(int y = 1; y < height - 1; y++) {
			int count = 0;
			for(int i = -1; i < 2; i++) {
				for(int j = -1; j < 2; j++) {
					r_mask[count] = original_data[x+i + (y+j) * width] >> 16 & 0xFF;
					g_mask[count] = original_data[x+i + (y+j) * width] >> 8 & 0xFF;
					b_mask[count] = original_data[x+i + (y+j) * width] & 0xFF;
					count++;
				}
			}
			std::sort(r_mask.begin(), r_mask.end());
			std::sort(g_mask.begin(), g_mask.end());
			std::sort(b_mask.begin(), b_mask.end());
			
			new_data[x + y * width] = (255 << 24 | r_mask[4] << 16 | g_mask[4] << 8 | b_mask[4]);
		}
	}
}

void __declspec(dllexport) __stdcall Median_11(__in int* original_data, __out int* new_data, int width, int height)
{
	std::array<int, 121> r_mask = {0};
	std::array<int, 121> g_mask = {0};
	std::array<int, 121> b_mask = {0};
	for(int x = 5; x < width - 5; x++) {
		for(int y = 5; y < height - 5; y++) {
			int count = 0;
			for(int i = -5; i < 6; i++) {
				for(int j = -5; j < 6; j++) {
					r_mask[count] = original_data[x+i + (y+j) * width] >> 16 & 0xFF;
					g_mask[count] = original_data[x+i + (y+j) * width] >> 8 & 0xFF;
					b_mask[count] = original_data[x+i + (y+j) * width] & 0xFF;
					count++;
				}
			}
			std::sort(r_mask.begin(), r_mask.end());
			std::sort(g_mask.begin(), g_mask.end());
			std::sort(b_mask.begin(), b_mask.end());
			new_data[x + y * width] = (255 << 24 | r_mask[61] << 16 | g_mask[61] << 8 | b_mask[61]);
		}
	}
}

void __declspec(dllexport) __stdcall Median_11_lum(__in int* original_data, __out int* new_data, int width, int height)
{
	std::array<int, 121> colour_mask = {0};
	for(int x = 5; x < width - 5; x++) {
		for(int y = 5; y < height - 5; y++) {
			int count = 0;
			for(int i = -5; i < 6; i++) {
				for(int j = -5; j < 6; j++) {
					colour_mask[count] = ((original_data[x+i + (y+j) * width] >> 16 & 0xFF) * 0.21 + (original_data[x+i + (y+j) * width] >> 8 & 0xFF) * 0.71 + (original_data[x+i + (y+j) * width] & 0xFF) * 0.07);
					count++;
				}
			}
			std::sort(colour_mask.begin(), colour_mask.end());
			new_data[x + y * width] = (255 << 24 | colour_mask[61] << 16 | colour_mask[61] << 8 | colour_mask[61]);
		}
	}
}

void __declspec(dllexport) __stdcall GaussianBlur(__in int* original_data, __out int* new_data, int width, int height)
{

}

void __declspec(dllexport) __stdcall SaltPepper(__in int* original_data, __out int* new_data, int width, int height, int percentage)
{	
	srand (time(0));
	for(int i = 0; i < width; ++i){
		for(int j = 0; j< height; ++j){
			if((std::rand() %100 + 1) < percentage){
				if(std::rand() % 2 == 0){
					new_data[i + j * width] = 0;
				}else{
					new_data[i + j * width] = RGB(255, 255, 255);
				}
			}else{
				new_data[i + j * width] = original_data[i + j * width];
			}
		}
	}
}

int __declspec(dllexport) __stdcall Benchmark(int* original_data, int* new_data, int width, int height, int percentage)
{
	int* noise_data = new int[width*height];

	//Salt and pepper
	SaltPepper(original_data, noise_data, width, height, percentage);

	//Median 11
	Median_11(noise_data, new_data, width, height);

	int size = width * height;
	//int *oldPixel;
	//int *newPixel;
	float calc;
	long double cum;
	//int* arr = new int[size];

	//r new_data[i] >> 16 & 0xFF	original_data[i] >> 16 & 0xFF
	//g	new_data[i] >> 8 & 0xFF		original_data[i] >> 8 & 0xFF
	//b	new_data[i] & 0xFF			original_data[i] & 0xFF
	for(int i = 0; i < size; ++i) {
		//(n - o) / o
		calc = ( ((new_data[i] >> 16 & 0xFF + new_data[i] >> 8 & 0xFF + new_data[i] & 0xFF) / 3.0) - ((original_data[i] >> 16 & 0xFF + original_data[i] >> 8 & 0xFF + original_data[i] & 0xFF) / 3.0)) / ((original_data[i] >> 16 & 0xFF + original_data[i] >> 8 & 0xFF + original_data[i] & 0xFF) / 3.0);
		if(calc < 0)
			cum += calc * -1.0;
		else
			cum += calc;
	}
	delete noise_data;
	return (int)((cum /size) * 100);	
}

/*	Implementation of SearchLicensePlateCoordinates
	This algortithm uses a treshhold to extract yellow pixels from an image,
	optionally this algorathim makes a histogram for all yellow pixels that where found.
	It also uses a 3x3 mask to detect if the region of the current pixels is 100% yellow or not.
*/
void __declspec(dllexport) __stdcall SearchLicenseplateCoordinates(int* original_data, int* new_data, int width, int height){
	int imgSize = (width*height);
	int yellowCount = 0;
    int r, g, b;
    int topLeftX, topLeftY, topRightX, topRightY, bottomRightX, bottomRightY, bottomLeftX, bottomLeftY;
    topLeftX = topLeftY = topRightX = topRightY = bottomRightX = bottomRightY = bottomLeftX = bottomLeftY = 0;

	/* Looping trough all the induvidual pixels */
	for (int counter = 0; counter < imgSize; counter++)
    {
        r = ((original_data[counter] & 0x00FF0000) >> 16);
        g = ((original_data[counter] & 0x0000FF00) >> 8);
        b = (original_data[counter] & 0x000000FF);

		/*	Threshholding for yellow, these are numbers that are working fine for me.
			If a yellow pixel is found it will be set to WHITE and a counter increments, 
			else it will set the pixel to BLACK.
		*/
        if (r > 180 && g > 130 && b < 40)
        {
            new_data[counter] = 0xFFFFFFFF;
            yellowCount++;
        }
        else
        {
            new_data[counter] = 0xFF000000;
        }
    }

	/*
		If the amount of yellow pixels found is less than 0.5% of the total image's pixels (most likely no good result then),
		the algorithm will use another threshhold that will look for different shades of yellow
	*/

    if (yellowCount < (int)(imgSize * 0.005))
    {
        for (int counter = 0; counter < imgSize; counter++)
        {
            r = ((original_data[counter] & 0x00FF0000) >> 16);
            g = ((original_data[counter] & 0x0000FF00) >> 8);
            b = (original_data[counter] & 0x000000FF);
            if (r > 80 && g > 70 && g < 120 && b < 70)
            {
                if (r > 200)
                {
                }
                else
                {
                    original_data[counter] = 0xFF000000;
                }
            }
            else
            {
                r += 120;
                g += 130;
                b -= 20;

                if (r > 255)
                {
                    r = 255;
                }
                if (g > 255)
                {
                    g = 255;
                }
                if (r > 200 && g > 170 && b < 40)
                {
                    original_data[counter] = 0xFFFFFFFF;
                }
                else
                {
                    original_data[counter] = 0xFF000000;
                }
            }
        }
    }
	/*
		Pushing all data from new_data to original_data and clearing new_data. This is not necessary if yellowCount is under 0.5%
	*/
    else
    {
        for (int i = 0; i < imgSize; i++)
        {
            if (new_data[i] != 0)
            {
                original_data[i] = new_data[i];
                new_data[i] = 0;
            }
        }
    }
	
    /*
	--------------Enable this to use histograms-------------
	
	int* histoX = new int[height];
    int* histoY = new int[width];
	
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            if (original_data[w + h * width] == 0xFFFFFFFF)
            {
                histoX[h]++;
                histoY[w]++;
            }
        }
    }
    int highestHistoXValue = 0;
    int highestHistoYValue = 0;

    for (int i = 0; i < height; i++)
    {
        if (histoX[i] > highestHistoXValue)
        {
            highestHistoXValue = histoX[i];
        }
    }

    for (int i = 0; i < width; i++)
    {
        if (histoY[i] > highestHistoYValue)
        {
            highestHistoYValue = histoY[i];
        }
    }*/

	/*
		The following code will use a 3x3 mask to check the adjacent pixels of the current pixel.
		If all these pixels where set to white in the previous threshhold step, white should be 9.
		If white is 9 this pixels will be set to RED, else it will be BLACK
	*/

    for (int h = 1; h < height - 1; h++)
    {
        //if (histoX[h] > (highestHistoXValue * 0.2))
        {
            for (int w = 1; w < width - 1; w++)
            {
                //if (histoY[w] > (highestHistoYValue * 0.2))
                {
                    int white = 0;

                    for (int i = -1; i < 2; i++)
                    {
                        for (int j = -1; j < 2; j++)
                        {
                            if (original_data[w + i + (h + j) * width] == 0xFFFFFFFF)
                            {
                                white++;
                            }
                        }
                    }
                    if (white == 9)
                    {
                        new_data[w + h * width] = 0xFFCD0000;

						//Topleft coordinate should have the lowest x and the lowest y pixels that is set to red
                        if (topLeftX > w || topLeftX == 0 && topLeftY > h || topLeftY == 0)
                        {
                            topLeftX = w;
                            topLeftY = h;                                    
                        }

						//Topright coordinate should have the highest x and the lowest y coordinate
                        if (topRightX < w || topRightX == 0 && topRightY > h || topRightY == 0)
                        {
                            topRightX = w;
                            topRightY = h;
                        }

						//Bottomleft coordinate should have the lowest x and the highest y coordinate
                        if ((bottomLeftX > w || bottomLeftX == 0) && (bottomLeftY > h || bottomLeftY == 0) && w > topLeftY)
                        {
                            bottomLeftX = w;
                            bottomLeftY = h;
                        }

						//Bottomleft coordinate should have the highest x and the highest y coordinate
                        if ((bottomRightX < w || bottomRightX == 0) && (bottomRightY < h || bottomRightY == 0) && w > topRightY)
                        {
                            bottomRightX = w;
                            bottomRightY = h;
                        }
                        bottomRightX = w;
                        bottomRightY = h;
                    }
                    else
                    {
                        new_data[w + h * width] = 0xFF000000;
                    }
                }
            }
        }
    }

	for (int i = 0; i < imgSize; i++)
    {
        if (new_data[i] != 0)
        {
			original_data[i] = new_data[i];
			new_data[i] = original_data[i];
        }
    }
}