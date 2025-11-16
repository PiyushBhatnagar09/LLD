#include "ParkingTicket.hpp"
#include <chrono>
#include <random>

static string generateUUID() {
    static const char* chars = "0123456789abcdef";
    string uuid = "";
    for (int i = 0; i < 32; i++) {
        uuid += chars[rand() % 16];
    }
    return uuid;
}

ParkingTicket::ParkingTicket(Vehicle* vehicle, ParkingSpot* spot)
    : vehicle(vehicle), spot(spot), exitTimestamp(0) {

    ticketId = generateUUID();

    entryTimestamp = chrono::duration_cast<chrono::milliseconds>(
            chrono::system_clock::now().time_since_epoch()
    ).count();
}

string ParkingTicket::getTicketId() const {
    return ticketId;
}

Vehicle* ParkingTicket::getVehicle() const {
    return vehicle;
}

ParkingSpot* ParkingTicket::getSpot() const {
    return spot;
}

long ParkingTicket::getEntryTimestamp() const {
    return entryTimestamp;
}

long ParkingTicket::getExitTimestamp() const {
    return exitTimestamp;
}

void ParkingTicket::setExitTimestamp() {
    exitTimestamp = chrono::duration_cast<chrono::milliseconds>(
            chrono::system_clock::now().time_since_epoch()
    ).count();
}
