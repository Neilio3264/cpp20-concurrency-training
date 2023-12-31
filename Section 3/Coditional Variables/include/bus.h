#pragma once

#include <iostream>
#include <mutex>
#include <thread>
#include <string>
#include <chrono>
#include <condition_variable>

using namespace std;

/**
 * This program illustrates an example of condition variables
 * The problem modeled is as follows:
 *  - You are boarding an overnight bus to your destination x distance away
 *  - You want to ensure that you are awake at the time you need to get off
 *  - Your options to achieve this are as follows:
 *      -> Stay awake talking to the bus driver but be extremely tired upon arrival
 *      -> Set an alarm to wake up at estimated arrival time but you could wake up early or late
 *         depending on the speed the driver is able to drive
 *      -> Have someone else wake you up when you reach your destination
 */

bool arrived = false;
int distanceToDestination = 10;
int distanceCovered = 0;
condition_variable cv;
mutex m;

void keepDriving()
{
    while (distanceCovered < 50)
    {
        this_thread::sleep_for(chrono::milliseconds(1000));
        distanceCovered++;

        if (distanceCovered == distanceToDestination)
            cv.notify_one();
    }
}

void keepAwake()
{
    while (distanceCovered < distanceToDestination)
    {
        cout << "Checking if I am there yet \n";
        this_thread::sleep_for(chrono::milliseconds(1000));
    }

    cout << "Arrived at destination! Distance Covered = " << distanceCovered << endl;
}

void setAlarm()
{
    if (distanceCovered < distanceToDestination)
    {
        cout << "Taking a nap \n";
        this_thread::sleep_for(chrono::milliseconds(10000));
    }

    cout << "Arrived at destination! Distance Covered = " << distanceCovered << endl;
}

void askToWake()
{
    unique_lock<mutex> ul(m);
    // * Want to use predicate to guard against spurious wake up via OS
    cv.wait(ul, []
            { return distanceCovered == distanceToDestination; });
    cout << "Arrived at destination! Distance Covered = " << distanceCovered << endl;
}

void run()
{
    thread driverThread(keepDriving);
    thread awakeThread(keepAwake);
    thread alarmThread(setAlarm);
    thread toWakeThread(askToWake);

    toWakeThread.join();
    awakeThread.join();
    alarmThread.join();
    driverThread.join();
}