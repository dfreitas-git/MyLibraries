
#pragma once

#include <Arduino.h>
#include "renderTypes.h"

//#################################
// Color definitions
//#################################

// Struct to hold the color definitions
struct palette { 
    RGB black          = {0,0,0};
    RGB white          = {255,255,255};
    RGB brown          = {102,51,64};
    RGB lightbrown     = {255,159,127};

    RGB darkgray       = {64,64,64};
    RGB mediumgray     = {96,96,96};
    RGB gray           = {128,128,128};
    RGB lightgray      = {192,192,192};

    RGB red32          = {32,0,0};
    RGB darkred        = {64,0,0};
    RGB meduimred      = {128,0,0};
    RGB red            = {255,0,0};
    RGB pixelgamered   = {255,40,40};

    RGB green32        = {0,32,0};
    RGB mediumgreen    = {0,128,0};
    RGB green          = {0,255,0};
    RGB olivegreen     = {64,80,0};
    RGB darkgreen      = {0,64,0};
    RGB limegreen      = {64,102,0};
    RGB pixelgamegreen = {40,255,60};

    RGB blue32         = {0,0,32};
    RGB darkblue       = {0,0,64};
    RGB mediumblue     = {0,0,128};
    RGB blue           = {0,0,255};
    RGB pixelgameblue  = {30,110,255};
    RGB pixelscoreblue = {60,160,255};

    RGB yellow32       = {32,18,0};
    RGB darkyellow     = {64,37,0};
    RGB yellow         = {255,150,0};
    RGB mediumyellow   = {128,75,0};

    RGB orange         = {255,159,0};
    RGB pink           = {255,192,203}; 
    RGB salmon         = {255,70,50}; 
    RGB purple         = {128,0,128};
};

constexpr RGB spiralColors[] = {
                {255,0,0},
                {0,255,0},
                {0,0,255},
              };


// Set up some pre-determined colors to cycle between for the checkerboard animation
// 2/7/2026 - Changed to black every other square for better contrast
constexpr RGB contrastColors[] = {
                {235,0,0},
                {0,0,0},
                //{0,235,0},
                {1,65,223},
                {0,0,0},
                //{10,229,0},
                {218,24,94},
                {0,0,0},
                //{74,160,240},
                {231,121,67},
                {0,0,0},
                //{72,106,16},
                {101,16,187},
                {0,0,0},
                //{5,17,37},
                {196,16,12},
                {0,0,0},
                //{0,235,235},
              };


constexpr RGB checkerBoardColors[] = {
                {64,0,0},
                {0,64,0},
                {0,0,64},
              };