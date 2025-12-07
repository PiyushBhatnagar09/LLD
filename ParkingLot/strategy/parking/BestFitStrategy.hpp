#ifndef BESTFITSTRATEGY_HPP
#define BESTFITSTRATEGY_HPP

#include "ParkingStrategy.hpp"
#include <vector>
#include <string>

using namespace std;

class BestFitStrategy : public ParkingStrategy {
public:
    ParkingSpot* findSpot(const std::vector<ParkingFloor>& floors, Vehicle* vehicle) override;
};

#endif