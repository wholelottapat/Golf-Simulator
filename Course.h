#pragma once
#include "raylib.h"
#include "BallPhysics.h"

struct CourseData {
    int holeNum = 1;
    int strokeCounter = 1;

    int holeDistances[9] = {
        166, 255, 300, 400, 500,
        600, 700, 800, 900
    };

    Vector2 hole1Pin = { 343.0f, 109.0f };

    float mapScale = 1.814f;
};

bool CheckHoleComplete(const CourseData& course,
    const BallData& ball);
