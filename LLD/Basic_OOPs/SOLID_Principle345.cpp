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
// In the above what all the basic OOPs concepts has been used
//Abstraction - Fighter class defines the contract
//Inheritance - Demons and DemonSlayer class inherits the base class Fighter
//Encapsulation - Data like breathing style and upperMoon hidden inside the class
//Polymorphism - Different behavior when calling fighter via get description
/*
##########################################################
4. Interface Segregation Principle
- A class should not be forced to use the interface it does not depend on
*/

class IFighter {
public:
    virtual void fightDemon() = 0;
};

class ITrainer {
public:
    virtual void trainSlayers() = 0;
};

class ISwordsSmith{
public:
    virtual void forgeSword() = 0;
};

// A Hashira implements both IFighter + iTrainer
//for e.g.
class Hashira: public IFighter, public ITrainer {
public:
    void fightDemon() override{}
    void trainSlayers() override{}
};
// New recruits implement only IFighter
// SwordsSmith implement only ISwordSmith

/*
######################################################
5. Dependency Inversion Principle (DIP)
- High level module should not depend on low level modules. Both should depend on abstraction
*/

class IWeapon{
public:
    virtual void attack() = 0;
    virtual ~IWeapon() = default;
};

class NichirinSword : public IWeapon{
public:
    void attack() override{
        cout << "Slashes the demon with Nichirin Sword" << endl;
    }
};

class DemonGun : public IWeapon{
public:
    void attack() override{
        cout << "Shots the demon with the demon gun." << endl;
    }
};

class Hashiras {
    IWeapon* weapon; // Instead of this if we put NichirinSword weapon; -> This would create a direct dependency and the Hashira can only use one type of weapon.
public:
    Hashiras(IWeapon* w) : weapon(w) {}
    void fight()
    {
        weapon->attack();
    }
};

void intMain1()
{
    NichirinSword sword;
    DemonGun gun;

    Hashiras giyu(&sword);
    Hashiras shinobu(&gun);

    giyu.fight();
    shinobu.fight();
}

//Keytakeaways
/*
- High level (Hashira) doesn't care about weapon details.
- Low level (Nichirin Sword) depend on abstraction IWeapon
- New weapons can be added without modifying Hashira -> just implement IWeapon
*/
