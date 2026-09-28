
#pragma once

#include <Arduino.h>
#include <renderTypes.h>
#include <colors.h>

class GraphicsAnimations {

  public:
    void clearBackground(FrameBuffer bbuf);
    void initShootingStars();
    void shootingStar(FrameBuffer bbuf);
    void fadeFramebuffer(FrameBuffer bbuf, uint8_t decay);

  private:
    float lerp(float a, float b, float f);
    void  lerpColor(RGB& out, RGB& a, RGB& b, float f);
    float clamp(float val, float minVal, float maxVal);
};