#include "VehicleBasedFeeStrategy.hpp"

const map<VehicleSize, double> VehicleBasedFeeStrategy::HOURLY_RATES = {
    { VehicleSize::SMALL, 10.0 },
    { VehicleSize::MEDIUM, 20.0 },
    { VehicleSize::LARGE, 30.0 }
};

double VehicleBasedFeeStrategy::calculateFee(ParkingTicket* parkingTicket) {
    long duration = parkingTicket->getExitTimestamp() - parkingTicket->getEntryTimestamp();
    long hours = (duration / (1000 * 60 * 60)) + 1;

    VehicleSize size = parkingTicket->getVehicle()->getSize();
    double rate = HOURLY_RATES.at(size);

    return hours * rate;
}