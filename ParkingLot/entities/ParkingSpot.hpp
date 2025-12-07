#ifndef PARKING_SPOT_HPP
#define PARKING_SPOT_HPP

#include <string>
#include "../vehicle/Vehicle.hpp"
#include "../vehicle/VehicleSize.hpp"
using namespace std;

class ParkingSpot {
private:
    string spotId;
    bool occupied;
    Vehicle* parkedVehicle;
    VehicleSize spotSize;

public:
    ParkingSpot(const string& spotId, VehicleSize spotSize);

    string getSpotId() const;
    VehicleSize getSpotSize() const;

    bool isAvailable();
    bool isOccupied() const;

    void parkVehicle(Vehicle* vehicle);
    void unparkVehicle();

    bool canFitVehicle(Vehicle* vehicle);
};

#endif // PARKING_SPOT_HPP