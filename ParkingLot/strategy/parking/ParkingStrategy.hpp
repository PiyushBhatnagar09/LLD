#ifndef PARKINGSTRATEGY_HPP
#define PARKINGSTRATEGY_HPP

#include <vector>
#include "ParkingFloor.hpp"
#include "ParkingSpot.hpp"
#include "Vehicle.hpp"

using namespace std;

class ParkingStrategy {
public:
    virtual ParkingSpot* findSpot(const vector<ParkingFloor>& floors,
                                           const Vehicle& vehicle) = 0;

    virtual ~ParkingStrategy() = default;
};

#endif
