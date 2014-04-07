#include "test.h"
#include <iostream>
#include <corona.h>
#include "basetimer.h"
#include <time.h>
#include "imagehandlerniek.h"
#include <vector>
#include <cmath>
#include "Treshold.h"

#define BESTANDSNAAM "C:/TestFoto/license_plate_5.jpg"
#define WIDTH 640
#define HEIGHT 480
#define PI 3.14159265

test::test(void)
{
}


/*//bron: http://msdn.microsoft.com/en-us/library/2c8d19sb.aspx
char* test::removePath(char* filenm)
{
	//Get Filename from path
	char *next_token = NULL;
	char *result = NULL;
	char *dup = _strdup(filenm);
	result = strtok_s(dup, "/", &next_token);

	while (result != NULL) {
		if (result != NULL) {
			//std::cout<<result<<std::endl;
			filenm = result;
			result = strtok_s(NULL, "/", &next_token);
		}
	}
	return filenm;
}

char* test::combineCharptr(char* fn, char* addition) 
{
	char* temp = removePath(fn);
	size_t size = strlen(addition) + strlen(temp) + 1;
	char* result = new char[size];

	strcpy(result, addition);
	strcat(result, temp);
	return result;
}*/

int main( int argc, char* argv[] ) {
	imagehandlerniek hand = imagehandlerniek();
	std::vector<byte> img = hand.loadimg(BESTANDSNAAM);
	Treshold loc = Treshold();
	loc.localizelicence(img,WIDTH, HEIGHT);

	
	system("PAUSE");
	return 0;
}


