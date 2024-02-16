#define _USE_MATH_DEFINES
#include <cmath>
#include <vector>
#include <iostream>

// thank you ChatGPT :)
std::vector<float> oscillate_rgb(float time, float freq) {
    float amplitude = 0.5f;
    float sin_period = 2.0f * (float)M_PI; // one full cycle
    float angle = time * freq;

    // evenly desynchronize color channels
    float red_phase = sin_period / 3.0f;
    float green_phase = sin_period * 2 / 3.0f;
    float blue_phase = sin_period;

    // set amplitude and normalize sin values to unit interval
    float red = sin(angle + red_phase) * amplitude + amplitude;
    float green = sin(angle + green_phase) * amplitude + amplitude;
    float blue = sin(angle + blue_phase) * amplitude + amplitude;

    std::vector<float> color_channels = {red, green, blue};
    return color_channels;
}