
#pragma once

#include <stdint.h>

constexpr uint32_t WAND_PROTOCOL_MAGIC   = 0x57414E44;  // "WAND"
constexpr uint16_t WAND_PROTOCOL_VERSION = 1;

enum class WandMode : uint8_t {
    Panel = 0,
    Scene = 1
};

enum class WandGesture : uint8_t {
    None = 0,

    SwipeLeft,
    SwipeRight,
    SwipeUp,
    SwipeDown,

    SwipeUpLeft,
    SwipeUpRight,
    SwipeDownLeft,
    SwipeDownRight,

    ThrustIn,
    ThrustOut,

    CircleCW,
    CircleCCW
};

struct WandPacket {
    uint32_t magic;
    uint16_t version;

    uint32_t sequence;
    uint32_t timestampMs;

    WandMode mode;
    WandGesture gesture;

    // Wand orientation, radians
    float roll;
    float pitch;
    float yaw;

    // Wand angular velocity, radians/sec
    float gx;
    float gy;
    float gz;

    // Virtual wand-relative translational velocity
    float vx;
    float vy;
    float vz;
};