#include <iostream>
#include <vector>
#include "test_code.cpp"
using namespace std;


//my main that will be used to test the previous codes, with input sizes such as 1000, 10000, 100000
int main()
{
    srand(time(0));

    vector<int> sizes = { 1000, 10000, 100000};
    vector <int> thresholds = {5, 10, 20};

    for (int threshold : thresholds)
    {
        for (int size : sizes)
        {
            testSorting(size, threhold)

        }
    }
    return 0;
}