#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>

std::mutex g_lock;

void job1(){
    g_lock.lock();
        std::cout << "job1 is executed" << std::endl;
    g_lock.unlock();
}

void job2(){
    if(g_lock.try_lock()){
        std::cout << "job2 is executed" << std::endl;
        g_lock.unlock();
    }else{
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(5s);
        if(g_lock.try_lock()){
            std::cout << "job2 exected on 2nd try\n";
            g_lock.unlock();
        }
    }
}

int main(){

    std::thread thread1(job1);
    std::thread thread2(job2);

    thread1.join();
    thread2.join();

    return 0;
}
