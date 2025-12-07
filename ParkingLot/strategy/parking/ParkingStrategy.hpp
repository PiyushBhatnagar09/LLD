#ifndef PARKINGSTRATEGY_HPP
#define PARKINGSTRATEGY_HPP

#include <vector>
#include "../../entities/ParkingFloor.hpp"
#include "../../entities/ParkingSpot.hpp"
#include "../../vehicle/Vehicle.hpp"

using namespace std;

class ParkingStrategy {
public:
    virtual ParkingSpot* findSpot(const vector<ParkingFloor>& floors,
                                             Vehicle* vehicle) = 0;

    virtual ~ParkingStrategy() = default;
};

#endif