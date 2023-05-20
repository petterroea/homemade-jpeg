#pragma once

#include <fstream>

void compress_image(unsigned char* image, int w, int h, std::ofstream* out);
unsigned char* decompress_image(std::ifstream* in);