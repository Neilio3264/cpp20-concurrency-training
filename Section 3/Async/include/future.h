#pragma once

#include <iostream>
#include <future>

using namespace std;

int universeAge() { return 5000; }

void otherCalculations()
{
    cout << "Doing other stuff " << endl;
}

void run()
{
    future<int> answer = async(universeAge);
    otherCalculations();
    cout << "The answer is " << answer.get() << endl;
}