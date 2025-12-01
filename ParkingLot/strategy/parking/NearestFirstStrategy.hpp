#ifndef NEARESTFIRSTSTRATEGY_HPP
#define NEARESTFIRSTSTRATEGY_HPP

#include "ParkingStrategy.hpp"

using namespace std;

class NearestFirstStrategy : public ParkingStrategy {
public:
    ParkingSpot* findSpot(const vector<ParkingFloor>& floors,
                                   const Vehicle& vehicle) override;
};

#endif
