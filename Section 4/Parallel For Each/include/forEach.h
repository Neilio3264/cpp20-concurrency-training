#pragma once

#include <iostream>
#include <future>
#include <execution>
#include <algorithm>
#include "common.h"

using namespace std;

const unsigned long minPerThread = 25;
const size_t testSize = 100000000;
const int iterationCount = 5;

template <typename Iterator, typename Func>
void parallelForEach(Iterator begin, Iterator end, Func f)
{
    const unsigned long length = distance(begin, end);
    if (!length)
        return;

    const unsigned long maxThreads = (length + minPerThread - 1) / minPerThread;

    const unsigned long hardwareThreadCount = thread::hardware_concurrency();
    const unsigned long numThreads = min(hardwareThreadCount != 0 ? hardwareThreadCount : 2, maxThreads);
    const unsigned long blockSize = length / numThreads;

    vector<future<void>> futures(numThreads - 1);
    vector<thread> threads(numThreads - 1);
    JoinThread guard(threads);

    Iterator blockStart = begin;
    for (unsigned long i = 0; i < (numThreads - 1); i++)
    {
        Iterator blockEnd = blockStart;
        advance(blockStart, blockSize);

        packaged_task<void(void)> task(
            [=]()
            {
                for_each(blockStart, blockEnd, f);
            });

        futures[i] = task.get_future();
        threads[i] = thread(move(task));

        blockStart = blockEnd;
    }

    for_each(blockStart, end, f);
    for (unsigned long i = 0; i < (numThreads - 1); i++)
        futures[i].get();
}

template <typename Iterator, typename Func>
void parallelForEachAsync(Iterator begin, Iterator end, Func f)
{
    const unsigned long length = distance(begin, end);
    if (!length)
        return;

    if (length < 2 * minPerThread)
        for_each(begin, end, f);
    else
    {
        const Iterator mid = begin + length / 2;
        future<void> firstHalf = async(&parallelForEachAsync<Iterator, Func>, begin, mid, f);
        parallelForEachAsync(mid, end, f);
        firstHalf.get();
    }
}

void print_results(const char *const tag, chrono::high_resolution_clock::time_point startTime, chrono::high_resolution_clock::time_point endTime)
{
    cout << tag << ":  Time: " << chrono::duration_cast<chrono::duration<double, milli>>(endTime - startTime).count() << endl;
}

void run()
{
    srand(time(0));

    cout << "Testing with " << testSize << " integers..." << endl;
    vector<int> ints(testSize, 1);

    auto func = [](const int &n)
    {
        int sum = 0;
        for (auto i = 0; i < 100000; i++)
        {
            sum += n * (i - 499);
        }
    };

    for (int i = 0; i < iterationCount; i++)
    {
        const auto startTime = chrono::high_resolution_clock::now();
        for_each(ints.cbegin(), ints.cend(), func);
        const auto endTime = chrono::high_resolution_clock::now();
        print_results("STL                  ", startTime, endTime);
    }

    for (int i = 0; i < iterationCount; i++)
    {
        const auto startTime = chrono::high_resolution_clock::now();
        for_each(execution::seq, ints.cbegin(), ints.cend(), func);
        const auto endTime = chrono::high_resolution_clock::now();
        print_results("STL-seq              ", startTime, endTime);
    }

    for (int i = 0; i < iterationCount; i++)
    {
        const auto startTime = chrono::high_resolution_clock::now();
        for_each(execution::par, ints.cbegin(), ints.cend(), func);
        const auto endTime = chrono::high_resolution_clock::now();
        print_results("STL-par              ", startTime, endTime);
    }

    for (int i = 0; i < iterationCount; i++)
    {
        const auto startTime = chrono::high_resolution_clock::now();
        parallelForEach(ints.cbegin(), ints.cend(), func);
        const auto endTime = chrono::high_resolution_clock::now();
        print_results("PAR-pt               ", startTime, endTime);
    }

    for (int i = 0; i < iterationCount; i++)
    {
        const auto startTime = chrono::high_resolution_clock::now();
        parallelForEachAsync(ints.cbegin(), ints.cend(), func);
        const auto endTime = chrono::high_resolution_clock::now();
        print_results("PAR-async            ", startTime, endTime);
    }
}