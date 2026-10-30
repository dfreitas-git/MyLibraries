
#include <graphicsGlobals.h>
#include <renderTypes.h>
#include <graphicsParticles.h>
#include <graphicsPrimitives.h>
#include <graphicsComposites.h>
#include <graphicsAnimations.h>

extern GraphicsParticles gPart;
extern GraphicsComposites gComp;
extern GraphicsAnimations gAnim;

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
    Star *s = &gPart.getStar(i);

    s->x  = random(0, COLUMNS);
    s->y  = random(0, ROWS);
    s->vx = random(-60, 60) / 100.0;   // horizontal drift
    s->vy = - (random(80, 140) / 100.0);  // vertical speed

    s->r = random(0, 255);
    s->g = random(0, 255);
    s->b = random(0, 255);
  }
}

// Set up parameters for the shooting star superStar
void GraphicsAnimations::initSuperStar(float& direction) {
    Star *superS = &gPart.getSuperStar();

    constexpr float SUPERSTAR_SPEED = 0.5f;  // Pixels per frame (tune to look good)
    float vx = SUPERSTAR_SPEED * cosf(direction);
    float vy = SUPERSTAR_SPEED * sinf(direction);

    float cx = (COLUMNS - 1) / 2.0f;
    float cy = (ROWS - 1) / 2.0f;

    // Distance from center to the boundary,
    // traveling opposite the swipe direction.
    float tx = fabsf(vx) > 0.0001f ? cx / fabsf(vx) : INFINITY;
    float ty = fabsf(vy) > 0.0001f ? cy / fabsf(vy) : INFINITY;

    float t = fminf(tx, ty);

    float startX = cx - t * vx;
    float startY = cy - t * vy;

    superS->x  = startX;
    superS->y  = startY;
    superS->vx = vx;   // horizontal drift
    superS->vy = vy;  // vertical speed
    superS->r =  255;
    superS->g =  255;
    superS->b =  255;
    superStarActive = true;

}

