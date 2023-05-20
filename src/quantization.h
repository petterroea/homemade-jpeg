#pragma once

#include "dct.h"

extern int quantization_lookup_table[DCT_SIZE * DCT_SIZE];

void do_quantization(float* dct_in, int* quantized_out);
void do_de_quantization(int* quantized_in, float* dct_out);