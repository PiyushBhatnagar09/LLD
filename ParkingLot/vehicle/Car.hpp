#ifndef CAR_HPP
#define CAR_HPP

#include "Vehicle.hpp"

class Car : public Vehicle {
public:
    explicit Car(const std::string& licenseNumber);
    void printInfo() const override;
};

#endif // CAR_HPP