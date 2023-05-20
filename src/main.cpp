#include <iostream>
#include <fstream>
#include <filesystem>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

#include "yuv.h"
#include "debug.h"
#include "dct.h"
#include "quantization.h"
#include "utils.h"
#include "io.h"

int main(int argc, char **argv) {
    std::cout << "Hello, world!" << std::endl;
    if(argc != 2) {
        std::cout << "Usage: homeMadeJpeg [in]" << std::endl;
        return 0;
    }

    std::filesystem::path inFile(argv[1]);
    if(!std::filesystem::exists(inFile)) {
        std::cout << "File " << argv[1] << " does not exist" << std::endl;
        return 0;
    }

    int w;
    int h;
    int comp;
    unsigned char* image = stbi_load(argv[1], &w, &h, &comp, STBI_rgb);
    if(w % 8 != 0 || h % 8 != 0) {
        std::cout << "ERROR: Image width and height must be divisible by 8" << std::endl;
        return 0;
    }

    yuv_image yuv = to_yuv(image, w, h);

    // DCT time
    build_lookup_table();

    /*
    unsigned char dct_square[DCT_SIZE * DCT_SIZE];
    extract_dct_square(yuv.y_image, dct_square, w, h, 0, 0);
    float dct_out[DCT_SIZE * DCT_SIZE];
    do_dct(dct_square, dct_out);
    int quant_out[DCT_SIZE * DCT_SIZE];
    do_quantization(dct_out, quant_out);
    */

    std::ofstream output("out.bin", std::ios::binary);
    unsigned char* u_downscaled = downsample(yuv.u_image, w, h);
    unsigned char* v_downscaled = downsample(yuv.v_image, w, h);

    compress_image(yuv.y_image, w, h, &output);
    compress_image(u_downscaled, w/2, h/2, &output);
    compress_image(v_downscaled, w/2, h/2, &output);

    output.close();

    // Read the file and run the opposite direction
    std::cout << "Done writing, now trying reading..." << std::endl;

    yuv_image yuv_read;
    std::ifstream input("out.bin", std::ios::binary);

    yuv_read.y_image = decompress_image(&input);
    unsigned char* u_down = upsample(decompress_image(&input), w/2, h/2);
    unsigned char* v_down = upsample(decompress_image(&input), w/2, h/2);

    yuv_read.u_image = u_down;
    yuv_read.v_image = v_down;

    unsigned char* rgb_image_out = to_rgb(&yuv_read, w, h);

    int channel_num = 3;
    stbi_write_png("testpng_out_post_compress.png", w, h, channel_num, rgb_image_out, w*channel_num);

    dump_yuv_to_png(&yuv_read, w, h);

    /*
    // Do it the other way
    float de_quant[DCT_SIZE * DCT_SIZE];
    do_de_quantization(quant_out, de_quant);
    unsigned char dct_square_out[DCT_SIZE * DCT_SIZE];
    reverse_dct(de_quant, dct_square_out);
    */


    /*
    // YUV conversion Test: Convert back and write it to disk
    int channel_num = 3;
    unsigned char* rgb_image_out = to_rgb(&yuv, w, h);

    stbi_write_png("testpng_out.png", w, h, channel_num, rgb_image_out, w*channel_num);

    dump_yuv_to_png(&yuv, w, h);
    */

    return 1;
}