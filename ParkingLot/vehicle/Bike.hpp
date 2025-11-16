#ifndef BIKE_HPP
#define BIKE_HPP

#include "Vehicle.hpp"

class Bike : public Vehicle {
public:
    explicit Bike(const std::string& licenseNumber);
};

#endif // BIKE_HPP
