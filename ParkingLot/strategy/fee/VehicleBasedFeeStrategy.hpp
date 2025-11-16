#ifndef VEHICLE_BASED_FEE_STRATEGY_HPP
#define VEHICLE_BASED_FEE_STRATEGY_HPP

#include "FeeStrategy.hpp"
#include "VehicleSize.hpp"
#include <map>
using namespace std;

class VehicleBasedFeeStrategy : public FeeStrategy {
private:
    static const map<VehicleSize, double> HOURLY_RATES;

public:
    VehicleBasedFeeStrategy() = default;

    double calculateFee(ParkingTicket* parkingTicket) override;
};

#endif // VEHICLE_BASED_FEE_STRATEGY_HPP
