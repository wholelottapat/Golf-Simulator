#include "raylib.h"
#include "raymath.h"

#include "GolfClubs.h"
#include "Swing.h"
#include "BallPhysics.h"
#include "Course.h"
#include "GameUI.h"

const int screenWidth = 800;
const int screenHeight = 1004;

int main()
{
    InitWindow(
        screenWidth,
        screenHeight,
        "Golf Simulator - OpenGL 2.1"
    );

    SetExitKey(KEY_NULL);
    SetTargetFPS(60);

    gameScreen currentScreen = gameScreen::mainMenu;

    Rectangle playButton = { 300, 350, 200, 60 };
    Rectangle optionsButton = { 300, 430, 200, 60 };
    Rectangle quitButton = { 300, 510, 200, 60 };

    double introStartTime = 0.0;

    // Game Data
    SwingData swing;
    BallData ball;
    CourseData course;

    // Game Assets
    GameAssets assets;
    assets.golfer =
        LoadTexture("resources/spritesheetGolfer.png");

    assets.hole1 =
        LoadTexture("resources/hole1WilliamsCreek.png");

    // Camera
    Camera2D camera = { 0 };
    camera.target = { 354, 830 };
    camera.offset = { screenWidth / 2.0f, 800 };
    camera.rotation = 0.0f;
    camera.zoom = 2.2f;

    while (!WindowShouldClose())
    {
        float GFT = GetFrameTime();
        Vector2 mousePos = GetMousePosition();

        // Main Menu
        if (currentScreen == gameScreen::mainMenu)
        {
            if (CheckCollisionPointRec(mousePos, playButton) &&
                IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                currentScreen = gameScreen::holeIntro;
                introStartTime = GetTime();
            }

            if (CheckCollisionPointRec(mousePos, optionsButton) &&
                IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                currentScreen = gameScreen::options;
            }

            if (CheckCollisionPointRec(mousePos, quitButton) &&
                IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                break;
            }
        }

        // Hole Introduction
        if (currentScreen == gameScreen::holeIntro &&
            GetTime() - introStartTime >= 4.5)
        {
            currentScreen = gameScreen::playing;
        }

        // Escape to Main Menu
        if (IsKeyPressed(KEY_ESCAPE) &&
            currentScreen != gameScreen::mainMenu)
        {
            currentScreen = gameScreen::mainMenu;
        }

        // Gameplay Updates
        if (currentScreen == gameScreen::playing)
        {
            UpdateSwing(
                swing,
                ball.flying,
                course.strokeCounter,
                ball.flightTime,
                GFT
            );

            UpdateBallPhysics(ball, swing, GFT);
            UpdateAim(ball, GFT);

            // Camera Mechanics
            if (ball.flying)
            {
                camera.target = ball.position;
            }

            float mapWidth =
                assets.hole1.width * course.mapScale;

            float mapHeight =
                assets.hole1.height * course.mapScale;

            float leftLimit =
                camera.offset.x / camera.zoom;

            float rightLimit =
                mapWidth -
                (screenWidth - camera.offset.x) / camera.zoom;

            float topLimit =
                camera.offset.y / camera.zoom;

            float bottomLimit =
                mapHeight -
                (screenHeight - camera.offset.y) / camera.zoom;

            camera.target.x = Clamp(
                camera.target.x, leftLimit, rightLimit
            );

            camera.target.y = Clamp(
                camera.target.y, topLimit, bottomLimit
            );

            // Scoring Mechanics
            if (CheckHoleComplete(course, ball))
            {
                currentScreen = gameScreen::scoring;
                introStartTime = GetTime();
            }
        }

        // Scoring Screen Transition
        if (currentScreen == gameScreen::scoring &&
            GetTime() - introStartTime >= 4.5)
        {
            // Keep the current hole until the next hole
            // has its own texture and starting position.
            currentScreen = gameScreen::mainMenu;
        }

        // Drawing
        BeginDrawing();
        ClearBackground(DARKGREEN);

        if (currentScreen == gameScreen::mainMenu)
        {
            DrawMainMenu(
                mousePos,
                playButton,
                optionsButton,
                quitButton
            );
        }
        else if (currentScreen == gameScreen::holeIntro)
        {
            DrawHoleIntro(assets, course);
        }
        else if (currentScreen == gameScreen::playing)
        {
            DrawGameplay(
                assets,
                course,
                swing,
                ball,
                camera,
                mousePos
            );
        }
        else if (currentScreen == gameScreen::scoring)
        {
            DrawScoring(course);
        }
        else if (currentScreen == gameScreen::options)
        {
            DrawOptions();
        }

        EndDrawing();
    }

    UnloadTexture(assets.golfer);
    UnloadTexture(assets.hole1);

    CloseWindow();

    return 0;
}
