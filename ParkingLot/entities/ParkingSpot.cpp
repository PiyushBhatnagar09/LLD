#include "ParkingSpot.hpp"

ParkingSpot::ParkingSpot(const string& spotId, VehicleSize spotSize)
    : spotId(spotId), spotSize(spotSize), occupied(false), parkedVehicle(nullptr) {}

string ParkingSpot::getSpotId() const {
    return spotId;
}

VehicleSize ParkingSpot::getSpotSize() const {
    return spotSize;
}

bool ParkingSpot::isAvailable() {
    return !occupied;
}

bool ParkingSpot::isOccupied() const {
    return occupied;
}

void ParkingSpot::parkVehicle(Vehicle* vehicle) {
    parkedVehicle = vehicle;
    occupied = true;
}

void ParkingSpot::unparkVehicle() {
    parkedVehicle = nullptr;
    occupied = false;
}

bool ParkingSpot::canFitVehicle(Vehicle* vehicle) {
    if (occupied) return false;

    VehicleSize vSize = vehicle->getSize();

    switch (vSize) {
        case VehicleSize::SMALL:
            return spotSize == VehicleSize::SMALL;

        case VehicleSize::MEDIUM:
            return spotSize == VehicleSize::MEDIUM ||
                   spotSize == VehicleSize::LARGE;

        case VehicleSize::LARGE:
            return spotSize == VehicleSize::LARGE;
    }

    return false;
}