// Singleton Design Pattern
/*
- Ensures that a class has only one instance throughout the program
- Provide a global point of access to that instance

Characteristics:
    - Single Instance
    - Private constructor -> Prevents direct creation with new
    - Static method -> Provides a global way to access the instance
    - Lazy or Eager Initialization -> Instance can be created at load time or only when needed
*/


// Logger in an application

#include <iostream>
#include <string>

using namespace std;

class Logger
{
private:
    static Logger* instance; // The single instance
    Logger() {}              // The private constructor
    // Having private constructor means only the member of the class can call the constructor
public:
    // Deleting copy constructor and assignment
    Logger(const Logger&) = delete;
    Logger& operator =(const Logger&) = delete;

    //Access point for instance
    static Logger* getInstance()
    {
        if (instance == nullptr)
        {
            instance = new Logger();
        }
        return instance;
    }

    void log(const string& message)
    {
        cout << "[LOG]: " << message << endl;
    }
};

// Initializing static member
Logger* Logger::instance = nullptr;

// Here if you see we have initialized it outside the main()
// Static members needs a single definition in the global scope, otherwise the compiler will not know where to allocate memory for them
// If we intialize it inside main(), it end up creating a local variable, not the actual class-wide static instance

int main()
{
    Logger* logger1 = Logger::getInstance();
    Logger* logger2 = Logger::getInstance();

    logger1->log("Application started.");
    logger2->log("User logged in.");

    if (logger1 == logger2)
    {
        cout << "Only one logger instance exists." << endl;
    }

    return 0;
}

// The above is a naive approach for using Singleton Design Pattern
/*
The above breaks when we use multithreading
If two threads call getInstance() simultaneously, it can create two different loggers -> breaks Singleton

#include <mutex>
class Logger
{
private:
    static Logger* instance;
    static mutex mtx;  // lock for thread safety
    Logger() {}
public:
    Logger(const Logger&) = delete;
    Logger& operator =(const Logger&) = delete;

    static Logger* getInstance()
    {
    lock_guard<mutex> lock<mtx>; // Ensures only one thread creates it
        if (instance == nullptr)
        {
            instance = new Logger();
        }
        return instance;
    }
};

*/
