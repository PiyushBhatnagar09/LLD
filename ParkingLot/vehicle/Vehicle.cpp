#include "Vehicle.hpp"

Vehicle::Vehicle(const std::string& licenseNumber, VehicleSize size)
    : licenseNumber(licenseNumber), size(size) {}

std::string Vehicle::getLicenseNumber() const {
    return licenseNumber;
}

VehicleSize Vehicle::getSize() const {
    return size;
}
