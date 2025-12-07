#ifndef PARKINGLOT_HPP
#define PARKINGLOT_HPP

#include <vector>
#include <map>
#include <string>
#include <memory>

#include "entities/ParkingFloor.hpp"
#include "entities/ParkingSpot.hpp"
#include "entities/ParkingTicket.hpp"
#include "strategy/parking/ParkingStrategy.hpp"
#include "strategy/fee/FeeStrategy.hpp"
#include "strategy/fee/FlatRateFeeStrategy.hpp"
#include "strategy/parking/BestFitStrategy.hpp"

using namespace std;

class ParkingLot {
private:
    static ParkingLot* instance;

    vector<ParkingFloor> floors;
    map<string, ParkingTicket*> activeTickets; // store pointers

    unique_ptr<FeeStrategy> feeStrategy;
    unique_ptr<ParkingStrategy> parkingStrategy;

    ParkingLot();

public:
    static ParkingLot* getInstance();

    void addFloor(const ParkingFloor& floor);

    void setFeeStrategy(unique_ptr<FeeStrategy> strategy);
    void setParkingStrategy(unique_ptr<ParkingStrategy> strategy);

    ParkingTicket* parkVehicle(Vehicle* vehicle);
    double* unparkVehicle(const string& licenseNumber); // corrected return type

    ~ParkingLot(); // destructor to clean up tickets
};

#endif