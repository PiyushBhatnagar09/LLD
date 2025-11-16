#include "Car.hpp"

Car::Car(const std::string& licenseNumber)
    : Vehicle(licenseNumber, VehicleSize::MEDIUM) {}
