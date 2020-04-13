// Copyright 2018 Your Name <your_email>

#include <iostream>
#include <header.h>
#include <thread>
#include <vector>

int main() {
    srand(time(NULL));

    int M = std::thread::hardware_concurrency();

    vector <thread> vector_of_thread;

    log_fileANDconsole();
    for ( int i = 0; i < (M-1); i++ ){
        vector_of_thread.push_back(std::thread(Start));
    }

    for ( int i = 0 ; i < (M-1); i++ ){
        vector_of_thread[i].join();
    }
    Start();

    return 0;
}
