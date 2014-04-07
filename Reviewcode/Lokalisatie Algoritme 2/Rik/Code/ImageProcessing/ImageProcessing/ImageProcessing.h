/* 
 * File: ImageProcessing.h
 * Image algorithms for 32 bit colour images.
 *
 * Autor: Jeroen Steendam & Rik Jacobs
 * Date : 8 februari 2014
 */
#pragma once

extern "C"
{
	class Algorithms
	{
	public:

		/* Compare the old and new image with each other */
		static int __declspec(dllexport) __stdcall Benchmark(int* original_data, int* new_data, int width, int height, int percentage);

		/* Make image black */
		static void __declspec(dllexport) __stdcall Black(void* data, int size);

			
		
		/* Apply gaussian blur to image */
		static void __declspec(dllexport) __stdcall GaussianBlur(int* original_data, int* new_data, int width, int height);

		/* Invert image colours */
		static void __declspec(dllexport) __stdcall Invert(char* original_data, char* new_data, int size);

		/* Apply 3 by 3 median filter */
		static void __declspec(dllexport) __stdcall Median_3(int* original_data, int* new_data, int width, int height);

		/* Apply 11 by 11 median filter on all channels */
		static void __declspec(dllexport) __stdcall Median_11(int* original_data, int* new_data, int width, int height);

		/* Apply 11 by 11 median filter with luminosity */
		static void __declspec(dllexport) __stdcall Median_11_lum(int* original_data, int* new_data, int width, int height);

		/* Apply salt and pepper noise to image */
		static void __declspec(dllexport) __stdcall SaltPepper(int* original_data, int* new_data, int width, int height, int percentage);	

		/* Find licenseplate in image */
		static void __declspec(dllexport) __stdcall SearchLicenseplateCoordinates(int* original_data, int* new_data, int width, int height);
		

	};
}