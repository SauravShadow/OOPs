// Strategy Pattern
/*
- It lets one define a family of algorithms, encapsulate each one and make them interchangeable.
- It makes the algorithm pluggable at runtime and eliminate if-else chains when one need to switch behaviors.

//Don't you think it is little like Liskov Substitution Principle just that it has fliexible runtime behavior.

Key-Components:
- Strategy Interface -> Defines a common method
- Concrete Strategies -> Implement the different version of algorithm
- Context Class -> Uses a strategy* reference and delegates the work to it.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include <utility> // for std::move

using namespace std;

// Strategy interface
class SortStrategy {
public:
    virtual void sort(vector<int>& data) = 0;
    virtual ~SortStrategy() = default;
};

// Concrete Strategy 1: Ascending
class AscendingSort : public SortStrategy {
public:
    void sort(vector<int>& data) override {
        std::sort(data.begin(), data.end());
    }
};

// Concrete Strategy 2: Descending
class DescendingSort : public SortStrategy {
public:
    void sort(vector<int>& data) override {
        std::sort(data.begin(), data.end(), greater<int>());
    }
};

// Concrete Strategy 3: Sort by absolute value
class AbsoluteSort : public SortStrategy {
public:
    void sort(vector<int>& data) override {
        std::sort(data.begin(), data.end(),
                  [](int a, int b) { return abs(a) < abs(b); });
    }
};

// Context
class SortContext {
private:
    unique_ptr<SortStrategy> strategy;
public:
    void setStrategy(unique_ptr<SortStrategy> s) {
        strategy = std::move(s);
    }

    void sortData(vector<int>& data) {
        if (strategy)
            strategy->sort(data);
        else
            cout << "No sorting strategy set!\n";
    }
};

// Utility: print vector
void printVec(const vector<int>& v) {
    for (int x : v) cout << x << " ";
    cout << "\n";
}

int main() {
    vector<int> numbers = {5, -1, 3, -7, 2};

    SortContext ctx;

    ctx.setStrategy(make_unique<AscendingSort>());
    ctx.sortData(numbers);
    cout << "Ascending: "; printVec(numbers);

    numbers = {5, -1, 3, -7, 2};
    ctx.setStrategy(make_unique<DescendingSort>());
    ctx.sortData(numbers);
    cout << "Descending: "; printVec(numbers);

    numbers = {5, -1, 3, -7, 2};
    ctx.setStrategy(make_unique<AbsoluteSort>());
    ctx.sortData(numbers);
    cout << "Absolute: "; printVec(numbers);

    return 0;
}
