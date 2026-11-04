#pragma once
#include "raylib.h"

enum class swingState {
    Idle, Backswing, Downswing
};

enum class hitType {
    Weak, Slice, Hook, Pure, Idle
};

struct SwingData {
    swingState state = swingState::Idle;
    hitType currentHit = hitType::Idle;

    int currentFrame = 0;
    float runningTime = 0.0f;
    float updateTime = 1.0f / 24.0f;

    double startTime = 0.0;
    double holdTime = 0.0;

    Vector2 swingMeter = { 550.0f, 919.664f };
    Vector2 swingDuration = { 28.0f, 0.0f };

    float rotationSpeed = 90.0f;
};

void UpdateSwing(SwingData& swing, bool ballFlying,
    int& strokeCounter, float& flightTime,
    float deltaTime);
