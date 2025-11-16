#ifndef TRUCK_HPP
#define TRUCK_HPP

#include "Vehicle.hpp"

class Truck : public Vehicle {
public:
    explicit Truck(const std::string& licenseNumber);
};

#endif // TRUCK_HPP
