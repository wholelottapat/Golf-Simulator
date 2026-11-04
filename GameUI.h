#pragma once
#include "raylib.h"
#include "Swing.h"
#include "BallPhysics.h"
#include "Course.h"

enum class gameScreen {
    mainMenu,
    holeIntro,
    playing,
    scoring,
    options
};

struct GameAssets {
    Texture2D golfer = {};
    Texture2D hole1 = {};
};

void DrawMainMenu(Vector2 mousePos,
    Rectangle playButton,
    Rectangle optionsButton,
    Rectangle quitButton);

void DrawHoleIntro(const GameAssets& assets,
    const CourseData& course);

void DrawGameplay(const GameAssets& assets,
    const CourseData& course,
    const SwingData& swing,
    const BallData& ball,
    const Camera2D& camera,
    Vector2 mousePos);

void DrawOptions();
void DrawScoring(const CourseData& course);
