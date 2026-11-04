#include "GolfClubs.h"

GolfClub::GolfClub(float speed, float carry) {
    ballSpeed = speed;
    carryYards = carry;
}

float GolfClub::getBallSpeed() const {
    return ballSpeed;
}

float GolfClub::getCarryYards() const {
    return carryYards;
}

// Golf Club Definitions
GolfClub driver(135.0f, 215.0f);
GolfClub threeWood(125.0f, 195.0f);
GolfClub fiveWood(118.0f, 180.0f);
GolfClub threeHybrid(112.0f, 170.0f);
GolfClub fourIron(108.0f, 160.0f);
GolfClub fiveIron(103.0f, 150.0f);
GolfClub sixIron(98.0f, 140.0f);
GolfClub sevenIron(93.0f, 130.0f);
GolfClub eightIron(87.0f, 120.0f);
GolfClub nineIron(81.0f, 110.0f);
GolfClub pitchingWedge(75.0f, 100.0f);
GolfClub gapWedge(68.0f, 85.0f);
GolfClub sandWedge(60.0f, 70.0f);
GolfClub lobWedge(52.0f, 55.0f);
