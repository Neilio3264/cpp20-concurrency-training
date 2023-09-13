#pragma once

#include <iostream>
#include <mutex>
#include <thread>
#include <string>
#include <chrono>

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

bool keepDriving()
{
}

void keepAwake()
{
}

void setAlarm()
{
}

void run()
{
}