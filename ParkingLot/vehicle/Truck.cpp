#include "Truck.hpp"
#include <iostream>

Truck::Truck(const std::string& licenseNumber)
    : Vehicle(licenseNumber, VehicleSize::LARGE) {}

void Truck::printInfo() const {
    std::cout << "Truck: " << getLicenseNumber() << std::endl;
}