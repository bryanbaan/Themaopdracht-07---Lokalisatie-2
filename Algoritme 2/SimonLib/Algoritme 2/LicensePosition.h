#ifndef LICENSEPOSITION_H
#define LICENSEPOSITION_H

#include <vector>


//! LicensePosition class.
//
//! This class iholds the positions from a license plate in an image.
//!
//! Team: Localization
//! Author(s): Mitchell Werensteijn & Yusuf Syakur
//! Version: 1.0
class LicensePosition {
public:
	//! Constructor
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

	//! Get top left position.
	std::vector<int> getTopLeft() { return topLeft; }
	//! Get top right position.
	std::vector<int> getTopRight() { return topRight; }
	//! Get bottom left position.
	std::vector<int> getBottomLeft() { return bottomLeft; }
	//! Get bottom right position.
	std::vector<int> getBottomRight() { return bottomRight; }
private:
	//! To hold the top left position.
	std::vector<int> topLeft;
	//! To hold the top right position.
	std::vector<int> topRight;
	//! To hold the bottom left position.
	std::vector<int> bottomLeft;
	//! To hold the bottom right position.
	std::vector<int> bottomRight;
};

#endif