#include "FarthestFirstStrategy.hpp"
#include <algorithm>

optional<ParkingSpot> FarthestFirstStrategy::findSpot(const vector<ParkingFloor>& floors,
                                                      const Vehicle& vehicle)
{
    // Reverse-copy floors
    vector<ParkingFloor> reversedFloors = floors;
    reverse(reversedFloors.begin(), reversedFloors.end());

    for (const auto& floor : reversedFloors) {
        auto spot = floor.findAvailableSpot(vehicle);
        if (spot.has_value()) {
            return spot;
        }
    }
    return nullopt;
}
