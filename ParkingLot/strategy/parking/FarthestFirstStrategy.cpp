#include "FarthestFirstStrategy.hpp"
#include <algorithm>

ParkingSpot* FarthestFirstStrategy::findSpot(const vector<ParkingFloor>& floors,
                                             Vehicle* vehicle)
{
    // Reverse-copy floors
    vector<ParkingFloor> reversedFloors = floors;
    reverse(reversedFloors.begin(), reversedFloors.end());

    for (const auto& floor : reversedFloors) {
        ParkingSpot* spot = floor.findAvailableSpot(vehicle);
        if (spot != nullptr) {
            return spot;
        }
    }
    return nullptr;
}