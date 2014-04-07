#pragma once
#include <vector>

typedef unsigned char byte;
 
class imagehandlerniek
{
public:
	int width;
	imagehandlerniek(void);
	//returned een vector met daarin bytes in de volgorde R8G8B8A8
	std::vector<byte> loadimg(char* fn);
	void saveimg(std::vector<byte> vec, char* naam, int width, int height);
};

