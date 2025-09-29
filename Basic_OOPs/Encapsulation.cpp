#include <iostream>
#include <string>
using namespace std;

/*
For restricting access to the data members of a class, we use encapsulation.
    - Basically the private, public and protected data members of the class.
*/

class Anime{
    private:
        string m_sName;
        int m_iEpisodes;
    
    public:

        void setName(string sName)
        {
            m_sName = sName;
        }

        void setEpisodes(int iEpisodes)
        {
            m_iEpisodes = iEpisodes;
        }
        

        string getName()
        {
            return m_sName;
        }

        int getEpisodes()
        {
            return m_iEpisodes;
        }
};

int main()
{
    Anime anime;
    anime.setName("Erase");
    anime.setEpisodes(12);
    cout << "Name: " << anime.getName() << endl;
    cout << "Episodes: " << anime.getEpisodes() << endl;
    return 0;
}