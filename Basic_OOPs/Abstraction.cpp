#include <iostream>
#include <string>
using namespace std;

/*
Abstraction is the process of hiding the internalimplementation details and showing only the functionality to the user.
*/

// This is an abstract class
class Anime
{
    public:
        Anime() = default; // Default Constructor. THe derived class must implement this constructor.
        virtual void setName(string sName) = 0;
        virtual void setEpisodes(int iEpisodes) = 0;
        virtual string getName() = 0;
        virtual int getEpisodes() = 0;

        //Virtual Destructor
        virtual ~Anime() = default;
};

// This is a concrete class
class Isekai : public Anime
{
    private:
        string m_sName;
        int m_iEpisodes;

    public:
        Isekai() = default; // Default Constructor.
        void setName(string sName) override
        {
            m_sName = sName;
        }

        void setEpisodes(int iEpisodes) override
        {
            m_iEpisodes = iEpisodes;
        }

        string getName() override
        {
            return m_sName;
        }

        int getEpisodes() override
        {
            return m_iEpisodes;
        }
};

int main()
{
    unique_ptr<Anime> anime = make_unique<Isekai>();
    anime->setName("ReZero");
    anime->setEpisodes(24);
    cout << "Name: " << anime->getName() << endl;
    cout << "Episodes: " << anime->getEpisodes() << endl;
    return 0;
}
