#pragma once
#include <string>
#include <stdio.h>
#include <fstream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

int main(int argc, char* argv[]) {
	std::string characters = "@&%QWNM0gB$#DR8mHXKAUbGOpV4d9h6PkqwSE2]ayjxY5Zoen[ult13If}C{iF|(7J)vTLs?z/*cr!+<>;=^,_:'-.` ";
	float length = characters.length();
	std::string file_path;


	if (argc > 1) {
		printf("%s\n", argv[1]);
		file_path = argv[1];
	}
	else {
		printf("Please enter a file path\n");
	}

	int x, y, n;
	unsigned char* data = stbi_load(file_path.c_str(), &x, &y, &n, 3);
	if (stbi_failure_reason()) {
		printf("%s", stbi_failure_reason());
	}

	int index = 0;
	std::ofstream outputFile("output.txt", std::ofstream::out | std::ofstream::trunc);
	if (outputFile.is_open()) {
		for (long i = 0; i < 3 * x * y; i += 3) {
			if (data != nullptr && x > 0 && y > 0) {
				int r = static_cast<int>(data[i]);
				int g = static_cast<int>(data[i + 1]);
				int b = static_cast<int>(data[i + 2]);

				float grayscale = 0.299 * r + 0.587 * g + 0.114 * b;
				char ascii = characters[round((grayscale / 255.0) * (length - 1.0))];
				if (ascii == NULL) {
					printf("CHAR WAS NULL. GRAYSCALE: %.6f\n", grayscale);
				}
				outputFile << ascii << " ";

				if (index == x) {
					outputFile << "\n";
					index = 0;
				}
				++index;
			}
		}
	}

	return 0;
}
