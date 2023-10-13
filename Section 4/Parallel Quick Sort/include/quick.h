#pragma once

#include <iostream>
#include <list>
#include <algorithm>
#include <future>
#include <stdlib.h>
#include <chrono>
#include <time.h>

using namespace std;

const size_t testSize = 1000000;
const int iterationCount = 5;

template <typename T>
list<T> quickSort(list<T> input)
{
    if (input.size() < 2)
    {
        return input;
    }

    list<T> result;
    result.splice(result.begin(), input, input.begin());
    T pivot = *result.begin();

    auto dividePoint = partition(input.begin(), input.end(),
                                 [&pivot](T const &t)
                                 {
                                     return t < pivot;
                                 });
    list<T> lowerList;
    lowerList.splice(lowerList.end(), input, input.begin(), dividePoint);

    list<T> newLower(quickSort(move(lowerList)));
    list<T> newUpper(quickSort(move(input)));

    result.splice(result.begin(), newLower);
    result.splice(result.end(), newUpper);

    return result;
}

template <typename T>
list<T> parallelQuickSort(list<T> input)
{
    if (input.size() < 2)
    {
        return input;
    }

    list<T> result;
    result.splice(result.begin(), input, input.begin());
    T pivot = *result.begin();

    auto dividePoint = partition(input.begin(), input.end(),
                                 [&pivot](T const &t)
                                 {
                                     return t < pivot;
                                 });
    list<T> lowerList;
    lowerList.splice(lowerList.end(), input, input.begin(), dividePoint);

    future<list<T>> newLower = async(launch::async | launch::deferred, &parallelQuickSort<T>, move(lowerList));
    list<T> newUpper(quickSort(move(input)));

    result.splice(result.begin(), newLower.get());
    result.splice(result.end(), newUpper);

    return result;
}

void print_results(const char *const tag, const list<int> &sorted, chrono::high_resolution_clock::time_point startTime, chrono::high_resolution_clock::time_point endTime)
{
    cout << tag << ": Lowest: " << sorted.front() << " Highest: " << sorted.back() << " Time: " << chrono::duration_cast<chrono::duration<double, milli>>(endTime - startTime).count() << endl;
}

void run()
{
    srand(time(0));

    cout << "Testing with " << testSize << " integers..." << endl;
    list<int> li(testSize, 1);
    for (auto &i : li)
    {
        i = static_cast<int>(rand());
    }

    for (int i = 0; i < iterationCount; i++)
    {
        const auto startTime = chrono::high_resolution_clock::now();
        list<int> sorted = quickSort(li);
        const auto endTime = chrono::high_resolution_clock::now();
        print_results("Serial Quick Sort ", sorted, startTime, endTime);
    }

    for (int i = 0; i < iterationCount; i++)
    {
        const auto startTime = chrono::high_resolution_clock::now();
        list<int> sorted = parallelQuickSort(li);
        const auto endTime = chrono::high_resolution_clock::now();
        print_results("Parallel Quick Sort ", sorted, startTime, endTime);
    }
}