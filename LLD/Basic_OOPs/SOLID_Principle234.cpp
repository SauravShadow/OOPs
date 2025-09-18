#include <iostream>
#include <string>

using namespace std;
/*
###########################################################
3. Liskov Substitution Principle
- object of superclass should be replaceable with objects of a subclass without breaking the correctness of the program.
- To enforce proper inheritance
*/

class Fighter
{
public:
    virtual string description() = 0;
    virtual ~Fighter() = default;
};

class Demon: public Fighter
{
    string m_sUpperMoon;
public:
    Demon(string moon) : m_sUpperMoon(moon){}
    string description() override
    {
        return "Upper Moon Demon: " + m_sUpperMoon ;
    }
};

class DemonSlayer: public Fighter
{
    string m_sBreathingStyle;
public:
    DemonSlayer(string breathingStyle) : m_sBreathingStyle(breathingStyle){}
    string description() override
    {
        return "Demon Slayer: " + m_sBreathingStyle + "Hashira" ;
    }
};

void printFighterInfo(Fighter& fighter)
{
    cout << fighter.description() << endl;
};

int main()
{
    DemonSlayer giyu("Water");
    Demon akaza("three");

    printFighterInfo(giyu);
    printFighterInfo(akaza);
}
