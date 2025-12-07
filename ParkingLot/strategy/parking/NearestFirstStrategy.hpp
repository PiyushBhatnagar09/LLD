#ifndef NEARESTFIRSTSTRATEGY_HPP
#define NEARESTFIRSTSTRATEGY_HPP

#include "ParkingStrategy.hpp"
#include <vector>
#include <string>

using namespace std;

class NearestFirstStrategy : public ParkingStrategy {
public:
    ParkingSpot* findSpot(const vector<ParkingFloor>& floors,
                                              Vehicle* vehicle) override;
};

#endif