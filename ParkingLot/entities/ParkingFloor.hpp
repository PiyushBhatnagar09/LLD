#ifndef PARKING_FLOOR_HPP
#define PARKING_FLOOR_HPP

#include <string>
#include <map>
#include "ParkingSpot.hpp"
#include "../vehicle/Vehicle.hpp"
#include "../vehicle/VehicleSize.hpp"
using namespace std;

class ParkingFloor {
private:
    int floorNumber;
    map<string, ParkingSpot*> spots;

public:
    ParkingFloor(int floorNumber);

    void addSpot(ParkingSpot* spot);

    ParkingSpot* findAvailableSpot(Vehicle* vehicle) const;

    void displayAvailability() const;
};

#endif // PARKING_FLOOR_HPP