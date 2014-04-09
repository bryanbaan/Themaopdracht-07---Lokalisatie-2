#ifndef LICENSEPOSITION_H
#define LICENSEPOSITION_H

#include <vector>

class LicensePosition {
public:
	LicensePosition(int topLeftX, int topLeftY, int topRightX, int topRightY, int bottomLeftX, int bottomLeftY, int bottomRightX, int bottomRightY) {
		topLeft.push_back(topLeftX);
		topLeft.push_back(topLeftY);

		topRight.push_back(topRightX);
		topRight.push_back(topRightY);

		bottomLeft.push_back(bottomLeftX);
		bottomLeft.push_back(bottomLeftY);

		bottomRight.push_back(bottomRightX);
		bottomRight.push_back(bottomRightY);
	};

	std::vector<int> getTopLeft() { return topLeft; }
	std::vector<int> getTopRight() { return topRight; }
	std::vector<int> getBottomLeft() { return bottomLeft; }
	std::vector<int> getBottomRight() { return bottomRight; }
private:
	std::vector<int> topLeft;
	std::vector<int> topRight;
	std::vector<int> bottomLeft;
	std::vector<int> bottomRight;
};

#endif