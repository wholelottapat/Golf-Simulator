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

GolfClub driver(135, 215);
GolfClub threeWood(125, 195);
GolfClub fiveWood(118, 180);
GolfClub threeHybrid(112, 170);
GolfClub fourIron(108, 160);
GolfClub fiveIron(103, 150);
GolfClub sixIron(98, 140);
GolfClub sevenIron(93, 130);
GolfClub eightIron(87, 120);
GolfClub nineIron(81, 110);
GolfClub pitchingWedge(75, 100);
GolfClub gapWedge(68, 85);
GolfClub sandWedge(60, 70);
GolfClub lobWedge(52, 55);
