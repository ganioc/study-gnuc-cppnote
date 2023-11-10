#include <iostream>
#include <boost/asio.hpp>
#include <exception>

namespace asio = boost::asio;
using namespace std;

int main(void){
    cout << "udp server" << endl;

    const unsigned short port = 55000;
    const string greet("Hello, world!");

    asio::io_service service;
    asio::ip::udp::endpoint endpoint(asio::ip::udp::v4(), port);
    asio::ip::udp::socket socket(service, endpoint);
    asio::ip::udp::endpoint ep;

    while(true)try {
        char msg[256];
        auto recvd = socket.receive_from(asio::buffer(msg,sizeof(msg)), ep);
        msg[recvd] = 0;
        cout << "Received: [" << msg << "] from ["
            << ep << "]" << endl;
        socket.send_to(asio::buffer(greet.c_str(), greet.size()),
            ep);
        socket.send_to(asio::buffer(msg, strlen(msg)), ep);
    }catch(exception& e){
        cout << e.what() << endl;
    }

    return 0;
}