#include "GameUI.h"

void DrawMainMenu(Vector2 mousePos,
    Rectangle playButton,
    Rectangle optionsButton,
    Rectangle quitButton)
{
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

void DrawHoleIntro(const GameAssets& assets,
    const CourseData& course)
{
    ClearBackground(BLACK);

    if (course.holeNum == 1)
    {
        DrawTextureEx(
            assets.hole1, { 0, 0 }, 0.0f,
            course.mapScale, WHITE
        );

        DrawText("HOLE 1", 330, 200, 40, BLACK);
        DrawText("PAR 3", 330, 250, 30, BLACK);
        DrawText("YARDS: 166", 300, 300, 30, BLACK);
    }
}

void DrawGameplay(const GameAssets& assets,
    const CourseData& course,
    const SwingData& swing,
    const BallData& ball,
    const Camera2D& camera,
    Vector2 mousePos)
{
    if (course.holeNum == 1)
    {
        const int framesPerRow = 4;
        const int totalRows = 9;

        float frameWidth =
            (float)assets.golfer.width / framesPerRow;

        float frameHeight =
            (float)assets.golfer.height / totalRows;

        float scale = course.mapScale * 0.1378f;

        int column = swing.currentFrame % framesPerRow;
        int row = swing.currentFrame / framesPerRow;

        Rectangle sourceRect = {
            column * frameWidth,
            row * frameHeight,
            frameWidth,
            frameHeight
        };

        Vector2 golferPosition = {
            ball.position.x - 246.0f,
            ball.position.y + 9.0f
        };

        Rectangle destRect = {
            golferPosition.x,
            golferPosition.y,
            frameWidth * scale,
            frameHeight * scale
        };

        Vector2 origin = {
            (frameWidth * scale) / 2.0f,
            (frameHeight / 2.0f) * 2.0f
        };

        DrawText("GOLF GAME", 280, 400, 40, WHITE);
        DrawText("Press ESC for menu", 270, 460, 20, WHITE);

        // World drawing
        // Uncomment BeginMode2D and EndMode2D together
        // when you are ready to use your camera.
        // BeginMode2D(camera);

        DrawTextureEx(
            assets.hole1, { 0, 0 }, 0.0f,
            course.mapScale, WHITE
        );

        DrawTexturePro(
            assets.golfer,
            sourceRect,
            destRect,
            origin,
            90.0f,
            WHITE
        );

        DrawCircleV(ball.position, ball.size, WHITE);

        if (!ball.flying)
        {
            DrawLineV(
                ball.aimLineStart,
                ball.aimLineEnd,
                WHITE
            );
        }

        // EndMode2D();

        // Corner Map
        DrawTextureEx(
            assets.hole1, { 670, 50 }, 0, 0.115f, WHITE
        );

        DrawRectangleLinesEx(
            { 670, 50, 100, 230.92f }, 2, BLACK
        );

        DrawText("Hold M for Map", 650, 290, 18, BLACK);

        if (IsKeyDown(KEY_M))
        {
            ClearBackground(BLACK);
            DrawTextureEx(
                assets.hole1, { 200, 0 }, 0, 0.5f, WHITE
            );
        }
        else
        {
            // Swing Meter
            DrawRectangle(550, 670, 28, 120, WHITE);
            DrawRectangle(550, 704, 28, 27, GREEN);

            DrawRectangleV(
                swing.swingMeter,
                swing.swingDuration,
                RED
            );

            const char* hitText = "Idle";

            switch (swing.currentHit)
            {
            case hitType::Weak:  hitText = "Weak"; break;
            case hitType::Slice: hitText = "Slice"; break;
            case hitType::Hook:  hitText = "Hook"; break;
            case hitType::Pure:  hitText = "Pure"; break;
            case hitType::Idle:  hitText = "Idle"; break;
            }

            DrawText(
                TextFormat("%.2f", swing.holdTime),
                538, 585, 20, WHITE
            );

            DrawText(hitText, 538, 622, 20, WHITE);

            DrawText(
                TextFormat("Mouse X: %.0f | Mouse Y: %.0f",
                    mousePos.x, mousePos.y),
                400, 550, 20, WHITE
            );

            DrawText(
                TextFormat("Stroke: %d", course.strokeCounter),
                400, 530, 20, WHITE
            );

            DrawText(
                TextFormat("Is flying: %s",
                    ball.flying ? "true" : "false"),
                400, 510, 20, WHITE
            );
        }
    }

    // Course Details / Score HUD
    Rectangle score = { 10, 10, 180, 60 };

    DrawRectangleRec(score, WHITE);
    DrawRectangleLinesEx(score, 2, BLACK);

    DrawLineEx({ 52, 40 }, { 52, 70 }, 2, BLACK);
    DrawLineEx({ 100, 40 }, { 100, 70 }, 2, BLACK);
    DrawLineEx({ 10, 40 }, { 190, 40 }, 2, BLACK);

    DrawText(
        TextFormat("%d", course.holeNum),
        25, 42, 30, BLACK
    );

    DrawText(
        TextFormat("%d",
            course.holeDistances[course.holeNum - 1]),
        56, 44, 25, BLACK
    );

    DrawText("1 2 3 4", 106, 44, 25, BLACK);
    DrawText("SCORE: +5", 20, 14, 25, BLACK);
}

void DrawOptions()
{
    DrawText("OPTIONS", 290, 400, 40, WHITE);
    DrawText("Press ESC to return", 260, 460, 20, WHITE);
}

void DrawScoring(const CourseData& course)
{
    ClearBackground(BLACK);

    DrawText("HOLE COMPLETE", 220, 350, 40, WHITE);

    DrawText(
        TextFormat("STROKES: %d", course.strokeCounter),
        280, 420, 30, WHITE
    );
}
