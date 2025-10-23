#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <chrono>
#include <iomanip>
#include <thread>

using namespace std;

//////////////////////////////////// Vehicle Type ////////////////////////////////////
class Vehicle
{
protected:
    string vehicleNo;
public:
    Vehicle(const string& no) : vehicleNo(no) {}
    virtual int getTotalCount() = 0;
    string getVehicleNo() const { return vehicleNo; }
    virtual ~Vehicle() = default;
};

class Bike : public Vehicle
{
    static int iBikeCount;
public:
    Bike(const string& no) : Vehicle(no) { iBikeCount++; }
    int getTotalCount() override { return iBikeCount; }
};
int Bike::iBikeCount = 0;

class Car : public Vehicle
{
    static int iCarCount;
public:
    Car(const string& no) : Vehicle(no) { iCarCount++; }
    int getTotalCount() override { return iCarCount; }
};
int Car::iCarCount = 0;

class Truck : public Vehicle
{
    static int iTruckCount;
public:
    Truck(const string& no) : Vehicle(no) { iTruckCount++; }
    int getTotalCount() override { return iTruckCount; }
};
int Truck::iTruckCount = 0;

/////////////////////////////// Available Spots /////////////////////////
class InitiateSpots
{
    string vehicleType;
    priority_queue<int, vector<int>, greater<int>> vehicleCapacity; // min-heap

public:
    InitiateSpots() = default;
    InitiateSpots(const string& veh) : vehicleType(veh) {}

    void VehicleCapacity(int n)
    {
        for (int i = 1; i <= n; i++)
            vehicleCapacity.push(i);
    }

    int getAvailableSpots()
    {
        if (vehicleCapacity.empty())
            return -1;

        int spotNo = vehicleCapacity.top();
        vehicleCapacity.pop();
        return spotNo;
    }

    void releaseSpot(int spotNo)
    {
        vehicleCapacity.push(spotNo);
    }
};

//////////////////////// Receipt /////////////////////////

class Receipt
{
    string vehicleNo;
    string vehicleType;
    int spotNo;
    int floorNo;
    chrono::system_clock::time_point entryTime;

public:
    Receipt() = default;  // Default constructor required for unordered_map
    Receipt(const string& vNo, const string& vType, int s, int f)
        : vehicleNo(vNo), vehicleType(vType), spotNo(s), floorNo(f),
          entryTime(chrono::system_clock::now()) {}

    string getVehicleNo() const { return vehicleNo; }
    string getVehicleType() const { return vehicleType; }
    int getSpotNo() const { return spotNo; }
    int getFloorNo() const { return floorNo; }
    chrono::system_clock::time_point getEntryTime() const { return entryTime; }

    void printReceipt() const
    {
        auto t = chrono::system_clock::to_time_t(entryTime);
        cout << "\n===== Entry Receipt =====\n";
        cout << "Vehicle No: " << vehicleNo
             << "\nVehicle Type: " << vehicleType
             << "\nSpot No: " << spotNo
             << "\nFloor No: " << floorNo
             << "\nEntry Time: " << put_time(localtime(&t), "%Y-%m-%d %H:%M:%S")
             << "\n=========================\n";
    }
};

//////////////////////// Rate /////////////////////////
class Rate
{
    string vehicleType;
    float rate;

public:
    Rate() = default;
    Rate(string vehicleType, float rate) : vehicleType(vehicleType), rate(rate) {}

    float getRate() const { return rate; }
};

//////////////////////// Bill /////////////////////////
class Bill
{
    chrono::system_clock::time_point entryTime;
    chrono::system_clock::time_point exitTime;
    Rate rate;

public:
    Bill(chrono::system_clock::time_point entry,
         chrono::system_clock::time_point exit,
         Rate rate)
        : entryTime(entry), exitTime(exit), rate(rate) {}

    float calculateBill()
    {
        auto duration = chrono::duration_cast<chrono::minutes>(exitTime - entryTime);
        float hours = duration.count() / 60.0f;
        if (hours < 1) hours = 1; // minimum 1 hour billing
        return hours * rate.getRate();
    }
};

//////////////////////// Parking Lot Manager /////////////////////////
class ParkingLotManager
{
    InitiateSpots bikeSpots;
    InitiateSpots carSpots;
    InitiateSpots truckSpots;
    Rate bikeRate;
    Rate carRate;
    Rate truckRate;

    unordered_map<string, Receipt> activeVehicles;

public:
    ParkingLotManager(int b, int c, int t)
        : bikeSpots("Bike"), carSpots("Car"), truckSpots("Truck"),
          bikeRate("Bike", 10.0f), carRate("Car", 20.0f), truckRate("Truck", 30.0f)
    {
        bikeSpots.VehicleCapacity(b);
        carSpots.VehicleCapacity(c);
        truckSpots.VehicleCapacity(t);
    }

    Receipt vehicleEntry(const string& vehicleNo, const string& type)
    {
        int spot = -1;
        if (type == "Bike") spot = bikeSpots.getAvailableSpots();
        else if (type == "Car") spot = carSpots.getAvailableSpots();
        else if (type == "Truck") spot = truckSpots.getAvailableSpots();

        if (spot == -1)
        {
            cout << "No spot available for " << type << "\n";
            throw runtime_error("No spot available");
        }

        Receipt r(vehicleNo, type, spot, 1);
        activeVehicles[vehicleNo] = r;
        r.printReceipt();
        return r;
    }

    void vehicleExit(const string& vehicleNo)
    {
        auto it = activeVehicles.find(vehicleNo);
        if (it == activeVehicles.end())
        {
            cout << "Vehicle not found.\n";
            return;
        }

        auto receipt = it->second;
        auto exitTime = chrono::system_clock::now();
        Rate applicableRate;

        if (receipt.getVehicleType() == "Bike") {
            bikeSpots.releaseSpot(receipt.getSpotNo());
            applicableRate = bikeRate;
        } else if (receipt.getVehicleType() == "Car") {
            carSpots.releaseSpot(receipt.getSpotNo());
            applicableRate = carRate;
        } else if (receipt.getVehicleType() == "Truck") {
            truckSpots.releaseSpot(receipt.getSpotNo());
            applicableRate = truckRate;
        }

        Bill bill(receipt.getEntryTime(), exitTime, applicableRate);
        float amount = bill.calculateBill();

        auto t = chrono::system_clock::to_time_t(exitTime);
        cout << "\n===== Exit Receipt =====\n";
        cout << "Vehicle No: " << receipt.getVehicleNo()
             << "\nVehicle Type: " << receipt.getVehicleType()
             << "\nExit Time: " << put_time(localtime(&t), "%Y-%m-%d %H:%M:%S")
             << "\nTotal Amount: ₹" << amount
             << "\n========================\n";

        activeVehicles.erase(it);
    }
};

//////////////////////// Main /////////////////////////
int main()
{
    ParkingLotManager manager(2, 2, 1);

    try
    {
        auto r1 = manager.vehicleEntry("BIKE123", "Bike");
        auto r2 = manager.vehicleEntry("CAR999", "Car");

        // simulate time gap (for demo purpose)
        this_thread::sleep_for(chrono::seconds(2));

        manager.vehicleExit("BIKE123");
        manager.vehicleExit("CAR999");
    }
    catch (const exception& e)
    {
        cerr << "Exception: " << e.what() << endl;
    }

    return 0;
}
