#include <iostream>
#include <memory>

#include <DawnNet/pch.hpp>
#include <DawnNet/Concurrency/ThreadManager.hpp>


int main(int argc, char* argv[])
{


    for(int i = 0; i < 4; i++)
    {
        DawnNet::GThreadManager->Launch([](){

        });
    }

    
    DawnNet::GThreadManager->Join();       
}