#include "BallPhysics.h"
#include <cmath>

void UpdateAim(BallData& ball, float deltaTime)
{
    // Aim Line Mechanics
    if (!ball.flying)
    {
        if (IsKeyDown(KEY_D))
            ball.aimAngle += 90.0f * deltaTime;

        if (IsKeyDown(KEY_A))
            ball.aimAngle -= 90.0f * deltaTime;

        ball.aimLineStart = ball.position;
    }

    float radians = ball.aimAngle * DEG2RAD;

    ball.aimLineEnd.x =
        ball.aimLineStart.x +
        cosf(radians) * ball.aimLength;

    ball.aimLineEnd.y =
        ball.aimLineStart.y +
        sinf(radians) * ball.aimLength;
}

void UpdateBallPhysics(BallData& ball,
    const SwingData& swing,
    float deltaTime)
{
    // Ball Physics + Club Selection Stuff
    // Looking at 0.23 yards per pixel

    if (swing.state == swingState::Downswing &&
        swing.currentFrame == 28 &&
        !ball.flying)
    {
        ball.flying = true;
        ball.flightTime = 0.0f;

        float radians = ball.aimAngle * DEG2RAD;

        ball.direction.x = cosf(radians);
        ball.direction.y = sinf(radians);
    }

    if (ball.flying)
    {
        ball.flightTime += deltaTime;

        if (ball.flightTime >= 8.0f)
            ball.flying = false;
    }

    if (ball.flying && ball.flightTime < 8.0f)
    {
        float strength = 0.0f;

        if (swing.currentHit == hitType::Weak)
            strength = 0.7f;
        else if (swing.currentHit == hitType::Pure)
            strength = 1.0f;
        else if (swing.currentHit == hitType::Slice)
            strength = 0.89f;
        else if (swing.currentHit == hitType::Hook)
            strength = 0.89f;

        ball.position.x +=
            ball.direction.x * strength * deltaTime;

        ball.position.y +=
            ball.direction.y * strength * deltaTime;

        // Distance per frame = speed x frametime.
    }
}
