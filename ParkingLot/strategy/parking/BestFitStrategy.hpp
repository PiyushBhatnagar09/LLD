#ifndef BESTFITSTRATEGY_HPP
#define BESTFITSTRATEGY_HPP

#include "ParkingStrategy.hpp"

using namespace std;

class BestFitStrategy : public ParkingStrategy {
public:
    optional<ParkingSpot> findSpot(const vector<ParkingFloor>& floors,
                                   const Vehicle& vehicle) override;
};

#endif
