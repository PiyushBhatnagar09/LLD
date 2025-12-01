#include "NearestFirstStrategy.hpp"

ParkingSpot* NearestFirstStrategy::findSpot(const vector<ParkingFloor>& floors,
                                                     const Vehicle& vehicle)
{
    for (const auto& floor : floors) {
        auto spot = floor.findAvailableSpot(vehicle);
        if (spot.has_value()) {
            return spot;
        }
    }
    return nullopt;
}
