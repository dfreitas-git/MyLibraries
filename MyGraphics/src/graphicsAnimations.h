
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

struct CheckerBoardSettings {
    int colorIndex = 0; 
    uint8_t squareScaler = 2;  // range of 1-4
};

struct EyeballSettings {
    int eyePosition_LR = 0;  // range of -1, 0, 1  (left, center, right)
    int eyePosition_UD = 0;  // range of -1, 0, 1  (down, center, up)
};

struct Pacman1Settings {
    int speed = 50;       // range of 0-99  0=stop, 99= full speed
    uint8_t vertPosition = 15;  // range of 0-29  0=bottom, 29 top
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
    void checker(FrameBuffer bbuf, const CheckerBoardSettings& settings);
    void spiralD(FrameBuffer bbuf);
    void flower(FrameBuffer bbuf);
    void eyeball( FrameBuffer bbuf, const EyeballSettings& settings, bool startBlink);
    void pacman1(FrameBuffer bbuf, const Pacman1Settings& settings);
    void flames(FrameBuffer bbuf);

  private:

    // State var for the fireworks animation
    FireworkState fwState = FIREWORK_ROCKET;
    uint32_t stateStartTime = 0;
    bool superStarActive = false;

    float lerp(float a, float b, float f);
    void  lerpColor(RGB& out, RGB& a, RGB& b, float f);
    float clamp(float val, float minVal, float maxVal);
};
