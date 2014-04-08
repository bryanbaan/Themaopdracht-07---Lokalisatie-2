#ifndef Point_H
#define Point_H

class Point {

private:
	int _x;
	int _y;
	
public: 
	Point();
	Point(int y, int x);

	void setX(int x);
	void setY(int y); 

	int getX();
	int getY();
};


#endif