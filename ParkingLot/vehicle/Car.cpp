#include "Car.hpp"
#include <iostream>

Car::Car(const std::string& licenseNumber)
    : Vehicle(licenseNumber, VehicleSize::MEDIUM) {}

void Car::printInfo() const {
    std::cout << "Car: " << getLicenseNumber() << std::endl;
}