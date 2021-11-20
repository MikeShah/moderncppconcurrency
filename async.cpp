// @file async.cpp
#include <iostream>
#include <future>

int square(int x){
    return x*x;
}

int main(){

    std::future<int> asyncFunction = std::async(&square,12);
    for(int i=0; i< 10; i++){
        std::cout << square(i) << std::endl;
    }

    // We are blocked at the 'get()' operation, until our
    // result has computed
    int result = asyncFunction.get();

    std::cout << "result is: " << result << std::endl;

    return 0;
}
