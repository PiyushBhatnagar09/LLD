#include "Truck.hpp"

Truck::Truck(const std::string& licenseNumber)
    : Vehicle(licenseNumber, VehicleSize::LARGE) {}
