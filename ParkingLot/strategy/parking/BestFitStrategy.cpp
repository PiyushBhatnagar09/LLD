#include "BestFitStrategy.hpp"

ParkingSpot* BestFitStrategy::findSpot(const vector<ParkingFloor>& floors,
                                       Vehicle* vehicle)
{
    ParkingSpot* bestSpot = nullptr;

    for (const auto& floor : floors) {
        ParkingSpot* spotOnThisFloor = floor.findAvailableSpot(vehicle);

        if (spotOnThisFloor != nullptr) {
            if (bestSpot == nullptr ||
                spotOnThisFloor->getSpotSize() < bestSpot->getSpotSize())
            {
                bestSpot = spotOnThisFloor;
            }
        }
    }
    return bestSpot;
}