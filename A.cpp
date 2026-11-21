#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

class TransitUnit {
protected:
    string trainID;
    bool inService;

public:
    static int activeTrains;

    TransitUnit(string id) : trainID(id), inService(true) {
        activeTrains++;
    }

    virtual ~TransitUnit() {
        activeTrains--;
    }

    virtual void transmitTelemetry() = 0;
};

int TransitUnit::activeTrains = 0;

class MagneticLevitationModule : virtual public TransitUnit {
protected:
    double levitationGapMM;

public:
    MagneticLevitationModule(string id, double gap) : TransitUnit(id), levitationGapMM(gap) {}

    void checkLevitation() {
        cout << "Maglev coil [" << trainID << "] levitation gap stable at " << levitationGapMM << " mm." << endl;
    }
};

class LinearInductionModule : virtual public TransitUnit {
protected:
    double cruiseSpeedKmh;

public:
    LinearInductionModule(string id, double speed) : TransitUnit(id), cruiseSpeedKmh(speed) {}

    void checkPropulsion() {
        cout << "Linear motor [" << trainID << "] cruising at " << cruiseSpeedKmh << " km/h." << endl;
    }
};

class AutonomousMaglevExpress : public MagneticLevitationModule, public LinearInductionModule {
private:
    int passengerCount;

public:
    AutonomousMaglevExpress(string id, double gap, double speed, int passengers)
        : TransitUnit(id),
          MagneticLevitationModule(id, gap),
          LinearInductionModule(id, speed),
          passengerCount(passengers) {}

    ~AutonomousMaglevExpress() {
        cout << "Maglev train " << trainID << " docked at terminal and coils powered down." << endl;
    }

    void transmitTelemetry() override {
        cout << "\n--- Autonomous Maglev Express Report: " << trainID << " ---" << endl;
        checkLevitation();
        checkPropulsion();
        cout << "Passengers Onboard: " << passengerCount << endl;
        cout << "Track Status: Clear & Synchronized" << endl;
    }
};

int main() {
    TransitUnit* train = new AutonomousMaglevExpress("MAG-EXP-08", 12.5, 430.0, 580);

    train->transmitTelemetry();

    cout << "\nActive Transit Units: " << TransitUnit::activeTrains << endl;

    delete train;

    cout << "Active Units After Terminal Docking: " << TransitUnit::activeTrains << endl;

    return 0;
}
