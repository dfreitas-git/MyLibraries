
#pragma once

#include <Arduino.h>
#include <renderTypes.h>
#include <colors.h>

// State variables for the fireworks animation.  ROCKET is for the single rising streak, EXPLOSION is when the "spokes" shoot out
typedef enum {
  FIREWORK_ROCKET,
  FIREWORK_EXPLOSION
} FireworkState;

struct ShootingStarSettings {
    uint8_t starCount = 5;
    float speedMultiplier = 1.0f;
};

class GraphicsAnimations {

  public:
    void clearBackground(FrameBuffer bbuf);
    void initShootingStars();
    void initSuperStar(float& direction);
    void shootingStar(FrameBuffer bbuf, const ShootingStarSettings& settings);
    void fadeFramebuffer(FrameBuffer bbuf, uint8_t decay);
    void fireworks(FrameBuffer bbuf);
    void initRocket();
    void initExplosion(float x, float y);
    void checker(FrameBuffer bbuf);
    void spiralD(FrameBuffer bbuf);
    void flower(FrameBuffer bbuf);
    void eyeball(FrameBuffer bbuf);
    void pacman1(FrameBuffer bbuf);
    void flames(FrameBuffer bbuf);
    //const bool& getSuperStarLaunchPending() const {
    //    return superStarLaunchPending;
   // }
   // void setSuperStarLaunchPending(bool status) {
   //    superStarLaunchPending  = status;
   // }
     

  private:

    // State var for the fireworks animation
    FireworkState fwState = FIREWORK_ROCKET;
    uint32_t stateStartTime = 0;
    bool superStarActive = false;

    float lerp(float a, float b, float f);
    void  lerpColor(RGB& out, RGB& a, RGB& b, float f);
    float clamp(float val, float minVal, float maxVal);
};
