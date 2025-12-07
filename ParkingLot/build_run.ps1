# build_run.ps1
cd $PSScriptRoot
cmd /c "chcp 65001>nul && C:\MinGW\bin\g++.exe -fdiagnostics-color=always -g ParkingLotDemo.cpp ParkingLot.cpp entities\*.cpp strategy\parking\*.cpp strategy\fee\*.cpp vehicle\*.cpp -o ParkingLotDemo.exe"
.\ParkingLotDemo.exe
