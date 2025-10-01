// Observer Pattern
/*
It defines a one-to-many dependency between objects so that when one object changes state, all its dependents (the Observers)
are automatically notified and updated
- To decouple the subjects from its observers

Key Components:
- Subject (Observable): maintains list of observers, provide attach(), detach() and notifies observers.
- Observer: Interface that defines an update()/onNotify() method.
- ConcreteSubject / ConcreteObserver: Concrete Implementations
*/

/*
Example:

Interfaces:
    IObservable -> subject contract (attach, detach, notify).
    IObserver -> observer contract (Update).
    IDisplay -> display contract (show data).

Concrete
    WeatherStation -> The concrete subject
    PhoneDisplay and WindowDisplay -> Concrete Observers
*/

#include <iostream>
#include <vector>
#include <algorithm>

// ----------------- INTERFACE ------------------

// Display Interface
struct IDisplay
{
    virtual void display() = 0;
    virtual ~IDisplay() = default;
};

// Observer Interface
struct IObserver
{
    virtual void update(float temperature) = 0;
    virtual ~IObserver() = default;
};

// Observable (Subject) Interface
struct IObservable
{
    virtual void attach(IObserver* o) = 0;
    virtual void detach(IObserver* o) = 0;
    virtual void notify() = 0;
    virtual ~IObservable() = default;
};

// --------------------- CONCRETE CLASSES ----------------------

// Concrete Subject : Weather Station
class WeatherStation: public IObservable
{
    std::vector<IObserver*> observers;
    float temperature = 0.0f;

public:
    void attach(IObserver* o) override
    {
        observers.push_back(o);
    }

    void detach(IObserver* o) override
    {
        observers.erase(std::remove(observers.begin(), observers.end(), o), observers.end());
    }

    void notify() override
    {
        for (auto* o : observers)
            o->update(temperature);
    }

    void setTemperature(float temp)
    {
        temperature = temp;
        notify();
    }
};

// Concrete Observer: Window Display
class WindowDsplay :public IDisplay, public IObserver
{
    float temperature = 0.0f;

public:
    void update (float temp) override
    {
        temperature = temp;
        display();
    }

    void display() override
    {
        std::cout << "Window Display -> Temperature: " << temperature << "Celsius\n";
    }
};

//Concrete Observer: Phone Display
class PhoneDisplay: public IDisplay, public IObserver
{
    float temperature = 0.0f;

public:
    void update (float temp) override
        {
            temperature = temp;
            display();
        }

    void display() override
    {
        std::cout << "Phone Display -> Temperature: " << temperature << "Celsius\n";
    }
};

int main ()
{
    WeatherStation station;

    PhoneDisplay phone;
    WindowDsplay window;

    //Attach Observer
    station.attach(&phone);
    station.attach(&window);

    // Change weather state
    station.setTemperature(25.5f);
    station.setTemperature(30.0f);

    //Detach one observer
    station.detach(&window);
    station.setTemperature(28.2f);

    return 0;
}

// Now here let's see about the dangling pointers
/*
- Weather station keeps the raw pointer of observers
- If one of those observers is destroyed while still attached to the subject
- The weather station still has a pointer to it in observers.
- Next time station.notify() is called, it may call a deleted object
*/

// BOOM - Dangling pointer access -> Undefined behavior -> Crashed


// Solution
/*

Instead of storing IObserver*, store std::weak_ptr<IObserver>

- Observers are held weakly, so they don't keep them alive forever

void notify(float temp) override
{
    for (auto it = observers.begin(); it != observers.end();)
    {
        if (auto obs = it->lock())    // Here lock converts the weak pointer to shared_ptr if it exist (Precaution in case of destroyed case)
        {
            obs->update(temp); // push the temperature
            ++it;
        } else
        {
            it = observers.erase(it); // clean expired
    }   }
}

// Now weather station keeps only the weak_ptr, if an observer is destroyed, the weak_ptr becomes expired
// On next notify(), exxpired observers are cleaned automatically

*/
