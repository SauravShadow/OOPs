// ADAPTER PATTERN
/*
It allows two incompatible interfaces to work together.
It adapts one class's interface to match what the client code expects.

Key Components:
- Target Interface
- Adaptee(Existing/Legacy class)
- Adapter
- Client(The code that interacts only with the target interface.)
*/

// Let say one system is there which proviede temperature in C but we want in F.

#include <iostream>

using namespace std;

//Existing incompatible class
class CelsiusSensor
{
public:
    double getTemperatureCelsius()
    {
        return 25.0;
    }
};

//Target interface expected by the new system
class FahrenheitCensor
{
public:
    virtual double getTemperatureFahrenheit() = 0;
};

//Adapter class

class TemperatureAdaptor : public FahrenheitCensor
{
private:
    CelsiusSensor& sensor;

public:
    TemperatureAdaptor(CelsiusSensor& sen) : sensor(sen){}

    double getTemperatureFahrenheit() override
    {
        double c = sensor.getTemperatureCelsius();
        return (c*9.0/5.0) + 32.0;
    }
};


int main()
{
    CelsiusSensor celsiusCensor;
    TemperatureAdaptor adapter(celsiusCensor);

    cout << "Temperature in Fahrenheit: " << adapter.getTemperatureFahrenheit() << " Degree" << endl;

    return 0;
}
