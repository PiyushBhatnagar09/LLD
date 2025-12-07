#ifndef FARTHESTFIRSTSTRATEGY_HPP
#define FARTHESTFIRSTSTRATEGY_HPP

#include "ParkingStrategy.hpp"

using namespace std;

class FarthestFirstStrategy : public ParkingStrategy {
public:
    ParkingSpot* findSpot(const vector<ParkingFloor>& floors, Vehicle* vehicle) override;
};

#endif