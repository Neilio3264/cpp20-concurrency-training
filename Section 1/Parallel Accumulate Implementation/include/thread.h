#pragma once

#include <string>
#include <numeric>
#include <functional>
#include <vector>
#include <iostream>
#include "common.h"

#define MIN_BLOCK_SIZE 1000

using namespace std;

template <typename iterator, typename T>
void accumulate(iterator start, iterator end, T &ref)
{
    ref = accumulate(start, end, 0);
}

template <typename iterator, typename T>
T parallelAccumulate(iterator start, iterator end, T &ref)
{
    int inputSize = distance(start, end);
    int allowedThreads = (inputSize) / MIN_BLOCK_SIZE;

    int allowedThreadsByHardware = thread::hardware_concurrency();

    int numThreads = min(allowedThreads, allowedThreadsByHardware);

    int blockSize = (inputSize + 1) / numThreads;

    vector<T> results(numThreads);
    vector<thread> threads(numThreads - 1);

    iterator last;

    for (int i = 0; i < numThreads - 1; i++)
    {
        last = start;
        advance(last, blockSize);
        threads[i] = thread(accumulate<iterator, T>, start, last, std::ref(results[i]));
        start = last;
    }

    results[numThreads - 1] = std::accumulate(start, end, 0);

    for_each(threads.begin(), threads.end(), mem_fn(&thread::join));

    return std::accumulate(results.begin(), results.end(), ref);
}

void run()
{
    const int size = 16000;
    int *array = new int[size];
    int ref = 0;

    srand(0);

    for (size_t i = 0; i < size; i++)
    {
        array[i] = rand() % 10;
    }

    int value = parallelAccumulate<int *, int>(array, array + size, ref);
    cout << "Accumulated value: " << value << endl;

    delete[] array;
    array = nullptr;
}