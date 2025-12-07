#include "ParkingLot.hpp"
#include <iostream>

using namespace std;

ParkingLot* ParkingLot::instance = nullptr;

ParkingLot::ParkingLot() {
    feeStrategy = make_unique<FlatRateFeeStrategy>();
    parkingStrategy = make_unique<BestFitStrategy>();
}

ParkingLot* ParkingLot::getInstance() {
    if (instance == nullptr) {
        instance = new ParkingLot();
    }
    return instance;
}

void ParkingLot::addFloor(const ParkingFloor& floor) {
    floors.push_back(floor);
}

void ParkingLot::setFeeStrategy(unique_ptr<FeeStrategy> strategy) {
    feeStrategy = std::move(strategy);
}

void ParkingLot::setParkingStrategy(unique_ptr<ParkingStrategy> strategy) {
    parkingStrategy = std::move(strategy);
}

ParkingTicket* ParkingLot::parkVehicle(Vehicle* vehicle) {
    ParkingSpot* spot = parkingStrategy->findSpot(floors, vehicle);

    if (spot != nullptr) {
        spot->parkVehicle(vehicle);

        ParkingTicket* ticket = new ParkingTicket(vehicle, spot);
        activeTickets[vehicle->getLicenseNumber()] = ticket;

        cout << vehicle->getLicenseNumber()
             << " parked at " << spot->getSpotId()
             << ". Ticket: " << ticket->getTicketId() << endl;

        return ticket;
    }

    cout << "No available spot for " << vehicle->getLicenseNumber() << endl;
    return nullptr;
}

double* ParkingLot::unparkVehicle(const string& licenseNumber) {
    auto it = activeTickets.find(licenseNumber);

    if (it == activeTickets.end()) {
        cout << "Ticket not found\n";
        return nullptr;
    }

    ParkingTicket* ticket = it->second;
    ParkingSpot* spot = ticket->getSpot();

    ticket->setExitTimestamp();
    spot->unparkVehicle();

    double fee = feeStrategy->calculateFee(ticket);

    delete ticket;
    activeTickets.erase(it);

    double* result = new double(fee);  // caller must delete!
    return result;
}

ParkingLot::~ParkingLot() {
    for (auto& entry : activeTickets) {
        delete entry.second;
    }
}