#include "Vehicle.hpp"
#include<iostream>

Vehicle::Vehicle(string licensePlate, VehicleType type, string color):licensePlate(licensePlate), type(type), color(color) {}

string Vehicle::getLicensePlate() const {
        return licensePlate;
}

VehicleType Vehicle::getType() const {
        return type;
}

string Vehicle::getColor() const {
        return color;
}

void Vehicle::displayInfo() const {
        cout<<"Vehicle: "<<color<<" ";
        switch (type)
        {
                case VehicleType::CAR: std::cout << "Car"; break;
                case VehicleType::MOTORCYCLE: std::cout << "Motorcycle"; break;
                case VehicleType::TRUCK: std::cout << "Truck"; break;
                case VehicleType::BUS: std::cout << "Bus"; break;
                default: break;
        }
        cout << " (License: " << licensePlate << ")" << endl;
}