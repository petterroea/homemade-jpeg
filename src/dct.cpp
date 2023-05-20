#include "dct.h"

#include <cmath>
#include <stdio.h>

#define pi 3.142857

int quantization_lookup_table[DCT_SIZE * DCT_SIZE] = {
    4, 3, 4, 4, 4, 6, 11, 15,
    3, 3, 3, 4, 5, 8, 14, 19,
    3, 4, 4, 5, 8, 12, 16, 20,
    4, 5, 6, 7, 12, 14, 18, 20,
    6, 6, 9, 11, 14, 17, 21, 23,
    9, 12, 12, 18, 23, 22, 25, 21,
    11, 13, 15, 17, 21, 23, 25, 21,
    13, 12, 12, 13, 16, 19, 21, 21

};

float dct_lookup_buffer[DCT_SIZE * DCT_SIZE * DCT_SIGNAL_SIZE * DCT_SIGNAL_SIZE];

void build_lookup_table() {
    // Per signal
    for(int i = 0; i < DCT_SIZE; i++) {
        for(int j = 0; j < DCT_SIZE; j++) {
            // Per pixel
            for(int k = 0; k < DCT_SIGNAL_SIZE; k++) {
                for(int l = 0; l < DCT_SIGNAL_SIZE; l++) {
                    int table_i = i*DCT_SIGNAL_SIZE;
                    int table_j = j*DCT_SIGNAL_SIZE;

                    dct_lookup_buffer[(table_i + k)+(table_j + l)*DCT_SIZE*DCT_SIGNAL_SIZE] = 
                        cos((2 * k + 1) * i * pi / (2 * DCT_SIZE)) *
                        cos((2 * l + 1) * j * pi / (2 * DCT_SIZE));
                }
            }
        }
    }
}

// https://www.geeksforgeeks.org/discrete-cosine-transform-algorithm-program/
void do_dct(unsigned char* square, float* dct) {
    int i, j, k, l;
 
    float ci, cj, dct1, sum;

    printf("Pre dct\n");
    for (i = 0; i < DCT_SIZE; i++) {
        for (j = 0; j < DCT_SIZE; j++) {
            printf("%d\t", square[i + j * DCT_SIZE]);
        }
        printf("\n");
    }
    
    // For each signal
    for (i = 0; i < DCT_SIZE; i++) {
        for (j = 0; j < DCT_SIZE; j++) {
 
            // ci and cj depends on frequency as well as
            // number of row and columns of specified matrix
            if (i == 0)
                ci = 1 / sqrt(DCT_SIZE);
            else
                ci = sqrt(2) / sqrt(DCT_SIZE);
            if (j == 0)
                cj = 1 / sqrt(DCT_SIZE);
            else
                cj = sqrt(2) / sqrt(DCT_SIZE);
 
            // sum will temporarily store the sum of
            // cosine signals
            // For each pixel
            sum = 0;
            for (k = 0; k < DCT_SIZE; k++) {
                for (l = 0; l < DCT_SIZE; l++) {
                    int signal_x= i*DCT_SIGNAL_SIZE;
                    int signal_y= j*DCT_SIGNAL_SIZE;
                    
                    dct1 = square[k + l * DCT_SIZE] * dct_lookup_buffer[(signal_x+ k)+(signal_y+ l)*DCT_SIZE*DCT_SIGNAL_SIZE];
                           
                    sum = sum + dct1;
                }
            }
            dct[i + j * DCT_SIZE] = ci * cj * sum;
        }
    }
 
    for (i = 0; i < DCT_SIZE; i++) {
        for (j = 0; j < DCT_SIZE; j++) {
            printf("%f\t", dct[i + j * DCT_SIZE]);
        }
        printf("\n");
    }
}

void reverse_dct(float* dct_input, unsigned char* square_out) {
    int i, j, k, l;
 
    float ci, cj, dct1, sum;
 
    // For each pixel
    for (k = 0; k < DCT_SIZE; k++) {
        for (l = 0; l < DCT_SIZE; l++) {
 
            // ci and cj depends on frequency as well as
            // number of row and columns of specified matrix
            // sum will temporarily store the sum of
            // cosine signals
            // For each signal
            sum = 0;
            for (i = 0; i < DCT_SIZE; i++) {
                for (j = 0; j < DCT_SIZE; j++) {
                    if (i == 0)
                        ci = 1 / sqrt(DCT_SIZE);
                    else
                        ci = sqrt(2) / sqrt(DCT_SIZE);
                    if (j == 0)
                        cj = 1 / sqrt(DCT_SIZE);
                    else
                        cj = sqrt(2) / sqrt(DCT_SIZE);
 
                    int signal_x = i*DCT_SIGNAL_SIZE;
                    int signal_y = j*DCT_SIGNAL_SIZE;
                    float dct_input_nocicj = dct_input[i + j * DCT_SIZE] * ci * cj;
                    
                    dct1 = dct_input_nocicj * dct_lookup_buffer[(signal_x + k)+(signal_y + l)*DCT_SIZE*DCT_SIGNAL_SIZE];
                           
                    sum = sum + dct1;
                }
            }
            square_out[k + l * DCT_SIZE] = sum;
        }
    }
 
    printf("Post DCT:\n");
    for (i = 0; i < DCT_SIZE; i++) {
        for (j = 0; j < DCT_SIZE; j++) {
            printf("%d\t", square_out[i + j * DCT_SIZE]);
        }
        printf("\n");
    }
}