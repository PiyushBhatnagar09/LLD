#ifndef FLAT_RATE_FEE_STRATEGY_HPP
#define FLAT_RATE_FEE_STRATEGY_HPP

#include "FeeStrategy.hpp"
using namespace std;

class FlatRateFeeStrategy : public FeeStrategy {
private:
    static const double RATE_PER_HOUR;

public:
    FlatRateFeeStrategy() = default;

    double calculateFee(ParkingTicket* parkingTicket) override;
};

#endif // FLAT_RATE_FEE_STRATEGY_HPP