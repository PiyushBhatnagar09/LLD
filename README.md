**C++ or Java for LLD?**

- Java: Mostly used in Industry, so every interviewer will know this language. LLD is relatively easy in Java than in C++.
- C++: I am more comfortable in C++ because I have used it for 4 years in college. Also, you need to create .hpp files for declaration of class then copy all functions declaration in separate file then write class_name:: before each function and write the logic for each function.

I am going forward with C++. Later on if possible or if needed then I will switch to Java.

Use this command - 
PS D:\PB\PIYUSH\LLD\ParkingLot> .\build_run.ps1

COMMANDS - 
cd 'd:\PB\PIYUSH\LLD\ParkingLot'; & .\ParkingLotDemo.exe

Process done by CoPilot - 
PS D:\PB\PIYUSH\LLD\ParkingLot> cd 'd:\PB\PIYUSH\LLD\ParkingLot'; & cmd /c "chcp 65001>nul && C:\MinGW\bin\g++.exe -fdiagnostics-color=always -g ParkingLotDemo.cpp ParkingLot.cpp entities\ParkingFloor.cpp entities\ParkingSpot.cpp entities\ParkingTicket.cpp strategy\parking\NearestFirstStrategy.cpp strategy\parking\FarthestFirstStrategy.cpp strategy\parking\BestFitStrategy.cpp strategy\fee\VehicleBasedFeeStrategy.cpp strategy\fee\FlatRateFeeStrategy.cpp vehicle\Vehicle.cpp vehicle\Car.cpp vehicle\Bike.cpp vehicle\Truck.cpp -o ParkingLotDemo.exe"
PS D:\PB\PIYUSH\LLD\ParkingLot> cd 'd:\PB\PIYUSH\LLD\ParkingLot'; & cmd /c "if exist ParkingLotDemo.exe (echo EXISTS) else (echo MISSING)"
EXISTS
PS D:\PB\PIYUSH\LLD\ParkingLot> cd 'd:\PB\PIYUSH\LLD\ParkingLot'; & .\ParkingLotDemo.exe
here1

--- Vehicle Entries ---
--- Floor 1 Availability ---
  SMALL spots: 1
  MEDIUM spots: 1
  LARGE spots: 1
--- Floor 2 Availability ---
  SMALL spots: 0
  MEDIUM spots: 2
  LARGE spots: 0
B-123 parked at F1-S1. Ticket: 93e41c6e20911b9b36bc7ce94edc677e
C-456 parked at F1-M1. Ticket: 32d83bb6f3ad985fd4bc655b3d9acbe2
T-789 parked at F1-L1. Ticket: 0a0e086d2926ed9cdf424060b4072b12

--- Availability after parking ---
--- Floor 1 Availability ---
  SMALL spots: 0
  MEDIUM spots: 0
  LARGE spots: 0
--- Floor 2 Availability ---
  SMALL spots: 0
  MEDIUM spots: 2
  LARGE spots: 0
C-999 parked at F2-M1. Ticket: 621d1bfa0a9292d9c0e595902a9c3f76
No available spot for B-000

--- Vehicle Exits ---
Car C-456 unparked. Fee: $20

--- Availability after one car leaves ---
--- Floor 1 Availability ---
  SMALL spots: 0
  MEDIUM spots: 1
  LARGE spots: 0
--- Floor 2 Availability ---
  SMALL spots: 0
  MEDIUM spots: 1
  LARGE spots: 0