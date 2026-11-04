#pragma once
#include "raylib.h"
#include "Swing.h"

struct BallData {
    Vector2 position = { 354.0f, 830.0f };
    Vector2 direction = { 0.0f, -1.0f };
    Vector2 golferPosition = { 108.0f, 839.0f };

    float size = 2.0f;
    float flightTime = 0.0f;
    bool flying = false;

    float aimAngle = -90.0f;
    float aimLength = 100.0f;

    Vector2 aimLineStart = { 354.0f, 830.0f };
    Vector2 aimLineEnd = { 354.0f, 730.0f };
};

void UpdateAim(BallData& ball, float deltaTime);

void UpdateBallPhysics(BallData& ball,
    const SwingData& swing,
    float deltaTime);
