#pragma once
#define DCT_SIZE 8
#define DCT_SIGNAL_SIZE 8

extern float dct_lookup_buffer[DCT_SIZE * DCT_SIZE * DCT_SIGNAL_SIZE * DCT_SIGNAL_SIZE];

void build_lookup_table();

void do_dct(unsigned char* square, float* output);
void reverse_dct(float* dct_input, unsigned char* square_out);
