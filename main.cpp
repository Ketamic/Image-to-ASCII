#pragma once
#include <string>
#include <stdio.h>
#include <fstream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

int main(int argc, char* argv[]) {
	// Characters that I use to create images in order from darkest to lightest
	std::string characters = "@&%QWNM0gB$#DR8mHXKAUbGOpV4d9h6PkqwSE2]ayjxY5Zoen[ult13If}C{iF|(7J)vTLs?z/*cr!+<>;=^,_:'-.` ";
	// length of all the characters i plan to use
	float length = characters.length();
	std::string file_path;

	// Making sure that there was a value passed for the file path
	if (argc > 1) {
		printf("%s\n", argv[1]);
		file_path = argv[1];
	}
	else {
		printf("Please enter a file path\n");
	}

	// Load file and get x and y size of file
	int x, y, n;
	unsigned char* data = stbi_load(file_path.c_str(), &x, &y, &n, 3);

	// Check for any failures loading the file
	if (stbi_failure_reason()) {
		printf("%s", stbi_failure_reason());
	}
	
	int index = 0;
	// Setting file to delete any previous outputs
	std::ofstream outputFile("output.txt", std::ofstream::out | std::ofstream::trunc);
	if (outputFile.is_open()) {
		// Since the array is 3x as long because each color value is stored one after another,
		// I calculate the amount of pixels in the image and then multiply it by 3, and increment by 3
		for (long i = 0; i < 3 * x * y; i += 3) {
			if (data != nullptr && x > 0 && y > 0) {
				// getting the rgb values from the data
				int r = static_cast<int>(data[i]);
				int g = static_cast<int>(data[i + 1]);
				int b = static_cast<int>(data[i + 2]);

				// Calculating the most accurate grayscale value by using the weighted method
				float grayscale = 0.299 * r + 0.587 * g + 0.114 * b;

				// Calculating how dark the greyscale is into a percentage, multiplying it by the
				// length of the characters and then rounding it in order to select the best character
				char ascii = characters[round((grayscale / 255.0) * (length - 1.0))];

				// If the character is null for any reason, print out the greyscale
				if (ascii == NULL) {
					printf("CHAR WAS NULL. GRAYSCALE: %.6f\n", grayscale);
				}
				// coutput to file with a space in an attempt to try and make the image more square
				outputFile << ascii << " ";

				// If the index is equivalent to X then we have reached the end of pixels in that row
				// and need to return and reset the index back to zero
				if (index == x) {
					outputFile << "\n";
					index = 0;
				}
				// increment index
				++index;
			}
		}
	}

	return 0;
}
