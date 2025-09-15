#include <iostream>
#include <string>
using namespace std;

/*
Polymorphism is the ability of an object to take on many forms based on the context it is used in.
Achieved using :
        - Function overloading -> Same function name, different parameter list.
        - Operator overloading -> Define how operators(+, ==, etc.) works for user defined types.
        - Resolved at compile time.
Virtual functions in base class, overridden in derived class.
*/

class Anime
{
    public:
    virtual void print(string s)
    {
        cout << s << " is an anime." << endl;
    }
};

class Isekai: public Anime
{
    public:
    void print(string s)
    {
        cout << s << " is an isekai anime." << endl;
    }
};

int main ()
{
    Anime anime;
    Anime* isek = new Isekai();

    anime.print("Erase");
    isek->print("Rezero");
    return 0;
}
