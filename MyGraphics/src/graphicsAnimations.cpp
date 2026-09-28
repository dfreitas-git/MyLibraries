
#include <graphicsGlobals.h>
#include <renderTypes.h>
#include <graphicsParticles.h>
#include <graphicsPrimitives.h>
#include <graphicsAnimations.h>

extern GraphicsParticles gParticles;

// ###########################
// Helpful utility functions
// ############################

// linear interpolation.  Return number between a and b.  f is interpolation factor between 0 and 1.0.
float GraphicsAnimations::lerp(float a, float b, float f) {
    return a + f * (b - a);
}

// linear interpolation to transition from one color to another.  Pass two RGB color structs, load the "out" struct with the interpolated colors.
// f is the interpolation point (between 0.0 and 1.0)
void GraphicsAnimations::lerpColor(RGB& out, RGB& a, RGB& b, float f) {
     out.r = a.r + f * (b.r - a.r);
     out.g = a.g + f * (b.g - a.g);
     out.b = a.b + f * (b.b - a.b);
}

// clamp  For clamping a number between two ranges
float GraphicsAnimations::clamp(float val, float minVal, float maxVal) {
  if(val - minVal < .001) {
    return minVal;
  } else if(val - maxVal > .001) {
    return maxVal;
  } else {
    return val;
  }
}

// Fill the sphere background
void GraphicsAnimations::clearBackground(FrameBuffer bbuf) {
  for (int col = 0; col < COLUMNS; col++) {
    for (int row = 0; row < ROWS; row++) {
      gPrim.writePixel(bbuf,col, row, {0,0,0});
    }
  }
}

//###############################################################################
//  Animated Shooting Star
//  We have an active "star" (head) that traces a path into the framebuffer, then
//  we use a fade function to go erase the trails with a defined time-constant.
//  Renders a a bright star shooting across the sphere with the tail fading off
//  behind it.
//###############################################################################
//     Helper functions 
void GraphicsAnimations::fadeFramebuffer(FrameBuffer bbuf, uint8_t decay) {
  for (int col = 0; col < COLUMNS; col++) {
    for (int row = 0; row < ROWS; row++) {
        int idx = (row * COLUMNS + col);
        uint8_t r = bbuf[idx].r;
        uint8_t g = bbuf[idx].g;
        uint8_t b = bbuf[idx].b;
        bbuf[idx].r = (r > decay) ? (r - decay) : 0;
        bbuf[idx].g = (g > decay) ? (g - decay) : 0;
        bbuf[idx].b = (b > decay) ? (b - decay) : 0;
    }
  }
}

// Set up parameters for multiple shootingStars
void GraphicsAnimations::initShootingStars() {
  for (int i = 0; i < NUM_STARS; i++) {
    Star *s = &gParticles.getStar(i);

    s->x  = random(0, COLUMNS);
    s->y  = random(0, ROWS);
    s->vx = random(-30, 30) / 100.0;   // subtle drift
    s->vy = - (random(80, 140) / 100.0);

    s->r = random(0, 255);
    s->g = random(0, 255);
    s->b = random(0, 255);
  }
}

// Main rendering function
void GraphicsAnimations::shootingStar(FrameBuffer bbuf) {

  // Iterate over the entire framebuffer subtracting brightness from each
  // pixel until we fade to black
  fadeFramebuffer(bbuf, 10);   // larger number fades quicker

  for (int i = 0; i < NUM_STARS; i++) {

    Star *s = &gParticles.getStar(i);

    s->x += s->vx;
    s->y += s->vy;

    // wrap columns
    if (s->x < 0)        s->x += COLUMNS;
    if (s->x >= COLUMNS) s->x -= COLUMNS;

    // respawn
    if (s->y < 0) {
      s->x = random(0, COLUMNS);
      s->y = ROWS - 1;

      // Alter these to change the glide slope
      s->vx = random(-60, 60) / 100.0;     // horizontal motion
      s->vy = - (random(16, 28) / 100.0);  // vertical motion
      //s->vx = random(-300, 300) / 100.0;   // faster
      //s->vy = - (random(80, 140) / 100.0); // faster

      // Every now and then throw in a "flare"
      if (random(0, 100) < 3) {
        s->r = s->g = s->b = 255;
      } else {
        s->r = random(0, 255);
        s->g = random(0, 255);
        s->b = random(0, 255);
      }
    }

    int col = (int)s->x;
    int row = (int)s->y;

    int idx = (row * COLUMNS + col);
    bbuf[idx] = {s->r, s->g, s->b};
  }
}
