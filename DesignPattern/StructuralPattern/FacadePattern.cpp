// FACADE PATTERN
/*
It provides a simplified interface to a complex subsystem
- It hides internal details of many classes and exposes a unified, easy-to-use interface
  to the client
- Easier to use, reduces coupling and improves readability

## When to use
- When you have a complex system with many interacting parts.
- When you want to make a system easier to use for clients.
- When you want to decouple client code from subsystem details.
*/


#include <iostream>
#include <string>

using namespace std;

// Example : Home theatre system
class Amplifier
{
public:
    void on() {cout << "Amplifier on" << endl; }
    void setVolume(int level) {cout << "Volume set to " << level << endl;}
};

class DvdPlayer
{
public:
  void on()  {cout << "DVD Player on" << endl;}
  void play(string movie) {cout << "Playing " << movie << endl;}
};

class Projector
{
public:
  void on() {cout << "Projector on" << endl;}
  void wideScreenMode() { cout << "Wide Screen mode" << endl;}
};

//Facade

class HomeTheatreFacade
{
  Amplifier* amp;
  DvdPlayer* dvd;
  Projector* projector;

public:
  HomeTheatreFacade(Amplifier* a, DvdPlayer* d, Projector* p) : amp(a), dvd(d), projector(p) {}

  void watchMovie(string movie)
  {
    cout << "Get ready to watch a movie..." << endl;

    amp->on();
    amp->setVolume(5);

    dvd->on();
    dvd->play(movie);

    projector->on();
    projector->wideScreenMode();
  }

  void endMovie()
  {
    cout << "Shutting down movie theatre..." << endl;
  }
};

int main()
{
  Amplifier a;
  DvdPlayer d;
  Projector p;

  HomeTheatreFacade homeTheatre(&a, &d, &p);

  homeTheatre.watchMovie("Baazigar");

  cout << "\n\nWatched movie for very long.\n";
  homeTheatre.endMovie();

}
