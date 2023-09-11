#pragma once

#include <iostream>
#include <mutex>
#include <string>
#include <thread>
#include <chrono>

using namespace std;

class BankAccount
{
private:
    double balance;
    string name;
    mutex m;

public:
    BankAccount(){};
    BankAccount(double _balance, string _name) : balance(_balance), name(_name) {}

    BankAccount(BankAccount &const) = delete;
    BankAccount &operator=(BankAccount &const) = delete;

    void withdraw(double amount)
    {
        lock_guard<mutex> lock(m);
        balance -= amount;
    }

    void deposit(double amount)
    {
        lock_guard<mutex> lock(m);
        balance += amount;
    }

    void transfer(BankAccount &from, BankAccount &to, double amount)
    {
        lock_guard<mutex> lock_1(from.m);
        cout << "lock for " << from.name << " account acquired by " << this_thread::get_id() << endl;
        this_thread::sleep_for(chrono::milliseconds(1000));

        cout << "waiting to acquire lock for " << to.name << " account by " << this_thread::get_id() << endl;
        lock_guard<mutex> lock_2(to.m);

        from.balance -= amount;
        to.balance += amount;
        cout << "transfer to - " << to.name << "  from - " << from.name << endl;
    }
};

void run()
{
    BankAccount account;

    BankAccount account1(1000, "James");
    BankAccount account2(2000, "Matthew");

    thread thread1(&BankAccount::transfer, &account, ref(account1), ref(account2), 500);
    this_thread::sleep_for(chrono::milliseconds(100));
    thread thread2(&BankAccount::transfer, &account, ref(account2), ref(account1), 200);

    thread1.join();
    thread2.join();
}