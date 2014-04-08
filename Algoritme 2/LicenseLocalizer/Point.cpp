#include "stdafx.h"
#include "Point.h"

Point::Point() {
	_x = -1;
	_y = -1;
}

Point::Point(int x, int y) {
	_x = x;
	_y = y;
}

void Point::setX(int x) {
	_x = x;
}

void Point::setY(int y) {
	_y = y;
}

int Point::getX() {
	return _x;
}

int Point::getY() {
	return _y;
}