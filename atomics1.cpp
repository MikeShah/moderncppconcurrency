// @file atomics.cpp
#include <iostream>
#include <thread>
#include <atomic>
#include <vector>

static std::atomic<int> shared_value= 0;

void shared_value_increment(){
    shared_value+=1;
}

int main(){

    std::vector<std::thread> threads;
    for(int i=0; i < 1000; i++){
        threads.push_back(std::thread(shared_value_increment));
    }

    for(int i=0; i < 1000; i++){
        threads[i].join(); 
    }

    std::cout << "Shared value:" << shared_value << std::endl;
    return 0;
}
