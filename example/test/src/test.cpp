
#include <iostream>
#include "packet/test.pb.h"

#define ASIO_STANDALONE
#include <boost/asio.hpp>
#include <boost/asio/ts/buffer.hpp>
#include <boost/asio/ts/internet.hpp>
#include <boost/bind/bind.hpp>

#include <DawnNet/pch.hpp>
#include <DawnNet/Concurrency/ThreadManager.hpp>

using namespace std;
using namespace DawnNet;

int main()
{   
    Vector<BYTE> buffer(0x10000);
    for(int i = 0; i < 10; i++)
    {
        buffer[i] = i + 1;
    }

    BYTE* ptr = &buffer[0];
    for(int i = 0; i < 3; i++)
    {
        // cout << reinterpret_cast<uint64>(ptr) << ", ";
        cout << hex << reinterpret_cast<uint64>(ptr) << ", ";
        cout << dec << static_cast<int>(*ptr) << '\n';
        ptr++;
    }

    // GOOGLE_PROTOBUF_VERIFY_VERSION;

    // tutorial::AddressBook address_book;

    // auto pkt = address_book.add_person();

    // pkt->set_name("Hi");
    // pkt->set_id(312);


    // const uint16_t dataSize = static_cast<uint16_t>(pkt->ByteSizeLong());

    // cout << "Data size: " << dataSize << '\n';


    // int a = 0;
    // for(int i = 0; i < 4; i++)
    // {
    //     std::cout << DawnNet::GThreadManager << '\n';
    //     DawnNet::GThreadManager->Launch([&a]() {
            
    //         for(int j = 0; j < 1000; j++)
    //         {
    //             a += 1;
    //         }

    //     });
    // }

    // DawnNet::GThreadManager->Join();

    // cout << "A is " << a << '\n';

    return 0;
}