//if not defined
#ifndef VEHICLE_H
//then define
#define VEHICLE_H

#include <string>
#include "VehicleSize.hpp"

class Vehicle {
protected:
    std::string licenseNumber;
    VehicleSize size;

public:
    Vehicle(const std::string& licenseNumber, VehicleSize size);

    virtual ~Vehicle() = default;  // Important for polymorphism

    std::string getLicenseNumber() const;
    VehicleSize getSize() const;

    virtual void printInfo() const = 0; // Pure virtual → keeps class abstract
};

#endif
