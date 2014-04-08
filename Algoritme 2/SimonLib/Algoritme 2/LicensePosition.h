#ifndef LICENSEPOSITION_H
#define LICENSEPOSITION_H

#include <vector>

class LicensePosition {
public:
	LicensePosition(int topLeftX, int topLeftY, int bottomRightX, int bottomRightY) : topLeft(topLeftX, topLeftY), bottomRight(bottomRightX, bottomRightY) { };

	std::vector<int> getTopLeft() { return topLeft; }
	std::vector<int> getBottomRight() { return bottomRight; }
private:
	std::vector<int> topLeft;
	std::vector<int> bottomRight;
};

#endif