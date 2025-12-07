#include "NearestFirstStrategy.hpp"

ParkingSpot* NearestFirstStrategy::findSpot(const vector<ParkingFloor>& floors,
                                            Vehicle* vehicle)
{
    for (const auto& floor : floors) {
        ParkingSpot* spot = floor.findAvailableSpot(vehicle);
        if (spot != nullptr) {
            return spot;
        }
    }
    return nullptr;
}