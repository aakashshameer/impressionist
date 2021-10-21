/****************************************************************************
 * Copyright ©2017 Brian Curless.  All rights reserved.  Permission is hereby
 * granted to students registered for University of Washington CSE 457 or CSE
 * 557 for use solely during Autumn Quarter 2017 for purposes of the course.
 * No other use, copying, distribution, or modification is permitted without
 * prior written consent. Copyrights for third-party components of this work
 * must be honored.  Instructors interested in reusing these course materials
 * should contact the author.
 ****************************************************************************/

#include "filter.h"

Kernel::Kernel(){
//    filter_ = new float[5][5];
}

void Kernel::SetKernelValue(int i, int j, float f){
   filter_[i][j] = f;
}

float Kernel::GetKernelValue (int i, int j){
    return filter_[i][j];
}

void Filter::ApplyFilterKernel(const unsigned char *source, unsigned char *dest, unsigned int width, unsigned int height, Kernel &k, int offset, bool clamping) {
    // REQUIREMENT: Implement this function
    int rGrid [height+4][width+4];
    int gGrid [height+4][width+4];
    int bGrid [height+4][width+4];

    int dest_rGrid [height][width];
    int dest_gGrid [height][width];
    int dest_bGrid [height][width];

    int point = 0;
    for(unsigned int i = 2; i < height + 2; i++) {
        for(unsigned int j = 2; j < width + 2; j++) {
            rGrid[i][j] = source[point];
            point++;
            gGrid[i][j] = source[point];
            point++;
            bGrid[i][j] = source[point];
            point += 2; //go to the next point and skip over alpha value
        }
    }

    for(unsigned int i = 0; i < 2; i++){
        for(unsigned int j = 0; j < 2; j++){
            rGrid[i][j] = rGrid[ 3 - i][3 - j];
            gGrid[i][j] = gGrid[ 3 - i][3 - j];
            bGrid[i][j] = bGrid[ 3 - i][3 - j];
        }
    }

    for(unsigned int i = height + 2; i < height + 4; i++){
        for(unsigned int j = width + 2; j < width + 4; j++){
            rGrid[i][j] = rGrid[2*height + 3 - i][2*width + 3 - j];
            gGrid[i][j] = gGrid[2*height + 3 - i][2*width + 3 - j];
            bGrid[i][j] = bGrid[2*height + 3 - i][2*width + 3 - j];
        }
    }


    for(unsigned int i = 2; i < height + 2; i++){
        for(unsigned int j = 2; j < width + 2; j++){
            float r_sum = 0.0f;
            float g_sum = 0.0f;
            float b_sum = 0.0f;
            for(unsigned int l = 0; l < 5; l++){
                for(unsigned int m = 0; j < 5; j++){
                    r_sum += k.GetKernelValue(l,m) * rGrid[i - 2 + l][j - 2 + m];
                    g_sum += k.GetKernelValue(l,m) * gGrid[i - 2 + l][j - 2 + m];
                    b_sum += k.GetKernelValue(l,m) * bGrid[i - 2 + l][j - 2 + m];
                }
            }

            dest_rGrid[i - 2][j - 2] = r_sum;
            dest_gGrid[i - 2][j - 2] = g_sum;
            dest_bGrid[i - 2][j - 2] = b_sum;
        }
    }

    point = 0;
    for(unsigned int i = 0; i < height; i++) {
        for(unsigned int j = 0; j < width; j++) {
            dest[point] = dest_rGrid[i][j];
            point++;
            dest[point] = dest_gGrid[i][j];
            point++;
            dest[point] = dest_bGrid[i][j];
            point += 2; //go to the next point and skip over alpha value
        }
    }



}

void Filter::ApplyGaussianBlur(const unsigned char *source, unsigned char *dest, unsigned int width, unsigned int height, float sigma) {
    unsigned int blur_radius = sigma * 3;
    unsigned int size = blur_radius * 2 + 1;
    // EXTRA CREDIT: Implement this function
}

void Filter::ApplyBilateralMeanBlur(const unsigned char *source, unsigned char *dest, unsigned int width, unsigned int height, unsigned int domain_half_width, unsigned int range) {
    unsigned int size = domain_half_width * 2 + 1;
    // REQUIREMENT: Implement this function
}

void Filter::ApplyBilateralGaussianBlur(const unsigned char *source, unsigned char *dest, unsigned int width, unsigned int height, float sigma_space, float sigma_range) {
    unsigned int radius = sigma_space * 3;
    unsigned int size = radius * 2 + 1;
    // EXTRA CREDIT: Implement this function
}
