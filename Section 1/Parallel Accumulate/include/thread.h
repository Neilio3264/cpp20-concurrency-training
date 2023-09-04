#pragma once

#include <string>
#include <numeric>
#include <vector>
#include <iostream>
#include "common.h"

using namespace std;

void sequentialAccumulateTest()
{
    vector<int> v{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int sum = accumulate(v.begin(), v.end(), 0);

    int product = accumulate(v.begin(), v.end(), 1, multiplies<int>());

    auto dash = [](string a, int &b)
    {
        return move(a) + "-" + to_string(b);
    };

    string s = accumulate(next(v.begin()), v.end(), to_string(v[0]), dash);

    cout << "sum = " << sum << endl;
    cout << "product = " << product << endl;
    cout << "dash = " << s << endl;
}

void run()
{
    thread thread1(sequentialAccumulateTest);
    ThreadGuard tg1(thread1);
}