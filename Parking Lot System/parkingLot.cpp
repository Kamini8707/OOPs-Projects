#include <iostream>
#include <vector>
#include <memory>

using namespace std;

enum class VehicleType {
    CAR,
    BIKE,
    TRUCK
};

enum class ParkingSpotType {
    LARGE,
    COMPACT,
    BIKE
};

class ParkingSpot;

class Vehicle {
public:
    Vehicle(VehicleType vehicleType) 
        : vehicleType(vehicleType), vehicleNo(0), parkingSpot(nullptr) {}

    int getVehicleNo() const {
        return vehicleNo;
    }

    void setVehicleNo(int vehicleNo) {
        this->vehicleNo = vehicleNo;
    }

    VehicleType getVehicleType() const {
        return vehicleType;
    }

    void setVehicleType(VehicleType vehicleType) {
        this->vehicleType = vehicleType;
    }

    ParkingSpot* getParkingSpot() const {
        return parkingSpot;
    }

    void setParkingSpot(ParkingSpot* parkingSpot) {
        this->parkingSpot = parkingSpot;
    }

private:
    int vehicleNo;
    VehicleType vehicleType;
    ParkingSpot* parkingSpot;
};

class ParkingSpot {
public:
    ParkingSpot(ParkingSpotType parkingSpotType) 
        : parkingSpotType(parkingSpotType), isFree(true), vehicle(nullptr) {}

    ParkingSpotType getParkingSpotType() const {
        return parkingSpotType;
    }

    void setParkingSpotType(ParkingSpotType parkingSpotType) {
        this->parkingSpotType = parkingSpotType;
    }

    bool getIsFree() const {
        return isFree;
    }

    void setIsFree(bool isFree) {
        this->isFree = isFree;
    }

    Vehicle* getVehicle() const {
        return vehicle;
    }

    void setVehicle(Vehicle* vehicle) {
        this->vehicle = vehicle;
    }

private:
    ParkingSpotType parkingSpotType;
    bool isFree;
    Vehicle* vehicle;
};

class ParkingLot {
public:
    ParkingLot(int largeSpotSize, int compactSpotSize, int bikeSpotSize) 
        : largeSpotSize(largeSpotSize), compactSpotSize(compactSpotSize), bikeSpotSize(bikeSpotSize) {}

    void parkTheVehicle(Vehicle* vehicle) {
        cout << "We are parking the vehicle " << static_cast<int>(vehicle->getVehicleType()) << endl;

        if (vehicle->getVehicleType() == VehicleType::TRUCK) {
            if (largeSpotSize > 0) {
                parkLargeVehicle(vehicle);
            } else {
                cout << "Large parking spots are full" << endl;
            }
        } else if (vehicle->getVehicleType() == VehicleType::CAR) {
            if (compactSpotSize > 0) {
                parkCompactVehicle(vehicle);
            } else {
                cout << "Compact parking spots are full" << endl;
            }
        } else if (vehicle->getVehicleType() == VehicleType::BIKE) {
            if (bikeSpotSize > 0) {
                parkBikeVehicle(vehicle);
            } else {
                cout << "Bike parking spots are full" << endl;
            }
        } else {
            cout << "Given vehicle parking not available" << endl;
        }
    }

    void unparkTheVehicle(Vehicle* vehicle) {
        cout << "We are unparking the vehicle " << static_cast<int>(vehicle->getVehicleType()) << endl;

        ParkingSpot* parkingSpot = vehicle->getParkingSpot();
        parkingSpot->setIsFree(true);

        if (vehicle->getVehicleType() == VehicleType::BIKE) {
            bikeSpotSize++;
        } else if (vehicle->getVehicleType() == VehicleType::TRUCK) {
            largeSpotSize++;
        } else {
            compactSpotSize++;
        }

        cout << "Unparking the vehicle successfully" << endl;
    }

private:
    int largeSpotSize;
    int compactSpotSize;
    int bikeSpotSize;

    vector<shared_ptr<ParkingSpot>> largeParkingSpotList;
    vector<shared_ptr<ParkingSpot>> compactParkingSpotList;
    vector<shared_ptr<ParkingSpot>> bikeParkingSpotList;

    void parkLargeVehicle(Vehicle* vehicle) {
        auto largeParkingSpot = make_shared<ParkingSpot>(ParkingSpotType::LARGE);
        largeParkingSpot->setIsFree(false);
        largeParkingSpot->setVehicle(vehicle);
        vehicle->setParkingSpot(largeParkingSpot.get());

        largeParkingSpotList.push_back(largeParkingSpot);
        largeSpotSize--;
        cout << "Vehicle TRUCK parked successfully" << endl;
    }

    void parkCompactVehicle(Vehicle* vehicle) {
        auto compactParkingSpot = make_shared<ParkingSpot>(ParkingSpotType::COMPACT);
        compactParkingSpot->setIsFree(false);
        compactParkingSpot->setVehicle(vehicle);
        vehicle->setParkingSpot(compactParkingSpot.get());

        compactParkingSpotList.push_back(compactParkingSpot);
        compactSpotSize--;
        cout << "Vehicle CAR parked successfully" << endl;
    }

    void parkBikeVehicle(Vehicle* vehicle) {
        auto bikeParkingSpot = make_shared<ParkingSpot>(ParkingSpotType::BIKE);
        bikeParkingSpot->setIsFree(false);
        bikeParkingSpot->setVehicle(vehicle);
        vehicle->setParkingSpot(bikeParkingSpot.get());

        bikeParkingSpotList.push_back(bikeParkingSpot);
        bikeSpotSize--;
        cout << "Vehicle BIKE parked successfully" << endl;
    }
};

int main() {
    ParkingLot parkingLot(1, 2, 3);

    auto vehicle1 = make_shared<Vehicle>(VehicleType::TRUCK);
    vehicle1->setVehicleNo(12345);
    parkingLot.parkTheVehicle(vehicle1.get());

    auto vehicle2 = make_shared<Vehicle>(VehicleType::TRUCK);
    vehicle2->setVehicleNo(67890);
    parkingLot.parkTheVehicle(vehicle2.get());

    auto vehicle3 = make_shared<Vehicle>(VehicleType::CAR);
    vehicle3->setVehicleNo(11121);
    parkingLot.parkTheVehicle(vehicle3.get());

    auto vehicle4 = make_shared<Vehicle>(VehicleType::BIKE);
    vehicle4->setVehicleNo(31415);
    parkingLot.parkTheVehicle(vehicle4.get());

    parkingLot.unparkTheVehicle(vehicle1.get());
    parkingLot.unparkTheVehicle(vehicle3.get());

    return 0;
}
