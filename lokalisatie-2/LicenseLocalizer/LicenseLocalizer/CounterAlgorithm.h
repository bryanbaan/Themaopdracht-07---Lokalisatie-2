#ifndef COUNTERALGORITHM_H
#define COUNTERALGORITHM_H

#include "../KernelWalker.h"
#include <algorithm>
#include <vector>
#define MEDIANSIZE 6

class CounterAlgorithm {
public:
	static void doAlgorithm(Image & image) {
		int srcHeight = image.getHeight();
		int srcWidth = image.getWidth();
		int amountData = srcHeight * srcWidth * 3;

		unsigned char * dataptr = image.getDataPointer();

		std::vector<int> values;
		for (int i = 0; i < amountData; i += 3) {
			values.push_back(dataptr[i]);
		}

		int counter = 0;
		std::vector<int> amounts;
		for (int i = 0; i < MEDIANSIZE; i++) {
			amounts.push_back(0);
		}
		for (int row = MEDIANSIZE; row < srcHeight - MEDIANSIZE; row++) {
			counter = 0;
			for (int x = MEDIANSIZE; x < srcWidth - MEDIANSIZE; x++) {
				if (values[row*srcWidth + x] == 255 && values[row*srcWidth + x + 1] == 0) counter++;
			}
			amounts.push_back(counter);
		}
		for (int i = 0; i < MEDIANSIZE; i++) {
			amounts.push_back(0);
		}


		std::ofstream output("counter.csv");

		if (output.is_open()) {
			output << "sep=,\n";

			for (int i = 0; i < amounts.size(); i++) {
				output << i << ',' << amounts[i] << std::endl;
			}

			output.close();
		}

		
	}
};

#endif