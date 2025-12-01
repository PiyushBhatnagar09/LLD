#include "BestFitStrategy.hpp"

ParkingSpot* BestFitStrategy::findSpot(const vector<ParkingFloor>& floors,
                                                const Vehicle& vehicle)
{
    ParkingSpot* bestSpot = nullopt;

    for (const auto& floor : floors) {
        auto spotOnThisFloor = floor.findAvailableSpot(vehicle);

        if (spotOnThisFloor.has_value()) {
            if (!bestSpot.has_value() ||
                spotOnThisFloor->getSpotSize() < bestSpot->getSpotSize()) 
            {
                bestSpot = spotOnThisFloor;
            }
        }
    }
    return bestSpot;
}
