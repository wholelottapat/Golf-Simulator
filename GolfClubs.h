#pragma once

class GolfClub {
private:
    float ballSpeed;
    float carryYards;

public:
    GolfClub(float speed, float carry) {
        ballSpeed = speed;
        carryYards = carry;
    }

    float getBallSpeed() const {
        return ballSpeed;
    }

    float getCarryYards() const {
        return carryYards;
    }
};

extern GolfClub driver;
extern GolfClub threeWood;
extern GolfClub fiveWood;
extern GolfClub threeHybrid;
extern GolfClub fourIron;
extern GolfClub fiveIron;
extern GolfClub sixIron;
extern GolfClub sevenIron;
extern GolfClub eightIron;
extern GolfClub nineIron;
extern GolfClub pitchingWedge;
extern GolfClub gapWedge;
extern GolfClub sandWedge;
extern GolfClub lobWedge;