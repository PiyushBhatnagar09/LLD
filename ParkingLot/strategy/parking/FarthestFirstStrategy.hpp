#ifndef FARTHESTFIRSTSTRATEGY_HPP
#define FARTHESTFIRSTSTRATEGY_HPP

#include "ParkingStrategy.hpp"

using namespace std;

class FarthestFirstStrategy : public ParkingStrategy {
public:
    optional<ParkingSpot> findSpot(const vector<ParkingFloor>& floors,
                                   const Vehicle& vehicle) override;
};

#endif
