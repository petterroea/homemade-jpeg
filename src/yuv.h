#pragma once

struct yuv_image {
    unsigned char* y_image;
    unsigned char* u_image;
    unsigned char* v_image;
};

yuv_image to_yuv(unsigned char* rgb, int w, int h);

unsigned char* to_rgb(yuv_image* image, int w, int h);