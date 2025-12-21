//if not defined
#ifndef VEHICLE_H
//then define
#define VEHICLE_H

#include <string>
#include "VehicleSize.hpp"

using namespace std;

class Vehicle {
protected:
    string licenseNumber;
    VehicleSize size;

public:
    Vehicle(const string& licenseNumber, VehicleSize size);

    //virtual destructor is needed so that derived class destructors are called properly 
    //once derived class objects are deleted through base class pointers
    virtual ~Vehicle() = default;  // Important for polymorphism

    string getLicenseNumber() const;
    
    VehicleSize getSize() const;

    virtual void printInfo() const = 0; // Pure virtual → keeps class abstract
};

#endif