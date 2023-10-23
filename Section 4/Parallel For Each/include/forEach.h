#pragma once

#include <iostream>
#include <future>
#include <execution>
#include <algorithm>
#include "common.h"

using namespace std;

const unsigned long minPerThread = 25;
const size_t testSize = 100;
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
    cout << "How many threads? " << numThreads << endl;
    cout << "Blocksize? " << blockSize << endl;

    vector<future<void>> futures(numThreads - 1);
    vector<thread> threads(numThreads - 1);
    JoinThread guard(threads);

    Iterator blockStart = begin;
    for (unsigned long i = 0; i <= (numThreads - 2); i++)
    {
        Iterator blockEnd = blockStart;
        advance(blockStart, blockSize);

        packaged_task<void(void)> task(
            [=]()
            {
                for_each(blockStart, blockEnd, f);
            });

        // ! Getting segmentation faults dealing with get futures and moving the future and task
        // TODO: Visit in the future
        auto fut = task.get_future();
        if (fut.valid())
        {
            cout << "not broken" << endl;
            futures[i] = move(fut);
            threads[i] = thread(std::move(task));
            cout << "thread works" << endl;
        }

        blockStart = blockEnd;
        cout << "new block start set" << endl;
    }

    cout << "Outside of threads setup" << endl;
    for_each(blockStart, end, f);
    for (unsigned long i = 0; i <= (numThreads - 2); i++)
    {
        cout << "Inside gets" << endl;
        if (futures[i].valid())
        {
            cout << "Valid get" << endl;
            futures[i].get();
        }
    }
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
        // TODO: Improve performance here
        parallelForEachAsync(mid, end, f);
        firstHalf.get();
    }
}

void print_results(const char *const tag, const int &sum, chrono::high_resolution_clock::time_point startTime, chrono::high_resolution_clock::time_point endTime)
{
    cout << tag << ": Sum: " << sum << "\t  Time: " << chrono::duration_cast<chrono::duration<double, milli>>(endTime - startTime).count() << endl;
}

void run()
{
    srand(time(0));

    cout << "Testing with " << testSize << " integers..." << endl;
    vector<int> ints(testSize, 1);

    // TODO: Have function actually access the vector information
    int sum = 0;
    auto func = [&sum](const int &n)
    {
        sum += n * static_cast<int>(rand() % 3);
    };

    for (int i = 0; i < iterationCount; i++)
    {
        const auto startTime = chrono::high_resolution_clock::now();
        for_each(ints.cbegin(), ints.cend(), func);
        const auto endTime = chrono::high_resolution_clock::now();
        print_results("STL                ", sum, startTime, endTime);
    }

    sum = 0;
    for (int i = 0; i < iterationCount; i++)
    {
        const auto startTime = chrono::high_resolution_clock::now();
        for_each(execution::seq, ints.cbegin(), ints.cend(), func);
        const auto endTime = chrono::high_resolution_clock::now();
        print_results("STL-seq            ", sum, startTime, endTime);
    }

    sum = 0;
    for (int i = 0; i < iterationCount; i++)
    {
        const auto startTime = chrono::high_resolution_clock::now();
        for_each(execution::par, ints.cbegin(), ints.cend(), func);
        const auto endTime = chrono::high_resolution_clock::now();
        print_results("STL-par            ", sum, startTime, endTime);
    }

    sum = 0;
    for (int i = 0; i < iterationCount; i++)
    {
        const auto startTime = chrono::high_resolution_clock::now();
        parallelForEach(ints.cbegin(), ints.cend(), func);
        const auto endTime = chrono::high_resolution_clock::now();
        print_results("PAR-pt             ", sum, startTime, endTime);
    }

    sum = 0;
    for (int i = 0; i < iterationCount; i++)
    {
        const auto startTime = chrono::high_resolution_clock::now();
        parallelForEachAsync(ints.cbegin(), ints.cend(), func);
        const auto endTime = chrono::high_resolution_clock::now();
        print_results("PAR-async          ", sum, startTime, endTime);
    }
}