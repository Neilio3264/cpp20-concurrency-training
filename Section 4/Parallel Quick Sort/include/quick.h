#pragma once

#include <iostream>
#include <list>
#include <algorithm>
#include <future>

using namespace std;

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

void run()
{
    int array[] = {8, 3, 12, 9, 5, 6, 11, 1, 13, 2};
}