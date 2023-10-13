#include <iostream>
#include <algorithm>
#include <random>
#include <vector>
#include <chrono>
#include <execution>

using namespace std;

const size_t testSize = 10000000;
const int iterationCount = 5;

void print_results(const char *const tag, const vector<double> &sorted, chrono::high_resolution_clock::time_point startTime, chrono::high_resolution_clock::time_point endTime)
{
    cout << tag << ": Lowest: " << sorted.front() << " Highest: " << sorted.back() << " Time: " << chrono::duration_cast<chrono::duration<double, milli>>(endTime - startTime).count() << endl;
}

int main()
{
    random_device rd;

    cout << "Testing with " << testSize << " doubles..." << endl;
    vector<double> doubles(testSize);
    for (auto &d : doubles)
    {
        d = static_cast<double>(rd());
    }

    for (int i = 0; i < iterationCount; i++)
    {
        vector<double> sorted(doubles);
        const auto startTime = chrono::high_resolution_clock::now();
        sort(sorted.begin(), sorted.end());
        const auto endTime = chrono::high_resolution_clock::now();
        print_results("Serial STL ", sorted, startTime, endTime);
    }

    for (int i = 0; i < iterationCount; i++)
    {
        vector<double> sorted(doubles);
        const auto startTime = chrono::high_resolution_clock::now();
        sort(execution::par, sorted.begin(), sorted.end());
        const auto endTime = chrono::high_resolution_clock::now();
        print_results("Parallel STL ", sorted, startTime, endTime);
    }

    return EXIT_SUCCESS;
}