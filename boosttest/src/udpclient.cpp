#include <iostream>
#include <boost/asio.hpp>
#include <exception>

namespace asio = boost::asio;
using namespace std;

int main(int argc, char* argv[]){
    cout << "udp client" << endl;

    if(argc<3){
        cerr << "Usage: " << argv[0] << " host port" << endl;
        return 1;
    }

    asio::io_service service;
    try{
        asio::ip::udp::resolver::query query(asio::ip::udp::v4(),
            argv[1], argv[2]);
        asio::ip::udp::resolver resolver(service);

        // 完成连接
        auto iter = resolver.resolve(query);
        asio::ip::udp::endpoint endpoint = iter->endpoint();

        asio::ip::udp::socket socket(service, asio::ip::udp::v4());

        const char *msg = "Hello from client";
        socket.send_to(asio::buffer(msg, strlen(msg)), endpoint);
        char buffer[256];
        size_t recvd = socket.receive_from(asio::buffer(buffer, sizeof(buffer)), endpoint);

        buffer[recvd] = 0;
        cout << "Received " << buffer << " from "
            << endpoint.address() << ':' << endpoint.port()
            << endl;

    }catch(exception& e){
        cerr << e.what() << endl;
    }

    return 0;
}