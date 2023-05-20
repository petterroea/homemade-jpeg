#include "utils.h"

#include "dct.h"

void extract_dct_square(unsigned char* image, unsigned char* out, int w, int h, int x, int y) {
    int image_x = x * DCT_SIZE;
    int image_y = y * DCT_SIZE;

    for(int xp = 0; xp < DCT_SIZE; xp++) {
        for(int yp = 0; yp < DCT_SIZE; yp++) {
            out[xp + yp * DCT_SIZE] = image[image_x + xp + (image_y + yp) * w];
        }
    }
}

void blit_dct_square(unsigned char* in, unsigned char* image, int w, int h, int x, int y) {
    int image_x = x * DCT_SIZE;
    int image_y = y * DCT_SIZE;

    for(int xp = 0; xp < DCT_SIZE; xp++) {
        for(int yp = 0; yp < DCT_SIZE; yp++) {
            image[xp + image_x + (yp + image_y) * w] = in[xp + yp * DCT_SIZE];
        }
    }
}

unsigned char* downsample(unsigned char* input, int w, int h) {
    int w_n = w/2;
    int h_n = h/2;

    unsigned char* output = new unsigned char[w_n * h_n];
    for(int x = 0; x < w_n; x++) {
        for(int y = 0; y < h_n; y++) {
            output[x + y * w_n] = static_cast<unsigned char>(
                (static_cast<unsigned int>(input[x*2+0 + (y*2+0)*w]) +
                static_cast<unsigned int>(input[x*2+0 + (y*2+1)*w]) +
                static_cast<unsigned int>(input[x*2+1 + (y*2+1)*w]) +
                static_cast<unsigned int>(input[x*2+1 + (y*2+0)*w])) / 4
            );
        }
    }
    return output;
}

unsigned char* upsample(unsigned char* input, int w, int h) {
    int w_n = w*2;
    int h_n = h*2;

    unsigned char* output = new unsigned char[w_n * h_n];
    for(int x = 0; x < w_n; x++) {
        for(int y = 0; y < h_n; y++) {
            output[x + y * w_n] = input[x/2 + (y/2)*w];
        }
    }
    return output;
}