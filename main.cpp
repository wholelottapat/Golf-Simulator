#include "raylib.h"
#include <raymath.h>
#include <math.h>

const int screenWidth = 800;
const int screenHeight = 1004;

const double minTime = .75;
const double maxTime = .95;

float rotationSpeed = 90.0f;

enum class swingState {
    Idle, Backswing, Downswing
};

enum class hitType {
    Weak, Slice, Hook, Pure, Idle
};

enum class gameScreen {
    mainMenu, playing, options
};

Color road = { 23, 28, 24 };
Color rough = { 25, 133, 48 };
Color fairway = { 38, 189, 70 };
Color green = { 27, 224, 69 };
Color fringe = { 29, 153, 55 };

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//

int main()
{
    InitWindow(screenWidth, screenHeight, "Golf Simulator - OpenGL 2.1");
    SetExitKey(KEY_NULL);

    gameScreen currentScreen = gameScreen::mainMenu;
    Rectangle playButton = { 300, 350, 200, 60 };
    Rectangle optionsButton = { 300, 430, 200, 60 };
    Rectangle quitButton = { 300, 510, 200, 60 };


    // Golf Animation
    Texture2D golfer = LoadTexture("resources/spritesheetGolfer.png");

    const int framesPerRow = 4;
    const int totalRows = 9;
    const int totalFrames = 35;

    int currentFrame = 0;

    float runningTime = 0.0f;
    float updateTime = 1.0f / 24.0f;

    float frameWidth = (float)golfer.width / framesPerRow;
    float frameHeight = (float)golfer.height / totalRows;

    swingState swingState = swingState::Idle;

    double startTime = 0.0;
    double holdTime = 0.0;

    Vector2 swingMeter = {
        (.6875 * screenWidth), 
        (.916 * screenHeight) 
    };

    Vector2 swingDuration = { 28, 0 }; //SWING METER//

    //Ball Position
    Vector2 ballPosition = {
        screenWidth / 2,
        .850*screenHeight
    };
    // Ball Size
    float ballSize = 2.0;

    float tf = 0;
    bool ballFlying = false;

    //Golfer Position
    Vector2 golferPosition = { ballPosition.x - 234, ballPosition.y + 19 };

    hitType currentHit = hitType::Idle;

    

    //Course
    Texture2D hole1 = LoadTexture("resources/pixel_art_large.png");
    Texture2D flag = LoadTexture("resources/golfFlag.png");

    Camera2D camera = { 0 };
    camera.target = { 400, 850 };
    camera.offset = { 400, 850 };
    camera.rotation = 0.0f;
    camera.zoom = 3.0f;
    
    int strokeCounter = 1;

    SetTargetFPS(60);
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
    while (!WindowShouldClose())
    {
        Vector2 mousePos = GetMousePosition();
        if (currentScreen == gameScreen::mainMenu) {
            if (CheckCollisionPointRec(mousePos, playButton) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                currentScreen = gameScreen::playing;
            }

            if (CheckCollisionPointRec(mousePos, optionsButton) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                currentScreen = gameScreen::options;
            }

            if (CheckCollisionPointRec(mousePos, quitButton) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                break;
            }
        }

        if (IsKeyPressed(KEY_ESCAPE) && currentScreen != gameScreen::mainMenu) {
            currentScreen = gameScreen::mainMenu;
        }


        // Golfer Animation
        float scale = .25f;

        Rectangle sourceRect = {
            0.0f,
            0.0f,
            frameWidth,
            frameHeight
        };

        Rectangle destRect = {
            (float)golferPosition.x, (float)golferPosition.y,
            frameWidth * scale,
            frameHeight * scale
        };

        Vector2 origin = {
            (frameWidth * scale) / 2.0f,
            (frameHeight / 2) * 2.0f
        };

        int column = currentFrame % framesPerRow;
        int row = currentFrame / framesPerRow;

        sourceRect.x = (float)column * frameWidth;
        sourceRect.y = (float)row * frameHeight;


        //Golf Swing Mechanics
        float GFT = GetFrameTime();

        if (IsKeyDown(KEY_SPACE) &&
            swingState == swingState::Idle &&
            !ballFlying)
        {
            swingState = swingState::Backswing;

            currentFrame = 0;
            runningTime = 0.0f;
            startTime = GetTime();
        }

        if (IsKeyReleased(KEY_SPACE) &&
            swingState == swingState::Backswing)
        {
            swingState = swingState::Downswing;

            currentFrame = 20;
            runningTime = 0.0f;
            holdTime = GetTime() - startTime;
            strokeCounter++;

            if (holdTime > maxTime)
            {
                int outcome = GetRandomValue(1, 2);

                if (outcome == 1)
                {
                    currentHit = hitType::Hook;
                }
                else
                {
                    currentHit = hitType::Slice;
                }
            }
            else if (holdTime < minTime)
            {
                currentHit = hitType::Weak;
            }
            else
            {
                currentHit = hitType::Pure;
            }

            tf = 0.0f;
        }


        if (swingState == swingState::Backswing ||
            swingState == swingState::Downswing)
        {
            runningTime += GFT;

            if (runningTime >= updateTime)
            {
                runningTime -= updateTime;

                if (swingState == swingState::Backswing)
                {
                    if (currentFrame < 19)
                    {
                        currentFrame++;
                    }
                }
                else if (swingState == swingState::Downswing)
                {
                    if (currentFrame < 34)
                    {
                        currentFrame++;
                    }
                    else
                    {
                        swingState = swingState::Idle;
                        currentFrame = 0;

                    }
                }
            }
        }
        
        

        // Swing Meter Stuff
        float growth = GFT * rotationSpeed;

        if (swingState == swingState::Backswing)
        {
            swingMeter.y -= growth;
            swingDuration.y += growth;
        }
        else if (!IsKeyPressed(KEY_SPACE))
        {
            swingMeter.y += 3 * growth;
            swingDuration.y -= 3 * growth;
        }

        swingDuration.y = Clamp(swingDuration.y, 0.0f, 120.0f);
        swingMeter.y = Clamp(swingMeter.y, 670.0f, 790.0f);

        // Ball Physics
        if (swingState == swingState::Downswing &&
            currentFrame == 28 &&
            !ballFlying) {
            ballFlying = true;
            tf = 0.0f;
        }
        if (ballFlying == true) {
            tf += GFT;

            if (tf >= 6.0f) {
                ballFlying = false;
            }
        }
        if (ballFlying == true && tf < 6) {
            if (currentHit == hitType::Weak) {
                ballPosition.y -= 50.0f * GFT;
            }
            else if (currentHit == hitType::Slice) {
                ballPosition.y -= 70.0f * GFT;
                ballPosition.x += 35.0f * GFT;
            }
            else if (currentHit == hitType::Hook) {
                ballPosition.y -= 70.0f * GFT;
                ballPosition.x -= 35.0f * GFT;
            }
            else {
                ballPosition.y -= 78.0f * GFT;
            }
        }
        if (ballFlying == true) {
            camera.target = ballPosition;
        }

        float mapX = 200.0f;
        float mapY = 0.0f;
        float mapWidth = hole1.width * 0.5f;
        float mapHeight = hole1.height * 0.5f;

        float leftLimit = mapX + camera.offset.x / camera.zoom;
        float rightLimit = mapX + mapWidth -
            (screenWidth - camera.offset.x) / camera.zoom;

        float topLimit = mapY + camera.offset.y / camera.zoom;
        float bottomLimit = mapY + mapHeight -
            (screenHeight - camera.offset.y) / camera.zoom;

        camera.target.x = Clamp(camera.target.x, leftLimit, rightLimit);
        camera.target.y = Clamp(camera.target.y, topLimit, bottomLimit);


        const char* hitText = "Idle";

        switch (currentHit)
        {
        case hitType::Weak:
            hitText = "Weak";
            break;

        case hitType::Slice:
            hitText = "Slice";
            break;

        case hitType::Hook:
            hitText = "Hook";
            break;

        case hitType::Pure:
            hitText = "Pure";
            break;

        case hitType::Idle:
            hitText = "Idle";
            break;
        }
        if (ballFlying == false) {
            golferPosition = { ballPosition.x - 246, ballPosition.y + 9 };
        }
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//

        BeginDrawing();
        ClearBackground(DARKGREEN);

        if (currentScreen == gameScreen::mainMenu) {
            DrawText("GOLF SIMULATOR", 190, 200, 45, WHITE);

            DrawRectangleRec(
                playButton,
                CheckCollisionPointRec(mousePos, playButton) ? LIME : GREEN
            );

            DrawRectangleRec(
                optionsButton,
                CheckCollisionPointRec(mousePos, optionsButton) ? LIME : GREEN
            );

            DrawRectangleRec(
                quitButton,
                CheckCollisionPointRec(mousePos, quitButton) ? LIME : GREEN
            );

            DrawText("PLAY", 365, 365, 30, WHITE);
            DrawText("OPTIONS", 330, 445, 30, WHITE);
            DrawText("QUIT", 365, 525, 30, WHITE);
        }
        else if (currentScreen == gameScreen::playing) {

            DrawText("GOLF GAME", 280, 400, 40, WHITE);
            DrawText("Press ESC for menu", 270, 460, 20, WHITE);
            //Background + Course
            BeginMode2D(camera);

            DrawTextureEx(
                hole1,
                { 200, 0 },
                0.0f,
                0.5f,
                WHITE);
            DrawTextureEx(
                flag,
                { 400, 100 },
                0.0f,
                .25f,
                WHITE
            );
            // Golfer
            DrawTexturePro(
                golfer,
                sourceRect,
                destRect,
                origin,
                90.0f,
                WHITE);

            // Golf Ball
            DrawCircleV(ballPosition, ballSize, WHITE);

            EndMode2D();

            //Corner Map
            DrawTextureEx(hole1, { 670, 50 }, 0, .115f, WHITE);
            DrawRectangleLinesEx({ 670, 50, 100, 230.92 }, 2, BLACK);
            DrawText("Hold M for Map", 650, 290, 18, BLACK);

            if (IsKeyDown(KEY_M)) {
                ClearBackground(BLACK);
                DrawTextureEx(hole1, { 200, 0 }, 0, .5f, WHITE);
            }
            else {
                // Swing Meter
                Rectangle whiteMeter = { 550, 670 };
                DrawRectangle(
                    whiteMeter.x, whiteMeter.y,
                    28,
                    120,
                    WHITE
                );
                DrawRectangle(
                    whiteMeter.x, whiteMeter.y + 34.5,
                    28,
                    27,
                    GREEN);
                DrawRectangleV(
                    swingMeter,
                    swingDuration,
                    RED);


                //Text With Time Callouts & Mouse Position
                DrawText(TextFormat("%.2f", holdTime), 0.6725 * screenWidth, .583 * screenHeight, 20, WHITE);
                DrawText(hitText, .6725 * screenWidth, .62 * screenHeight, 20, WHITE);
                DrawText(TextFormat("Mouse X: %.0f | Mouse Y: %.0f", mousePos.x, mousePos.y), 400, 550, 20, WHITE);
                DrawText(TextFormat("Stroke: %d", strokeCounter), 400, 530, 20, WHITE);
                DrawText(TextFormat("Is flying: %s", ballFlying ? "true" : "false"), 400, 510, 20, WHITE);
            }



            //Course Details
            Rectangle score =
            { 10, 10, 180, 60 };
            DrawRectangle(
                10,
                10,
                180,
                60,
                WHITE
            );
            DrawRectangleLinesEx(
                score,
                2,
                BLACK
            );
            DrawLineEx(
                { 52, 40 },
                { 52, 70 },
                2,
                BLACK
            );
            DrawLineEx(
                { 100, 40 },
                { 100, 70 },
                2,
                BLACK
            );
            DrawLineEx(
                { 10, 40 },
                { 190, 40 },
                2,
                BLACK
            );
            DrawText(       //ADD CODE TO KNOW WHICH HOLE YOU ARE ON//
                "1",
                25, 42,
                30,
                BLACK
            );
            DrawText(
                "135",      //ADD CODE TO KNOW YARDS TO PIN//
                56, 44,
                25,
                BLACK
            );
            DrawText(
                "1 2 3 4",      //ADD CODE TO KNOW WHAT STROKE YOU ARE ON//
                106, 44,
                25,
                BLACK
            );
            DrawText(
                "SCORE: +5",      //ADD CODE TO KNOW SCORE//
                20, 14,
                25,
                BLACK
            );

        }
        else if (currentScreen == gameScreen::options) {

            DrawText("OPTIONS", 290, 400, 40, WHITE);
            DrawText("Press ESC to return", 260, 460, 20, WHITE);
        }

       
        EndDrawing();
    }


    UnloadTexture(golfer);
    UnloadTexture(hole1);

    CloseWindow();

    return 0;
}

