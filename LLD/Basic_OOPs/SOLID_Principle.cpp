#include <iostream>
#include <string>
#include <memory>

using namespace std;

/*
These are the 5 design principle to help the developer to :
- Maintain
- Scale
- Easy to understand
- Flexible to change
*/

//###############################################################################
// S -> Single Responsibility Principle (SRP)
// Each class module has to do one thing

class Anime
{
    string m_sTitle;
    int m_iEpisodes;
    string m_sGenre;

    public:
    //Parameterized Constructor
    Anime(string title, int episodes, string genre) : m_sTitle(title), m_iEpisodes(episodes), m_sGenre(genre){}; // Using Initializer list
    // Other way to do the same : Initializing under constructor body
    // Anime(string title, int episodes) { m_sTitle = title; m_iEpisodes = episodes;}

    string getTitle() { return m_sTitle; }
    int getEpisodes () { return m_iEpisodes;}
    string getGenre () { return m_sGenre;}

    // Here if we do print of this info at once like
    /*void printInfo()
    {
        cout << m_sTitle << " has " << m_iEpisodes << "episodes." << endl;
    }
    */
    // This printing info is breaking the first rule
};

class AnimeInfo
{
    public:
    void printInfo(Anime& anime)
    {
        cout << anime.getTitle() << " has " << anime.getEpisodes() << " episodes and is of "<< anime.getGenre() << endl;
    }
};

void demoSRP ()
{
    cout << "For S Principle: \n";
    Anime anime("Attack On Titan", 75, "action");
    AnimeInfo animeInfo;

    animeInfo.printInfo(anime);
}

//###############################################################################
// O -> Open Closed Principle (OCP)
// Open for extension and closed for modification

// Here the best way to do it using polymorphism
class PrintAnimeInfo
{
    public:
    virtual ~PrintAnimeInfo() = default;

    virtual void printAnimeInfo(Anime& anime) = 0;

};

class ActionAnimeInfo: public PrintAnimeInfo
{
    public:
    void printAnimeInfo(Anime &anime) override
    {
        cout << anime.getTitle() << " is a crazy action anime with "
        << anime.getEpisodes() << " episodes!. It will definitely blow your mind if you watch it" << endl;
    }
};

class RomanceAnimeInfo: public PrintAnimeInfo
{
    public:
    void printAnimeInfo(Anime& anime) override
    {
        cout << anime.getTitle() << " is a sweet romance anime with "
        << anime.getEpisodes() << " episodes!" << endl;
    }
};

void demoOCP()
{
    cout << "\nFor O Principle" << endl;
    Anime anime1("Attack On Tiatan", 75, "Action");
    Anime anime2("Your Lie in April", 22, "Romance");

    unique_ptr<PrintAnimeInfo> pActionAnime = make_unique<ActionAnimeInfo>();
    unique_ptr<PrintAnimeInfo> pRomanceAnime = make_unique<RomanceAnimeInfo>();

    pActionAnime->printAnimeInfo(anime1);
    pRomanceAnime->printAnimeInfo(anime2);
};

int main()
{
    demoSRP();
    demoOCP();
    return 0;
}


//How the above could be changed so that it does not follow OCP
// We could have created a class printAnimeInfo which just print action anime for now
// Inside it there would be a check if (anime.getGenre() == "Action") then only print animeInfo
// This would need to be modified if another genre anime comes into the picture.
//Question : Does this follow the first S principle of single responsibility .
