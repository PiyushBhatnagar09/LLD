#include "Bike.hpp"

Bike::Bike(const std::string& licenseNumber)
    : Vehicle(licenseNumber, VehicleSize::SMALL) {}
