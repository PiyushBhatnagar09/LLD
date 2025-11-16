#include "FlatRateFeeStrategy.hpp"

const double FlatRateFeeStrategy::RATE_PER_HOUR = 10.0;

double FlatRateFeeStrategy::calculateFee(ParkingTicket* parkingTicket) {
    long duration = parkingTicket->getExitTimestamp() - parkingTicket->getEntryTimestamp();
    long hours = (duration / (1000 * 60 * 60)) + 1;
    return hours * RATE_PER_HOUR;
}
