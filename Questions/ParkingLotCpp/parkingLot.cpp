#include <iostream>
#include <vector>
#include <unordered_map>
#include <memory>
#include <string>
#include <stdexcept>
#include <ctime>
#include <cstdlib>
#include <mutex>
#include <thread>

using namespace std;

// Forward declarations
class Vehicle;
class ParkingSpot;
class ParkingTicket;
class FeeStrategy;

// Enum for vehicle types
enum class VehicleType {
    CAR,
    BIKE,
    TRUCK
};

// Enum for parking spot types
enum class ParkingSpotType {
    COMPACT,
    LARGE,
    BIKE
};

// Abstract class for Vehicle
class Vehicle {
protected:
    string licensePlate;
    VehicleType type;

public:
    Vehicle(string licensePlate, VehicleType type) : licensePlate(licensePlate), type(type) {}
    string getLicenseNumber() const { return licensePlate; }
    VehicleType getType() const { return type; }
};

// Car class
class Car : public Vehicle {
public:
    Car(string license) : Vehicle(license, VehicleType::CAR) {}
};

// Bike class
class Bike : public Vehicle {
public:
    Bike(string license) : Vehicle(license, VehicleType::BIKE) {}
};

// Truck class
class Truck : public Vehicle {
public:
    Truck(string license) : Vehicle(license, VehicleType::TRUCK) {}
};

// Abstract class for ParkingSpot
class ParkingSpot {
protected:
    string spotId;
    bool isOccupied;
    shared_ptr<Vehicle> vehicle;

public:
    ParkingSpot(string spotId) : spotId(spotId), isOccupied(false) {}

    virtual bool canFitVehicle(shared_ptr<Vehicle> vehicle) const = 0;
    bool isAvailable() const { return !isOccupied; }
    bool assignVehicle(shared_ptr<Vehicle> v) {
        if (isOccupied) return false;
        vehicle = v;
        isOccupied = true;
        return true;
    }
    void removeVehicle() {
        vehicle.reset();
        isOccupied = false;
    }
    string getSpotId() const { return spotId; }
};

// BikeSpot class
class BikeSpot : public ParkingSpot {
public:
    BikeSpot(string spotId) : ParkingSpot(spotId) {}
    bool canFitVehicle(shared_ptr<Vehicle> v) const override {
        return v->getType() == VehicleType::BIKE;
    }
};

// CompactSpot class
class CompactSpot : public ParkingSpot {
public:
    CompactSpot(string spotId) : ParkingSpot(spotId) {}
    bool canFitVehicle(shared_ptr<Vehicle> v) const override {
        return v->getType() == VehicleType::CAR;
    }
};

// LargeSpot class
class LargeSpot : public ParkingSpot {
public:
    LargeSpot(string spotId) : ParkingSpot(spotId) {}
    bool canFitVehicle(shared_ptr<Vehicle> v) const override {
        return v->getType() == VehicleType::TRUCK;
    }
};

// Factory class to create parking spots
class ParkingSpotFactory {
public:
    static shared_ptr<ParkingSpot> createParkingSpot(ParkingSpotType type, string spotId) {
        switch (type) {
        case ParkingSpotType::BIKE:
            return make_shared<BikeSpot>(spotId);
        case ParkingSpotType::COMPACT:
            return make_shared<CompactSpot>(spotId);
        case ParkingSpotType::LARGE:
            return make_shared<LargeSpot>(spotId);
        default:
            throw invalid_argument("Unknown parking spot type");
        }
    }
};

// FeeStrategy interface
class FeeStrategy {
public:
    virtual double calculateFee(shared_ptr<ParkingTicket> ticket) = 0;
};

// FlatRateFeeStrategy class
class FlatRateFeeStrategy : public FeeStrategy {
private:
    static const double RATE_PER_HOUR;

public:
    double calculateFee(shared_ptr<ParkingTicket> ticket) override {
        time_t duration = ticket->getExitTimestamp() - ticket->getEntryTimestamp();
        long hours = (duration / (60 * 60)) + 1;
        return hours * RATE_PER_HOUR;
    }
};

const double FlatRateFeeStrategy::RATE_PER_HOUR = 10.0;

// VehicleBasedFeeStrategy class
class VehicleBasedFeeStrategy : public FeeStrategy {
private:
    unordered_map<VehicleType, double> hourlyRates;

public:
    VehicleBasedFeeStrategy() {
        hourlyRates[VehicleType::CAR] = 20.0;
        hourlyRates[VehicleType::BIKE] = 10.0;
        hourlyRates[VehicleType::TRUCK] = 30.0;
    }

    double calculateFee(shared_ptr<ParkingTicket> ticket) override {
        time_t duration = ticket->getExitTimestamp() - ticket->getEntryTimestamp();
        long hours = (duration / (60 * 60)) + 1;
        return hours * hourlyRates[ticket->getVehicle()->getType()];
    }
};

// ParkingTicket class
class ParkingTicket {
private:
    string ticketId;
    shared_ptr<Vehicle> vehicle;
    shared_ptr<ParkingSpot> spot;
    time_t entryTimestamp;
    time_t exitTimestamp;

public:
    ParkingTicket(shared_ptr<Vehicle> v, shared_ptr<ParkingSpot> s)
        : vehicle(v), spot(s), entryTimestamp(time(0)) {
        ticketId = to_string(rand());  // Just a simple random string generator
    }

    string getTicketId() const { return ticketId; }
    shared_ptr<Vehicle> getVehicle() const { return vehicle; }
    shared_ptr<ParkingSpot> getSpot() const { return spot; }
    time_t getEntryTimestamp() const { return entryTimestamp; }
    time_t getExitTimestamp() const { return exitTimestamp; }

