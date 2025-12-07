#ifndef PARKING_TICKET_HPP
#define PARKING_TICKET_HPP

#include <string>
#include <ctime>
#include "../vehicle/Vehicle.hpp"
#include "ParkingSpot.hpp"
using namespace std;

class ParkingTicket {
private:
    string ticketId;
    Vehicle* vehicle;
    ParkingSpot* spot;
    long entryTimestamp;
    long exitTimestamp;

public:
    ParkingTicket(Vehicle* vehicle, ParkingSpot* spot);

    string getTicketId() const;
    Vehicle* getVehicle() const;
    ParkingSpot* getSpot() const;
    long getEntryTimestamp() const;
    long getExitTimestamp() const;

    void setExitTimestamp();
};

#endif // PARKING_TICKET_HPP