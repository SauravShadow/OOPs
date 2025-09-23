// BUILDER DESIGN PATTERN
/*
Instead of writing a giant constructor with 10+ parameter(hard to read, easy to mess up), builder helps to build the object in controlled readable
way.

Key Components
- Product -> The complex object being built.
- Builder(abstract) -> Interface for building the parts.
- ConcreteBuilder -> implements the steps to build a specific representation.
- Director (optional) -> controls the building order.
- Client -> uses the builder to create the object.
*/

#include <iostream>
#include <string>

using namespace std;

// Product
class House
{
    public:
    string walls;
    string roof;
    string windows;
    string doors;

    void show()
    {
        cout << "House with " << walls << " walls, " << roof << " roof, " << windows << " windows, and " << doors << " doors." << endl;
    }
};

// Builder (Abstract Interface)
class HouseBuilder
{
    public:
    virtual ~HouseBuilder() = default;
    virtual void buildWalls() = 0;
    virtual void buildRoof() = 0;
    virtual void buildWindows() = 0;
    virtual void buildDoors() = 0;
    virtual House getResult() = 0;
};

// Concrete Builder : Wooden House
class WoodenHouseBuilder : public HouseBuilder
{
    House house;
public:
    void buildWalls() override { house.walls = "Wooden";}
    void buildRoof() override { house.roof = "Wooden";}
    void buildWindows() override { house.windows = "Glass";}
    void buildDoors() override { house.doors = "Wooden";}
    House getResult() override { return house;}
};

// Concret Builder : Brick House
class BrickHouseBuilder : public HouseBuilder
{
    House house;
public:
    void buildWalls() override { house.walls = "Brick";}
    void buildRoof() override { house.roof = "Concrete";}
    void buildWindows() override { house.windows = "Aluminium";}
    void buildDoors() override { house.doors = "Steel";}
    House getResult() override { return house;}
};

// Director (controls the building order)
class ConstructionEngineer
{
    HouseBuilder* builder;
public:
    ConstructionEngineer(HouseBuilder* b) : builder(b) {}

    House construct()
    {
        builder->buildWalls();
        builder->buildRoof();
        builder->buildWindows();
        builder->buildDoors();

        return builder->getResult();
    }
};

// Client
int main()
{
    WoodenHouseBuilder woodenBuilder;
    BrickHouseBuilder brickBuilder;

    ConstructionEngineer engineer1(&woodenBuilder);
    ConstructionEngineer engineer2(&brickBuilder);

    House woodenHouse = engineer1.construct();
    House brickHouse = engineer2.construct();

    woodenHouse.show();
    brickHouse.show();

    return 0;
}


/*
Let's check for some of the OOPs concept if being followed above or not

1. Encapsulation:
    - House hides it construction detail.
    - Client doesn't see how the house is built

2. Abstraction:
    - House builder is abstract, so the client and director knows only about House builder, not about specific builders

3. Inheritance:
    - WoodenHouseBuilder and BrickHouseBuilder inherit from HouseBuilder

4. Polymorphism
    - virtual functions buildWalls, buildRoofs, etc.
    - Director calls builder method without knowing the actual type

Similarly we can check for all SOLID principle.
*/
