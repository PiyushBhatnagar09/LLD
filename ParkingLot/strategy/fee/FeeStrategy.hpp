#ifndef FEESTRATEGY_HPP
#define FEESTRATEGY_HPP

#include "../../entities/ParkingTicket.hpp"
using namespace std;

class FeeStrategy {
public:
    virtual ~FeeStrategy() = default;
    virtual double calculateFee(ParkingTicket* parkingTicket) = 0;
};

#endif // FEESTRATEGY_HPP