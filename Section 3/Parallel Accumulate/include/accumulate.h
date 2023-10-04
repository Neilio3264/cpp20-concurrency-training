#pragma once

#include <iostream>
#include <thread>
#include <vector>
#include <future>
#include <numeric>

#define MIN_BLOCK_SIZE 1000

using namespace std;

template <typename iterator>
int accumulate(iterator begin, iterator end)
{
    long length = distance(begin, end);

    if (length < MIN_BLOCK_SIZE)
    {
        cout << this_thread::get_id() << endl;
        return accumulate(begin, end, 0);
    }

    iterator mid = begin;
    advance(mid, (length + 1) / 2);

    future<int> f1 = async(launch::deferred | launch::async, accumulate<iterator>, mid, end);
    auto sum = accumulate(begin, mid);
    return sum + f1.get();
}

void run()
{
    vector<int> v(10000, 1);
    cout << "The sum is " << accumulate(v.begin(), v.end()) << '\n';
    cout << endl;
}