#pragma once
void extract_dct_square(unsigned char* image, unsigned char* out, int w, int h, int x, int y);
void blit_dct_square(unsigned char* in, unsigned char* image, int w, int h, int x, int y);

unsigned char* downsample(unsigned char* input, int w, int h);
unsigned char* upsample(unsigned char* input, int w, int h);