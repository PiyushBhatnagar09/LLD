#ifndef PARKING_FLOOR_HPP
#define PARKING_FLOOR_HPP

#include <string>
#include <map>
#include "ParkingSpot.hpp"
#include "Vehicle.hpp"
#include "VehicleSize.hpp"
using namespace std;

class ParkingFloor {
private:
    int floorNumber;
    map<string, ParkingSpot*> spots;

public:
    ParkingFloor(int floorNumber);

    void addSpot(ParkingSpot* spot);

    ParkingSpot* findAvailableSpot(Vehicle* vehicle);

    void displayAvailability();
};

#endif // PARKING_FLOOR_HPP
