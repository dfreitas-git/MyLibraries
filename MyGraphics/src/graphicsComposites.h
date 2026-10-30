
#pragma once

#include <Arduino.h>
#include <renderTypes.h>
#include <colors.h>

// eyeball movement enum
enum EYEBALL_MOVE {CENTER, LEFT, RIGHT, UP, DOWN, LEFT_UP, LEFT_DOWN, RIGHT_UP, RIGHT_DOWN};

//#####################
//  Class Definition                         
//#####################
class GraphicsComposites {

public:
  void drawEyeball(FrameBuffer bbuf, int centerX, int centerY, int radius, const struct RGB& eyeColor, const struct RGB& bgColor, const struct RGB& fgColor, int move );
  void drawPacman(FrameBuffer bbuf,int centerX, int centerY, const struct RGB& bodyColor, const struct RGB& bgColor, bool mouthOpen);
  void drawCampfire(FrameBuffer bbuf,int centerX, int centerY);
  void drawRoastingStick(FrameBuffer bbuf,int centerX, int centerY);
//  void drawOwl(FrameBuffer buf, int centerX, int centerY,  bool blink, bool squawk);

private:


};
