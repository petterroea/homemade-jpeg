#include "quantization.h"

#include <stdio.h>

void do_quantization(float* dct_in, int* quantized_out) {
    for(int x = 0; x < DCT_SIZE; x++) {
        for(int y = 0; y < DCT_SIZE; y++) {
            quantized_out[x + y * DCT_SIZE] = static_cast<int>(dct_in[x + y * DCT_SIZE] / static_cast<float>(quantization_lookup_table[x + y * DCT_SIZE]));
        }
    }
    for (int i = 0; i < DCT_SIZE; i++) {
        for (int j = 0; j < DCT_SIZE; j++) {
            printf("%d\t", quantized_out[i + j * DCT_SIZE]);
        }
        printf("\n");
    }
}

void do_de_quantization(int* quantized_in, float* dct_out) {
    for(int x = 0; x < DCT_SIZE; x++) {
        for(int y = 0; y < DCT_SIZE; y++) {
            dct_out[x + y * DCT_SIZE] = static_cast<float>(quantized_in[x + y * DCT_SIZE]) * static_cast<float>(quantization_lookup_table[x + y * DCT_SIZE]);
        }
    }
    for (int i = 0; i < DCT_SIZE; i++) {
        for (int j = 0; j < DCT_SIZE; j++) {
            printf("%f\t", dct_out[i + j * DCT_SIZE]);
        }
        printf("\n");
    }
}