// Main rendering function
void GraphicsAnimations::shootingStar(FrameBuffer bbuf, const ShootingStarSettings& settings) {

  // Iterate over the entire framebuffer subtracting brightness from each
  // pixel until we fade to black
  fadeFramebuffer(bbuf, 10);   // larger number fades quicker

  for (int i = 0; i < settings.starCount; i++) {

    Star *s = &gPart.getStar(i);

    s->x += s->vx * settings.speedMultiplier;
    s->y += s->vy * settings.speedMultiplier;

    // wrap columns
    if (s->x < 0)        s->x += COLUMNS;
    if (s->x >= COLUMNS) s->x -= COLUMNS;

    // respawn
    if (s->y < 0) {
      s->x = random(0, COLUMNS);
      s->y = ROWS - 1;

      // Alter these to change the glide slope
      s->vx = (random(-60, 60) / 100.0);     // horizontal motion
      s->vy = - (random(16, 28) / 100.0);  // vertical motion

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

    if (col >= 0 && col < COLUMNS && row >= 0 && row < ROWS) {
        int idx = (row * COLUMNS + col);
        bbuf[idx] = {s->r, s->g, s->b};
    }
  }

  // Now fill in the superStar if it has been init'ed
  if (superStarActive) {
  Star *superS = &gPart.getSuperStar();

  superS->x += superS->vx * settings.speedMultiplier;
  superS->y += superS->vy * settings.speedMultiplier;

  if (superS->y < 0 ||
      superS->x < 0 ||
      superS->x >= COLUMNS) {
      superStarActive = false;
  } else {
      int col;
      int row;
 
      // Make it triple wide/tall
      for(int i=-1; i<2; i++) {
          col = (int)superS->x+i;
          row = (int)superS->y+i;
    
          if (col >= 0 && col < COLUMNS && row >= 0 && row < ROWS) {
              int idx = (row * COLUMNS + col);
              bbuf[idx] = {superS->r, superS->g, superS->b};
          }
      }
    }
  }
}

// ###############################################
// Functions for the fireworks animation
// A classic rocket streaking up and exploding into 
// a starburst which then fades out
// ###############################################
uint8_t NUM_EXPLOSION_SPOKES;
void GraphicsAnimations::initRocket() {

  Star *s = &gPart.getStar(0);

  s->x  = random(10, 20);  // keep them away from the edges
  s->y  = 0;   // bottom

  // diagonal upward motion
  s->vx = random(-30, 30) / 100.0;   // add horizontal drift
  s->vy = random(24, 32) / 100.0;  // strong upward velocity
  s->r = 255;
  s->g = 200;
  s->b = 100;

  fwState = FIREWORK_ROCKET;
  stateStartTime = millis();
}

void GraphicsAnimations::initExplosion(float x, float y) {

  uint8_t r,g,b;
  r = random(150, 255);
  g = random(100, 255);
  b = random(100, 255);

  NUM_EXPLOSION_SPOKES =  random(7,NUM_SPOKES);

  // Slow dow for fewer spokes so they don't look like leggy spiders...
  float speed = ((NUM_EXPLOSION_SPOKES * 9.0) / 1.6) / 100.0;

  for (int i = 0; i < NUM_EXPLOSION_SPOKES; i++) {
    Star *s = &gPart.getSpokes(i);

    // need to adjust gravity for different speeds (i.e. smaller number of spokes 
    // use slower speed //so use less gravity  so it doesn't deflect the path as much)
    s->gravity = .03 * (float(NUM_EXPLOSION_SPOKES) / float(NUM_SPOKES));
    s->x = x;
    s->y = y;

    float angle = (TWO_PI / NUM_EXPLOSION_SPOKES) * i;

    s->vx = cos(angle) * speed;
    s->vy = sin(angle) * speed;
    s->r = r;
    s->g = g;
    s->b = b;
    s->age = 0;
    //s->maxAge = random(18, 35);   // ~0.3–0.6 sec at 60fps
    //s->maxAge = 20;            // Keep them all the same size  
    s->maxAge = 100;            // Keep them all the same size  
    s->active = true;
  }

  fwState = FIREWORK_EXPLOSION;
  stateStartTime = millis();
}
// ###########################################################
// Main Fireworks code
// Control the rocket/explosion phases with state variables
// ###########################################################
void GraphicsAnimations::fireworks(FrameBuffer bbuf) {

  switch (fwState) {
    case FIREWORK_ROCKET: {
      gAnim.fadeFramebuffer(bbuf, 9);   // fade the rocket trail faster
      Star *s = &gPart.getStar(0);
      s->x += s->vx;
      s->y += s->vy;

       // Don't wrap columns
       if (s->x < 0)        s->x = 0;
       if (s->x >= COLUMNS) s->x = COLUMNS-1;

      int col = (int)s->x;
      int row = (int)s->y;

      // Write the bright head of the rocket path
      if (row >= 0 && row < ROWS) {
        gPrim.writePixel(bbuf, col, row, {s->r, s->g, s->b});
      }

      // explode at 3/4 height or if the rocket gets near the L/R edge of the panel.
      if (s->y > (ROWS * 0.75) || (s->x < 4) || (s->x >= COLUMNS-4)) {
        initExplosion(s->x, s->y);
      }

    } break;

    case FIREWORK_EXPLOSION: {
      gAnim.fadeFramebuffer(bbuf, 2);   // Slower fade for the firework burst
      for (int i = 0; i < NUM_EXPLOSION_SPOKES; i++) {
        Star *s = &gPart.getSpokes(i);

        if (!s->active) continue;

        s->x += s->vx;
        s->y += s->vy - s->gravity;

        s->vx *= 0.92;   // optional drag
        s->vy *= 0.92;

        // Don't wrap columns, if we're out of bounds, ignore this pixel
        if(s->x <= 0 || s->x >= COLUMNS-1) {
         continue;
        }

        s->age++;

        if (s->age >= s->maxAge) {
          s->active = false;
          continue;
        }

        int col = (int)s->x;
        int row = (int)s->y;
        
        if (col >= 0 && col < COLUMNS && row >= 0 && row < ROWS) {
          gPrim.writePixel(bbuf, col, row, {s->r,s->b,s->g});
        }
      }

      if (millis() - stateStartTime > 1000) {
        initRocket();
      }
    } break;
  }
}


//#############################################
//  Checker Board with changing colors and size
//#############################################
void GraphicsAnimations::checker(FrameBuffer bbuf, const CheckerBoardSettings& settings) {

  int period = 1000;

  // Use time to control the frequency of color changes
  uint32_t elapsed = millis();

  // Pick the color based on the pose parameters
  RGB color = checkerBoardColors[settings.colorIndex];

  uint8_t bright;

  if(settings.colorIndex < 33) {
      bright = map(settings.colorIndex,0,32,6,48);
      color = {bright,0,0};
  } else if(settings.colorIndex < 66) {
      bright = map(settings.colorIndex,33,62,6,96);
      color = {0,bright,0};
  } else {
      bright = map(settings.colorIndex,63,99,6,128);
      color = {0,0,bright};
  }

  // Now map the color based on the position
  for (int col = 0; col < COLUMNS; col++) {
    for (int row = 0; row < ROWS; row++) {

      // shift by n (where n is 1,2,3,4) so we "coarseify" the xor to happen across multiple row/col bands
      uint8_t coarseify = settings.squareScaler;
      bool fg = ((row >> coarseify) ^ (col >> coarseify)) & 1;
      RGB curColor;
      if(fg) {
        curColor = color;
      } else { 
        curColor = {0,0,0};
      }
      int idx = (row * COLUMNS + col);
      bbuf[idx] = {curColor.r, curColor.g, curColor.b};
    }
  }
}


//##################################
//  Double Spiral around the Sphere
//##################################
void GraphicsAnimations::spiralD(FrameBuffer bbuf) {

  constexpr int K = 1;  // Spiral twist factor
  constexpr int numSpirals = 2;
  constexpr int thickness = 1;  // How many pixels wide are the spirals
  static int fg0ColorIndex = 0;
  static int fg1ColorIndex = 1;

  RGB bgColor = {0,0,0};
  int colorArrLen = sizeof(spiralColors) / sizeof(spiralColors[0]);

  // color change period
  constexpr uint32_t spiralRevPeriod = 3000; //in mS 

  // How quickly we do framebuffer updates (in ms).  Can't be faster than 16ms which is the graphics task loop time.
  uint16_t animatePeriod = 50;
  static int animateCount = 1;

  static uint32_t phase = 0;
  static uint32_t lastColorSwitchTime = 0;
  uint32_t now = millis();

  // What animate cycle are we in?
  uint32_t cycle = now / animatePeriod; 
  static uint32_t lastCycle = 0;

  // Increment the animate count when we see a cycle transition
  // We increment up and down so the pattern rises/falls
  // Switch colors once the spiral rise and falls once
  static int animateIncrement = 1;
  static bool switchColors = false;
  if( cycle != lastCycle){
    lastCycle = cycle;
    if(animateCount >= ROWS-1) {
      animateIncrement = -1;
    }
    if(animateCount <= 1) {
      animateIncrement = 1;
      switchColors = true;
    }
    animateCount += animateIncrement;
  }

  // Change color once the spiral has done one rise/fall
  if (switchColors) {    
    switchColors = false;
    lastColorSwitchTime = now;
    fg0ColorIndex = fg1ColorIndex;
    fg1ColorIndex += 1;

    if(fg1ColorIndex == colorArrLen) {
       fg1ColorIndex = 0;
    }
  }


  // Fill the background
  for (int col = 0; col < COLUMNS; col++) {
    for (int row = 0; row < ROWS; row++) {
      gPrim.writePixel(bbuf,col, row, bgColor);
    }
  }
  // One spiral is fixed height, the other will grow from the bottom to the top
  gPrim.drawDiagonalBands(bbuf, phase, K, numSpirals, thickness, animateCount, spiralColors[fg0ColorIndex]);
  gPrim.drawDiagonalBands(bbuf, phase, -K, numSpirals, thickness, animateCount, spiralColors[fg1ColorIndex]);

}


//#########################
//  Expanding Flower
//#########################
void GraphicsAnimations::flower(FrameBuffer bbuf) {

  // How quickly we do framebuffer updates (in ms).  Can't be faster than 16ms which is the graphics task loop time.
  uint16_t animatePeriod = 25;
  static int animateCount = 1;

  // Get the colors
  static palette c;

  // Use time to control the animation
  uint32_t elapsed = millis();

  // What cycle are we in?
  uint32_t cycle = elapsed / animatePeriod; 
  static uint32_t lastCycle = 0;

  // Fill the background
  for (int col = 0; col < COLUMNS; col++) {
    for (int row = 0; row < ROWS; row++) {
      gPrim.writePixel(bbuf,col, row, c.black);
    }
  }

  // Increment the animate count when we see a cycle transition
  static int animateIncrement = 1;
  if( cycle != lastCycle){
    lastCycle = cycle;
    if(animateCount >= ROWS-1) {
      animateIncrement = -1;
    }
    if(animateCount <= 1) {
      animateIncrement = 1;
    }
    animateCount += animateIncrement;
  }

  // From bottom to top
  // Just pull the middle vertex up/down to grow the triangles
  gPrim.drawTriangle(bbuf,{0,0},{7,animateCount},{14,0}, c.red);
  gPrim.drawTriangle(bbuf,{14,0},{21,animateCount},{29,0}, c.blue);

  // From top to bottom
  gPrim.drawTriangle(bbuf,{0,29},{0,29-animateCount},{7,29}, c.blue);
  gPrim.drawTriangle(bbuf,{8,29},{14,29-animateCount},{21,29}, c.green);
  gPrim.drawTriangle(bbuf,{21,29},{29,29-animateCount},{29,29}, c.red);

}


//##############################################################
//  Animated blinking eyeballs
//  wand roll left/right, pitch up/down control eye position
//  thrustIn causes a blink
//##############################################################
void GraphicsAnimations::eyeball(FrameBuffer bbuf, const EyeballSettings& settings, bool startBlink) {

  // How quickly we do framebuffer updates (in ms)
  constexpr uint16_t blinkPeriod = 50;  // how fast to blink
  static uint8_t blinkRow = ROWS - 1;  // How far down the blink is

  // Get the colors
  static palette c;

  // Use time to control the animation
  uint32_t elapsed = millis();

  // What cycle are we in?
  uint32_t blinkCycle = elapsed / blinkPeriod; 
  static uint32_t lastBlinkCycle = 0;

  // Fill the black background
  for (int col = 0; col < COLUMNS; col++) {
    for (int row = 0; row < ROWS; row++) {
      gPrim.writePixel(bbuf,col, row, c.black);
    }
  }
  // Animate the eyeball by offsetting the iris/pupil based on the wand pose
  static EYEBALL_MOVE position[9] = {CENTER, LEFT, RIGHT, UP, DOWN, LEFT_UP, LEFT_DOWN, RIGHT_UP, RIGHT_DOWN};
  static int posIndex = 0;
  static bool blinkActive = false;
  #define CLOSING  0
  #define OPENING  1
  static uint8_t blinkDirection = CLOSING;

    // eyePosition 
    posIndex = 0;
    if(settings.eyePosition_LR == -1 && settings.eyePosition_UD == 0) 
        posIndex = 1;
    if(settings.eyePosition_LR == 1 && settings.eyePosition_UD == 0) 
        posIndex = 2;
    if(settings.eyePosition_LR == 0 && settings.eyePosition_UD == 1) 
        posIndex = 3;
    if(settings.eyePosition_LR == 0 && settings.eyePosition_UD == -1) 
        posIndex = 4;
    if(settings.eyePosition_LR == -1 && settings.eyePosition_UD == 1) 
        posIndex = 5;
    if(settings.eyePosition_LR == -1 && settings.eyePosition_UD == -1) 
        posIndex = 6;
    if(settings.eyePosition_LR == 1 && settings.eyePosition_UD == 1) 
        posIndex = 7;
    if(settings.eyePosition_LR == 1 && settings.eyePosition_UD == -1) 
        posIndex = 8;

    if(startBlink) {
      blinkActive = true;
      blinkRow = ROWS - 1;
      blinkDirection = CLOSING;
    }

  // Blink down and back up then done.
  if(blinkActive ) {
    if(blinkDirection == CLOSING) {
      blinkRow -= 1;
      if(blinkRow == 0) {
        blinkDirection = OPENING;
      }
    } else {
      blinkRow += 1;
      if(blinkRow == ROWS-1) {
        blinkActive = false;
      }
    }
  }
  // Draw Eyeball
  gComp.drawEyeball(bbuf,7, 15, 6, c.mediumblue, c.black, c.darkgray, position[posIndex] );
  gComp.drawEyeball(bbuf,22, 15, 6, c.mediumblue, c.black, c.darkgray, position[posIndex] );

  //if(blinkTrigger < 0) {
  if(blinkActive) {
    // Mask the eyeball from the top down over the blinkPeriod 
    gPrim.drawRect(bbuf,0,blinkRow,29,29, 0,c.black);
  }
}

//#########################
//  Pacman chasing ghosts
//#########################
void GraphicsAnimations::pacman1(FrameBuffer bbuf, const Pacman1Settings& settings) {

  // How quickly we do movement updates (in ms)
  uint16_t animatePeriod = 100;
  uint16_t animateMouthPeriod = 200;

  // Get the colors
  static palette c;

  // Use time to control the animation
  uint32_t elapsed = millis();

  // What cycle are we in?
  uint32_t cycle = elapsed / animatePeriod; 
  uint32_t mouthCycle = elapsed / animateMouthPeriod; 
  static uint32_t lastCycle = 0;
  static uint32_t lastMouthCycle = 0;

  // Fill the black background
  for (int col = 0; col < COLUMNS; col++) {
    for (int row = 0; row < ROWS; row++) {
      gPrim.writePixel(bbuf, col, row, c.black);
    }
  }
  // Animate the mouth by drawing open/close based on the cycle we are in
  static bool mouthOpen = false;
  static bool jumpUp = false;
  static int centerX = COLUMNS-1;
  if(cycle != lastCycle) {
    lastCycle = cycle;
    centerX--;
    if(centerX == -11) {
      centerX=COLUMNS+10;
    }
  }
  if(mouthCycle != lastMouthCycle) {
    mouthOpen = !mouthOpen;
    lastMouthCycle = mouthCycle;
  }
  // Draw Pacman
  gComp.drawPacman(bbuf,centerX,15,c.darkyellow,c.black,mouthOpen);
}

//#########################
//  Campfire flames
//#########################
void GraphicsAnimations::flames(FrameBuffer bbuf) {

  // How quickly we do movement updates (in ms)
  uint16_t animatePeriod = 10;

  // Get the colors
  static palette c;

  // Use time to control the animation
  uint32_t elapsed = millis();

  // What cycle are we in?
  uint32_t cycle = elapsed / animatePeriod; 
  static uint32_t lastCycle = 0;

  // Fill the black background
  for (int col = 0; col < COLUMNS; col++) {
    for (int row = 0; row < ROWS; row++) {
      gPrim.writePixel(bbuf, col, row, c.black);
    }
  }

  // Animate the flames by modifying the flame height/color
  // Slowing down the flicker rate using the cycle counter
  if(cycle != lastCycle) {
    lastCycle = cycle;
    gComp.drawCampfire(bbuf,15,0);
  }
}