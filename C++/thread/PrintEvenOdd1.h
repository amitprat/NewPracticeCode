#pragma once
#include "../Header.h"

class PrintEvenOdd {
    mutex m;
    condition_variable cv;

public:
    static void test() {
        vector<int> arr = { 3,1,2,5,6,7,8,10,9 };
        atomic<int> index = 0;
        PrintEvenOdd obj;

        thread t1([&] {
            obj.printEven(arr, index);
            });
        thread t2([&] {
            obj.printOdd(arr, index);
            });

        t1.join();
        t2.join();
    }

    void printEven(vector<int> arr, atomic<int>& index) {
        bool done = false;
        while (!done && index < arr.size()) {
            unique_lock lock(m);
            cv.wait(lock, [&] {return !(arr[index] & 1); });

            if (index < arr.size()) {
                cout << "Print by even thread " << arr[index++] << endl;
            }
            else { done = true; }

            lock.unlock();
            cv.notify_all();
        }
    }

    void printOdd(vector<int> arr, atomic<int>& index) {
        bool done = false;
        while (!done && index < arr.size()) {
            unique_lock lock(m);
            cv.wait(lock, [&] {return (arr[index] & 1); });

            if (index < arr.size()) {
                cout << "Print by odd thread " << arr[index++] << endl;
            }
            else { done = true; }

            lock.unlock();
            cv.notify_all();
        }
    }
};