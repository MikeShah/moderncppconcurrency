// @file cv.cpp
#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <condition_variable>

std::mutex gLock;
std::condition_variable gConditionVariable;

int main(){

    int result = 0;
    bool notified = false;

    // Reporting thread
    // Must wait on work, done by the working thread
    std::thread reporter([&]{
        std::unique_lock<std::mutex> lock(gLock);
        if(!notified){
            gConditionVariable.wait(lock);
        }
        std::cout << "Reporter, result is: " << result << std::endl;
    });

    // Working thread
    std::thread worker([&]{
        std::unique_lock<std::mutex> lock(gLock);
        // Do our work, because we have the lock
        result = 42 + 1 + 7;
        // Our work is done
        notified = true;
        std::this_thread::sleep_for(std::chrono::seconds(5));
        std::cout << "Work complete\n";
        // Wake up a thread, that is waiting, for some
        // condition to be true
        gConditionVariable.notify_one();
    });

    reporter.join();
    worker.join();

    std::cout << "Program complete" << std::endl;
    return 0;
}
