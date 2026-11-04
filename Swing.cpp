#include "Swing.h"
#include "raymath.h"

void UpdateSwing(SwingData& swing, bool ballFlying,
    int& strokeCounter, float& flightTime,
    float deltaTime)
{
    const double minTime = 0.75;
    const double maxTime = 0.95;

    // Golf Swing Mechanics
    if (IsKeyDown(KEY_SPACE) &&
        swing.state == swingState::Idle &&
        !ballFlying)
    {
        swing.state = swingState::Backswing;
        swing.currentFrame = 0;
        swing.runningTime = 0.0f;
        swing.startTime = GetTime();
    }

    if (IsKeyReleased(KEY_SPACE) &&
        swing.state == swingState::Backswing)
    {
        swing.state = swingState::Downswing;
        swing.currentFrame = 20;
        swing.runningTime = 0.0f;
        swing.holdTime = GetTime() - swing.startTime;
        strokeCounter++;

        if (swing.holdTime > maxTime)
        {
            int outcome = GetRandomValue(1, 2);

            if (outcome == 1)
                swing.currentHit = hitType::Hook;
            else
                swing.currentHit = hitType::Slice;
        }
        else if (swing.holdTime < minTime)
        {
            swing.currentHit = hitType::Weak;
        }
        else
        {
            swing.currentHit = hitType::Pure;
        }

        flightTime = 0.0f;
    }

    // Golfer Sprite Animation
    if (swing.state == swingState::Backswing ||
        swing.state == swingState::Downswing)
    {
        swing.runningTime += deltaTime;

        if (swing.runningTime >= swing.updateTime)
        {
            swing.runningTime -= swing.updateTime;

            if (swing.state == swingState::Backswing)
            {
                if (swing.currentFrame < 19)
                    swing.currentFrame++;
            }
            else if (swing.state == swingState::Downswing)
            {
                if (swing.currentFrame < 34)
                    swing.currentFrame++;
                else
                {
                    swing.state = swingState::Idle;
                    swing.currentFrame = 0;
                }
            }
        }
    }

    // Swing Meter Stuff
    float growth = deltaTime * swing.rotationSpeed;

    if (swing.state == swingState::Backswing)
    {
        swing.swingMeter.y -= growth;
        swing.swingDuration.y += growth;
    }
    else if (!IsKeyPressed(KEY_SPACE))
    {
        swing.swingMeter.y += 3 * growth;
        swing.swingDuration.y -= 3 * growth;
    }

    swing.swingDuration.y =
        Clamp(swing.swingDuration.y, 0.0f, 120.0f);

    swing.swingMeter.y =
        Clamp(swing.swingMeter.y, 670.0f, 790.0f);
}
