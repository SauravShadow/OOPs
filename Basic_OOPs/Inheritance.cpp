#include <iostream>
using namespace std;

/*
By using inheritance, one class (child or derived class) can reuse the properties and behavior of another class (parent or base class).
*/

class Anime
{
    public:
    void goodAnime() { cout << "Erase is a good anime" << endl; };
};

class Isekai : public Anime
{
    public:
    void betterAnime(){ cout << "ReZero is a good anime" << endl; };
};

int main ()
{
    Anime anime = Isekai();
    anime.goodAnime();
    //anime.betterAnime();    // This will not work because the betterAnime is not a member of the Anime class

    Isekai isekai = Isekai();
    isekai.betterAnime();
    isekai.goodAnime();
    return 0;
}
