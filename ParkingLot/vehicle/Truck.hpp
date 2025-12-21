#ifndef TRUCK_HPP
#define TRUCK_HPP

#include "Vehicle.hpp"

class Truck : public Vehicle {
public:
    //use explicit with single argument constructors to avoid implicit conversions like Truck t = "ABC123";
    explicit Truck(const string& licenseNumber);

    //this 'override' keyword is optional but good practice to indicate that this method overrides a base class method so that if the base class method signature changes, compiler will give an error
    void printInfo() const override;
};

#endif // TRUCK_HPP