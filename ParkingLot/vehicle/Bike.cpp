#include "Bike.hpp"
#include <iostream>

Bike::Bike(const std::string& licenseNumber)
    : Vehicle(licenseNumber, VehicleSize::SMALL) {}

void Bike::printInfo() const {
    std::cout << "Bike: " << getLicenseNumber() << std::endl;
}