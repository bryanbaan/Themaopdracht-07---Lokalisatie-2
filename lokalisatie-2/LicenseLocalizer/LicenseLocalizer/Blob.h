#ifndef Blob_H
#define Blob_H
	
class Blob {

private:
	int _pixelCount;

	int _smallestY;
	int _biggestY;

	int _smallestX;
	int _biggestX;

public:
	Blob();
    void addPixel(int x, int y);
	void removePixel(int x, int y);

	int getGroundSurface(){return (getWidth() * getHeight());};
	int getRatio(){return (getWidth() / getHeight());};
	int getActualBlobPercentage(){ return (_pixelCount / getGroundSurface() * 100);};
	int getMass(){return _pixelCount;};

	int* getCornerPoints();

	int getWidth(){return (_biggestX - _smallestX);};
	int getHeight(){return (_biggestY - _smallestY);};



};

#endif