#ifndef PARKINGLOT_HPP
#define PARKINGLOT_HPP

#include <vector>
#include <map>
#include <string>
#include <memory>

#include "ParkingFloor.hpp"
#include "ParkingSpot.hpp"
#include "ParkingTicket.hpp"
#include "ParkingStrategy.hpp"
#include "FeeStrategy.hpp"
#include "FlatRateFeeStrategy.hpp"
#include "BestFitStrategy.hpp"

using namespace std;

class ParkingLot {
private:
    static ParkingLot* instance;

    vector<ParkingFloor> floors;
    map<string, ParkingTicket> activeTickets;

    unique_ptr<FeeStrategy> feeStrategy;
    unique_ptr<ParkingStrategy> parkingStrategy;

    ParkingLot();

public:
    static ParkingLot* getInstance();

    void addFloor(const ParkingFloor& floor);

    void setFeeStrategy(unique_ptr<FeeStrategy> strategy);
    void setParkingStrategy(unique_ptr<ParkingStrategy> strategy);

    ParkingTicket* parkVehicle(Vehicle* vehicle);
    double* unparkVehicle(const string& licenseNumber);
};

#endif
