#include "ParkingFloor.hpp"
#include <iostream>

ParkingFloor::ParkingFloor(int floorNumber)
    : floorNumber(floorNumber) {}

void ParkingFloor::addSpot(ParkingSpot* spot) {
    spots[spot->getSpotId()] = spot;
}

ParkingSpot* ParkingFloor::findAvailableSpot(Vehicle* vehicle) const {
    ParkingSpot* best = nullptr;

    for (const auto& entry : spots) {
        ParkingSpot* spot = entry.second;

        if (!spot->isOccupied() && spot->canFitVehicle(vehicle)) {
            if (best == nullptr ||
                spot->getSpotSize() < best->getSpotSize()) {
                best = spot;
            }
        }
    }

    return best;  // nullptr means no spot available
}

void ParkingFloor::displayAvailability() const {
    cout << "--- Floor " << floorNumber << " Availability ---" << endl;

    map<VehicleSize, int> availableCounts = {
        {VehicleSize::SMALL, 0},
        {VehicleSize::MEDIUM, 0},
        {VehicleSize::LARGE, 0}
    };

    for (const auto& entry : spots) {
        ParkingSpot* spot = entry.second;
        if (!spot->isOccupied()) {
            availableCounts[spot->getSpotSize()]++;
        }
    }

    cout << "  SMALL spots: " << availableCounts[VehicleSize::SMALL] << endl;
    cout << "  MEDIUM spots: " << availableCounts[VehicleSize::MEDIUM] << endl;
    cout << "  LARGE spots: " << availableCounts[VehicleSize::LARGE] << endl;
}