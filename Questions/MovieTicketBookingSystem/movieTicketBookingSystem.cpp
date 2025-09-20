#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <unordered_map>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <ctime>
#include <atomic>
#include <mutex>

using namespace std;

class PaymentMethod
{
public:
        virtual bool pay(double amount) = 0;
        virtual string getMethodName() const = 0;
        virtual ~PaymentMethod() = default;
};

class PaytmPayment : public PaymentMethod
{
public:
        bool pay(double amount) override
        {
                cout << "Paid ₹" << amount << " using Paytm.\n";
                return true; // mock success
        }
        string getMethodName() const override
        {
                return "Paytm";
        }
};

class CardPayment : public PaymentMethod
{
public:
        bool pay(double amount) override
        {
                cout << "Paid ₹" << amount << " using Credit/Debit Card.\n";
                return true; // mock success
        }
        string getMethodName() const override
        {
                return "Card";
        }
};

class UpiPayment : public PaymentMethod
{
public:
        bool pay(double amount) override
        {
                cout << "Paid ₹" << amount << " using UPI.\n";
                return true;
        }
        string getMethodName() const override
        {
                return "UPI";
        }
};

// Exception Classes
class SeatNotAvailableException : public exception
{
public:
        const char *what() const noexcept override
        {
                return "One or more selected seats are not available.";
        }
};

class InvalidShowException : public exception
{
public:
        const char *what() const noexcept override
        {
                return "The selected show is invalid or not found.";
        }
};

class BookingFailedException : public exception
{
public:
        const char *what() const noexcept override
        {
                return "Failed to complete the booking.";
        }
};

class CancellationFailedException : public exception
{
public:
        const char *what() const noexcept override
        {
                return "Failed to cancel the booking.";
        }
};

// Enums
enum class SeatStatus
{
        AVAILABLE,
        BOOKED
};
enum class SeatType
{
        NORMAL,
        PREMIUM
};
enum class BookingStatus
{
        PENDING,
        CONFIRMED,
        CANCELLED
};

// Forward Declarations
class Show;
class User;

// Seat Class
class Seat
{
        string id;
        int row, column;
        SeatType type;
        double price;
        SeatStatus status;

public:
        Seat(string id, int row, int column, SeatType type, double price, SeatStatus status)
            : id(id), row(row), column(column), type(type), price(price), status(status) {}

        string getId() const { return id; }
        int getRow() const { return row; }
        int getColumn() const { return column; }
        SeatType getType() const { return type; }
        double getPrice() const { return price; }
        SeatStatus getStatus() const { return status; }
        void setStatus(SeatStatus s) { status = s; }
};

// Movie Class
class Movie
{
        string id, title, description;
        int durationInMinutes;

public:
        Movie(string id, string title, string description, int duration)
            : id(id), title(title), description(description), durationInMinutes(duration) {}

        int getDurationInMinutes() const { return durationInMinutes; }
        string getId() const { return id; }
        string getTitle() const { return title; }
};

// Theater Class
class Theater
{
        string id, name, location;
        vector<shared_ptr<Show>> shows;

public:
        Theater(string id, string name, string location)
            : id(id), name(name), location(location) {}

        string getId() const { return id; }
        void addShow(shared_ptr<Show> show) { shows.push_back(show); }
};

// User Class
class User
{
        string id, name, email;

public:
        User(string id, string name, string email)
            : id(id), name(name), email(email) {}

        string getId() const { return id; }
};

// Show Class
class Show
{
        string id;
        shared_ptr<Movie> movie;
        shared_ptr<Theater> theater;
        time_t startTime, endTime;
        map<string, shared_ptr<Seat>> seats;

public:
        Show(string id, shared_ptr<Movie> movie, shared_ptr<Theater> theater,
             time_t start, time_t end, map<string, shared_ptr<Seat>> seats)
            : id(id), movie(movie), theater(theater), startTime(start), endTime(end), seats(seats) {}

        string getId() const { return id; }
        map<string, shared_ptr<Seat>> &getSeats() { return seats; }
        shared_ptr<Movie> getMovie() const { return movie; }
        shared_ptr<Theater> getTheater() const { return theater; }
};

// Booking Class
class Booking
{
        string id;
        shared_ptr<User> user;
        shared_ptr<Show> show;
        vector<shared_ptr<Seat>> seats;
        shared_ptr<PaymentMethod> paymentMethod;
        double totalPrice;
        BookingStatus status;

public:
        Booking(string id, shared_ptr<User> user, shared_ptr<Show> show,
                vector<shared_ptr<Seat>> seats, double price, BookingStatus status, shared_ptr<PaymentMethod> paymentMethod)
            : id(id), user(user), show(show), seats(seats), totalPrice(price), status(status), paymentMethod(paymentMethod) {}

        bool processPayment()
        {
                if (!paymentMethod)
                        return false;
                return paymentMethod->pay(totalPrice);
        }

        string getPaymentMethod() const
        {
                return paymentMethod ? paymentMethod->getMethodName() : "None";
        }
        string getId() const { return id; }
        BookingStatus getStatus() const { return status; }
        void setStatus(BookingStatus s) { status = s; }
        shared_ptr<Show> getShow() const { return show; }
        const vector<shared_ptr<Seat>> &getSeats() const { return seats; }
};

// Singleton Booking System
class MovieTicketBookingSystem
{
        vector<shared_ptr<Movie>> movies;
        vector<shared_ptr<Theater>> theaters;
        unordered_map<string, shared_ptr<Show>> shows;
        unordered_map<string, shared_ptr<Booking>> bookings;

        static shared_ptr<MovieTicketBookingSystem> instance;
        static atomic<long> bookingCounter;
        static mutex mtx;

