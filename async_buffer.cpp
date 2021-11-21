// @file async_buffer.cpp
#include <iostream>
#include <future>
#include <thread>
#include <chrono>

bool bufferedFileLoader(){
    size_t bytesLoaded = 0;
    while(bytesLoaded < 20000){
        std::cout << "thread: loading file..." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
        bytesLoaded += 1000;
    }
    return true;
}

int main(){

    std::future<bool> backgroundThread = std::async(std::launch::async,
                                                    bufferedFileLoader);

    std::future_status status;
    // Our main program loop
    while(true){
        std::cout << "Main thread is running" << std::endl;
        // artificial sleep for our program
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        status = backgroundThread.wait_for(std::chrono::milliseconds(1));
        // If our data is ready, that is, our background
        // thread has completed
        if(status == std::future_status::ready){
            std::cout << "Our data is ready..." << std::endl;
            break;
        }

    }

    std::cout << "Program is complete" << std::endl;

    return 0;
}
