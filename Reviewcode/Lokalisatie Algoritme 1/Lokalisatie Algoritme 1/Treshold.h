#pragma once
#include <vector>

typedef unsigned char byte;

class Treshold
{
public:
	Treshold(void);
	//Tresholds an image on yellow (Everything thats yellow becomes white, and everything that isnt becomes black)
	std::vector<byte> threshholdyellow(std::vector<byte> oldvec, int width, int height);
	//Calls the findcorner functions and currently just prints them on the console
	std::vector<int> localizelicence(std::vector<byte> imgvec,int width, int height);

	//
	//The following 4 methods are very similar. They walk over the image with a mask and try to find a corner
	//A corner is defined if the mask is filled for at least 85% (But this percentage is adjustable)
	//In order for these functions to work the image has to be binary (only black/white)
	std::vector<int> findtopleftcorner(std::vector<byte> img, int width, int height);
	std::vector<int> findtoprightcorner(std::vector<byte> img, int width, int height);
	std::vector<int> findbottomleftcorner(std::vector<byte> img, int width, int height);
	std::vector<int> findbottomrightcorner(std::vector<byte> img, int width, int height);
};

