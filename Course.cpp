#include "Course.h"

bool CheckHoleComplete(const CourseData& course,
    const BallData& ball)
{
    if (course.holeNum == 1)
    {
        return CheckCollisionCircles(
            ball.position,
            ball.size,
            course.hole1Pin,
            5.0f
        );
    }

    return false;
}
