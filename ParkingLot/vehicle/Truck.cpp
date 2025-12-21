#include "Truck.hpp"
#include <iostream>

Truck::Truck(const string& licenseNumber)
    : Vehicle(licenseNumber, VehicleSize::LARGE) {}

void Truck::printInfo() const {
    cout << "Truck: " << getLicenseNumber() << endl;
}