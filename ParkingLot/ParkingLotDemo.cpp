#include <iostream>
#include <memory>

#include "ParkingLot.hpp"
#include "entities/ParkingFloor.hpp"
#include "entities/ParkingSpot.hpp"
#include "entities/ParkingTicket.hpp"
#include "strategy/fee/VehicleBasedFeeStrategy.hpp"
#include "vehicle/Bike.hpp"
#include "vehicle/Car.hpp"
#include "vehicle/Truck.hpp"

using namespace std;

int main() {
    ParkingLot* parkingLot = ParkingLot::getInstance();

    cout<<"here1"<<endl;

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

    Bike* bike = new Bike("B-123");
    Car* car = new Car("C-456");
    Truck* truck = new Truck("T-789");

    ParkingTicket* bikeTicket = parkingLot->parkVehicle(bike);
    ParkingTicket* carTicket  = parkingLot->parkVehicle(car);
    ParkingTicket* truckTicket = parkingLot->parkVehicle(truck);

    cout << "\n--- Availability after parking ---\n";
    floor1.displayAvailability();
    floor2.displayAvailability();

    Car* car2 = new Car("C-999");
    ParkingTicket* car2Ticket = parkingLot->parkVehicle(car2);

    Bike* bike2 = new Bike("B-000");
    ParkingTicket* failedBikeTicket = parkingLot->parkVehicle(bike2);

    cout << "\n--- Vehicle Exits ---\n";

    if (carTicket != nullptr) {
    double* fee = parkingLot->unparkVehicle(car->getLicenseNumber());
        if (fee != nullptr) {
            cout << "Car C-456 unparked. Fee: $" << *fee << endl;
            delete fee;
        }
    }

    cout << "\n--- Availability after one car leaves ---\n";
    floor1.displayAvailability();
    floor2.displayAvailability();

    delete bike;
    delete car;
    delete truck;
    delete car2;
    delete bike2;
    return 0;
}