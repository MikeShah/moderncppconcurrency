// @file thread4.cpp
#include <iostream>
#include <thread>
#include <vector>

int main(){

    auto lambda=[](int x){
        std::cout << "Hello from thread!" << std::this_thread::get_id() << std::endl;
        std::cout << "Argument passed in: " << x << std::endl;
    };

    std::vector<std::jthread> jthreads;
    for(int i=0; i < 10; i++){
        jthreads.push_back(std::jthread(lambda, i));
    }


    std::cout << "hello from my main thread" << std::endl;
    return 0;
}
