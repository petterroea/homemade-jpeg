#include "debug.h"
#include <stb_image_write.h>

void dump_yuv_to_png(yuv_image* yuv, int w, int h) {
    unsigned char* empty_color_channel = (unsigned char*)calloc(3, w*h);

    // Y only
    {
        yuv_image y_only;
        y_only.y_image = yuv->y_image;
        y_only.u_image = empty_color_channel;
        y_only.v_image = empty_color_channel;

        unsigned char* rgb_image_out = to_rgb(&y_only, w, h);

        stbi_write_png("testpng_out_y.png", w, h, 3, rgb_image_out, w*3);
        free(rgb_image_out);
    }
    // U only
    {
        yuv_image u_only;
        u_only.y_image = empty_color_channel;
        u_only.u_image = yuv->y_image;
        u_only.v_image = empty_color_channel;

        unsigned char* rgb_image_out = to_rgb(&u_only, w, h);

        stbi_write_png("testpng_out_u.png", w, h, 3, rgb_image_out, w*3);
        free(rgb_image_out);
    }
    // V only
    {
        yuv_image v_only;
        v_only.y_image = empty_color_channel;
        v_only.u_image = empty_color_channel;
        v_only.v_image = yuv->y_image;

        unsigned char* rgb_image_out = to_rgb(&v_only, w, h);

        stbi_write_png("testpng_out_v.png", w, h, 3, rgb_image_out, w*3);
        free(rgb_image_out);
    }
    free(empty_color_channel);
}