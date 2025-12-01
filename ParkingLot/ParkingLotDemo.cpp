#include <iostream>

#include "ParkingLot.hpp"
#include "ParkingFloor.hpp"
#include "ParkingSpot.hpp"
#include "ParkingTicket.hpp"
#include "VehicleBasedFeeStrategy.hpp"
#include "Bike.hpp"
#include "Car.hpp"
#include "Truck.hpp"

using namespace std;

int main() {
    ParkingLot* parkingLot = ParkingLot::getInstance();

    ParkingFloor floor1(1);
    floor1.addSpot(new ParkingSpot("F1-S1", VehicleSize::SMALL));
    floor1.addSpot(new ParkingSpot("F1-M1", VehicleSize::MEDIUM));
    floor1.addSpot(new ParkingSpot("F1-L1", VehicleSize::LARGE));

    ParkingFloor floor2(2);
    floor2.addSpot(new ParkingSpot("F2-M1", VehicleSize::MEDIUM));
    floor2.addSpot(new ParkingSpot("F2-M2", VehicleSize::MEDIUM));

    parkingLot->addFloor(floor1);
    parkingLot->addFloor(floor2);

    parkingLot->setFeeStrategy(make_unique<VehicleBasedFeeStrategy>());

    cout << "\n--- Vehicle Entries ---\n";
    floor1.displayAvailability();
    floor2.displayAvailability();

    Bike bike("B-123");
    Car car("C-456");
    Truck truck("T-789");

    ParkingTicket* bikeTicket = parkingLot->parkVehicle(bike);
    ParkingTicket* carTicket  = parkingLot->parkVehicle(car);
    ParkingTicket* truckTicket = parkingLot->parkVehicle(truck);

    cout << "\n--- Availability after parking ---\n";
    floor1.displayAvailability();
    floor2.displayAvailability();

    Car car2("C-999");
    ParkingTicket* car2Ticket = parkingLot->parkVehicle(car2);

    Bike bike2("B-000");
    ParkingTicket* failedBikeTicket = parkingLot->parkVehicle(bike2);

    cout << "\n--- Vehicle Exits ---\n";

    if (carTicket != nullptr) {
        double* fee = parkingLot->unparkVehicle(car.getLicenseNumber());
        if (fee != nullptr) {
            cout << "Car C-456 unparked. Fee: $" << *fee << endl;
            delete fee;
        }
    }

    cout << "\n--- Availability after one car leaves ---\n";
    floor1.displayAvailability();
    floor2.displayAvailability();

    return 0;
}
