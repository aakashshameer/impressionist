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

void Filter::ApplyFilterKernel(const unsigned char *source, unsigned char *dest, unsigned int width, unsigned int height, Kernel &k, int offset, bool clamping) {
    // REQUIREMENT: Implement this function
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