        MovieTicketBookingSystem() = default;

public:
        static shared_ptr<MovieTicketBookingSystem> getInstance()
        {
                lock_guard<mutex> lock(mtx);
                if (!instance)
                        instance = shared_ptr<MovieTicketBookingSystem>();
                return instance;
        }

        void addMovie(shared_ptr<Movie> movie) { movies.push_back(movie); }
        void addTheater(shared_ptr<Theater> theater) { theaters.push_back(theater); }
        void addShow(shared_ptr<Show> show) { shows[show->getId()] = show; }

        shared_ptr<Booking> bookTickets(shared_ptr<User> user, shared_ptr<Show> show, vector<shared_ptr<Seat>> selectedSeats)
        {
                lock_guard<mutex> lock(mtx);
                for (auto &seat : selectedSeats)
                {
                        //     if (show->getSeats()[seat->getId()]->getStatus() != SeatStatus::AVAILABLE)
                        // return nullptr;

                        if (show == nullptr)
                        {
                                throw InvalidShowException();
                        }
                        for (auto &seat : selectedSeats)
                        {
                                auto it = show->getSeats().find(seat->getId());
                                if (it == show->getSeats().end() || it->second->getStatus() != SeatStatus::AVAILABLE)
                                {
                                        throw SeatNotAvailableException();
                                }
                        }
                }

                if (selectedSeats.empty())
                {
                        throw BookingFailedException();
                }

                for (auto &seat : selectedSeats)
                {
                        show->getSeats()[seat->getId()]->setStatus(SeatStatus::BOOKED);
                }

                double totalPrice = 0.0;
                for (auto &seat : selectedSeats)
                        totalPrice += seat->getPrice();

                string bookingId = generateBookingId();
                auto booking = make_shared<Booking>(bookingId, user, show, selectedSeats, totalPrice, BookingStatus::PENDING);
                bookings[bookingId] = booking;
                return booking;
        }

        void confirmBooking(const string &bookingId)
        {
                lock_guard<mutex> lock(mtx);
                auto it = bookings.find(bookingId);
                if (it != bookings.end() && it->second->getStatus() == BookingStatus::PENDING)
                {
                        it->second->setStatus(BookingStatus::CONFIRMED);
                }
        }

        void cancelBooking(const string &bookingId)
        {
                lock_guard<mutex> lock(mtx);
                auto it = bookings.find(bookingId);
                if (it == bookings.end() || it->second->getStatus() == BookingStatus::CANCELLED)
                {
                        throw CancellationFailedException();
                }

                if (it != bookings.end() && it->second->getStatus() != BookingStatus::CANCELLED)
                {
                        it->second->setStatus(BookingStatus::CANCELLED);
                        for (auto &seat : it->second->getSeats())
                        {
                                it->second->getShow()->getSeats()[seat->getId()]->setStatus(SeatStatus::AVAILABLE);
                        }
                }
        }

private:
        string generateBookingId()
        {
                time_t now = time(nullptr);
                tm *ltm = localtime(&now);
                stringstream ss;
                ss << "BKG" << put_time(ltm, "%Y%m%d%H%M%S") << setw(6) << setfill('0') << bookingCounter++;
                return ss.str();
        }
};

shared_ptr<MovieTicketBookingSystem> MovieTicketBookingSystem::instance = nullptr;
atomic<long> MovieTicketBookingSystem::bookingCounter(0);
mutex MovieTicketBookingSystem::mtx;

// Helper to create seats
map<string, shared_ptr<Seat>> createSeats(int rows, int cols)
{
        map<string, shared_ptr<Seat>> seats;
        for (int r = 1; r <= rows; ++r)
        {
                for (int c = 1; c <= cols; ++c)
                {
                        string id = to_string(r) + "-" + to_string(c);
                        SeatType type = (r <= 2) ? SeatType::PREMIUM : SeatType::NORMAL;
                        double price = (type == SeatType::PREMIUM) ? 150.0 : 100.0;
                        seats[id] = make_shared<Seat>(id, r, c, type, price, SeatStatus::AVAILABLE);
                }
        }
        return seats;
}

// Demo Function
int main()
{
        auto system = MovieTicketBookingSystem::getInstance();

        auto movie1 = make_shared<Movie>("M1", "Movie 1", "Desc", 120);
        auto movie2 = make_shared<Movie>("M2", "Movie 2", "Desc", 135);
        system->addMovie(movie1);
        system->addMovie(movie2);

        auto theater1 = make_shared<Theater>("T1", "Theater 1", "City 1");
        auto theater2 = make_shared<Theater>("T2", "Theater 2", "City 2");
        system->addTheater(theater1);
        system->addTheater(theater2);

        time_t now = time(nullptr);
        auto show1 = make_shared<Show>("S1", movie1, theater1, now, now + 7200, createSeats(10, 10));
        auto show2 = make_shared<Show>("S2", movie2, theater2, now, now + 8100, createSeats(8, 8));
        system->addShow(show1);
        system->addShow(show2);

        auto user = make_shared<User>("U1", "Piyush", "piyush@example.com");
        vector<shared_ptr<Seat>> selected = {show1->getSeats()["1-5"], show1->getSeats()["1-6"]};
        try
        {
                auto booking = system->bookTickets(user, show1, selected);
                if (booking)
                {
                        cout << "Booking Success: " << booking->getId() << endl;
                        system->confirmBooking(booking->getId());

                        system->cancelBooking(booking->getId());
                        cout << "Booking Cancelled: " << booking->getId() << endl;
                }
                else
                {
                        cout << "Booking Failed" << endl;
                }
        }
        catch (const exception &ex)
        {
                cerr << "Error: " << ex.what() << endl;
        }

        return 0;
}
