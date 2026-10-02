
#pragma once

#include <Arduino.h>

// Struct for the shootingStar animation
#define NUM_STARS 5
#define NUM_SPOKES 12

typedef struct {
  float x;
  float y;
  float vx;
  float vy;
  uint8_t r, g, b;
  uint16_t age;
  uint16_t maxAge;
  bool active;
  float gravity;
} Star;


class GraphicsParticles {

public:
  Star& getStar(int i);
  Star& getSpokes(int i);

private:
  // This is used in the star animation.  Its the number of stars shooting at any given time
  Star stars[NUM_STARS];

  // This is used in the fireworks animation.  Its the number of exploding spokes
  Star explosionSpokes[NUM_SPOKES];

};
