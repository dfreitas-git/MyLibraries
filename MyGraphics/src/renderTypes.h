
#pragma once
#include <Arduino.h>

// Struct to hold pixel RGB value
struct RGB {
    uint8_t r, g, b;
};

static_assert(sizeof(RGB) == 3,
              "RGB must be exactly 3 bytes");


// More descriptive for the graphics calls which need a framebuffer pointer
using FrameBuffer = RGB*;

// Struct to hold vertex point
struct Vec2 {
    int x, y;
};