    void setExitTimestamp() { exitTimestamp = time(0); }
};

// ParkingFloor class
class ParkingFloor {
private:
    int floorNumber;
    vector<shared_ptr<ParkingSpot>> parkingSpots;

public:
    ParkingFloor(int floorNumber, vector<shared_ptr<ParkingSpot>> spots)
        : floorNumber(floorNumber), parkingSpots(spots) {}

    shared_ptr<ParkingSpot> getAvailableSpot(shared_ptr<Vehicle> vehicle) {
        for (auto& spot : parkingSpots) {
            if (spot->isAvailable() && spot->canFitVehicle(vehicle)) {
                return spot;
            }
        }
        return nullptr;
    }
};

// ParkingLot Singleton class
class ParkingLot {
private:
    static ParkingLot* instance;
    vector<shared_ptr<ParkingFloor>> floors;
    unordered_map<string, shared_ptr<ParkingTicket>> activeTickets;
    shared_ptr<FeeStrategy> feeStrategy;
    mutex mtx; // Mutex for thread safety

    vector<Observer*> observers;

    ParkingLot() {
        feeStrategy = make_shared<FlatRateFeeStrategy>();
    }

public:
    static ParkingLot* getInstance() {
        static ParkingLot* instance = nullptr; // Thread-safe initialization
        if (!instance) {
            instance = new ParkingLot();
        }
        return instance;
    }

    void addFloor(shared_ptr<ParkingFloor> floor) {
        floors.push_back(floor);
    }

    void setFeeStrategy(shared_ptr<FeeStrategy> strategy) {
        feeStrategy = strategy;
    }

    shared_ptr<ParkingTicket> parkVehicle(shared_ptr<Vehicle> vehicle) {
        lock_guard<mutex> lock(mtx); // Locking to ensure thread safety
        for (auto& floor : floors) {
            shared_ptr<ParkingSpot> spot = floor->getAvailableSpot(vehicle);
            if (spot) {
                if (spot->assignVehicle(vehicle)) {
                    auto ticket = make_shared<ParkingTicket>(vehicle, spot);
                    activeTickets[vehicle->getLicenseNumber()] = ticket;
                    return ticket;
                }
            }
        }
        throw runtime_error("No available spot for the vehicle");
    }

    void notifyObservers(const string& message) {
        for (Observer* obs : observers) {
            obs->notify(message);
        }
    }

    double unparkVehicle(string license) {
        lock_guard<mutex> lock(mtx); // Locking to ensure thread safety
        auto ticket = activeTickets[license];
        if (!ticket) throw runtime_error("Ticket not found");

        ticket->getSpot()->removeVehicle();
        ticket->setExitTimestamp();

        notifyObservers("A parking spot is now available!");
        return feeStrategy->calculateFee(ticket);
    }
};

// Define the static instance of ParkingLot
ParkingLot* ParkingLot::instance = nullptr;

// Demo function with concurrency
void parkingLotDemo() {
    ParkingLot* parkingLot = ParkingLot::getInstance();

    vector<shared_ptr<ParkingSpot>> parkingSpotsFloor1 = {
        ParkingSpotFactory::createParkingSpot(ParkingSpotType::BIKE, "101"),
        ParkingSpotFactory::createParkingSpot(ParkingSpotType::COMPACT, "102"),
        ParkingSpotFactory::createParkingSpot(ParkingSpotType::LARGE, "103")
    };

    vector<shared_ptr<ParkingSpot>> parkingSpotsFloor2 = {
        ParkingSpotFactory::createParkingSpot(ParkingSpotType::BIKE, "201"),
        ParkingSpotFactory::createParkingSpot(ParkingSpotType::LARGE, "202")
    };

    shared_ptr<ParkingFloor> floor1 = make_shared<ParkingFloor>(1, parkingSpotsFloor1);
    shared_ptr<ParkingFloor> floor2 = make_shared<ParkingFloor>(2, parkingSpotsFloor2);

    parkingLot->addFloor(floor1);
    parkingLot->addFloor(floor2);

    parkingLot->setFeeStrategy(make_shared<VehicleBasedFeeStrategy>());

    // Create vehicles
    shared_ptr<Vehicle> car1 = make_shared<Car>("ABC123");
    shared_ptr<Vehicle> bike1 = make_shared<Bike>("M1234");

    // Run parking and unparking in different threads
    thread t1([&]() {
        try {
            auto ticket1 = parkingLot->parkVehicle(car1);
            cout << "Car 1 parked, Ticket Id: " << ticket1->getTicketId() << endl;
            double fee = parkingLot->unparkVehicle(car1->getLicenseNumber());
            cout << "Car 1 Unparked, Fee: " << fee << endl;
        } catch (const exception& e) {
            cout << "Exception: " << e.what() << endl;
        }
    });

    thread t2([&]() {
        try {
            auto ticket2 = parkingLot->parkVehicle(bike1);
            cout << "Bike 1 parked, Ticket Id: " << ticket2->getTicketId() << endl;
        } catch (const exception& e) {
            cout << "Exception: " << e.what() << endl;
        }
    });

    t1.join();
    t2.join();
}

class Observer {
public:
    virtual void notify(string message) = 0;
    virtual ~Observer() = default;
};

class Customer : public Observer {
private:
    string name;
public:
    Customer(const string& name) : name(name) {}

    void notify(string message) override {
        cout << "[Notification to " << name << "]: " << message << endl;
    }

    string getName() const { return name; }
};


int main() {
    srand(time(0));
    parkingLotDemo();
    return 0;
}
