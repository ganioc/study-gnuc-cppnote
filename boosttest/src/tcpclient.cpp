#include <iostream>
#include <boost/asio.hpp>

using namespace std;
namespace asio = boost::asio;

int main(int argc, char* argv[]){
    cout << "tcp client" << endl;

    if(argc < 3){
        cerr << "Usage: " << argv[0] << " Host port" << endl;
        exit(1);
    }

    const char *host = argv[1], *port = argv[2];

    asio::io_service service;
    asio::ip::tcp::resolver  resolver(service);

    try{
        asio::ip::tcp::resolver::query query(asio::ip::tcp::v4(),
            host, port);
        asio::ip::tcp::resolver::iterator end,
            iter = resolver.resolve(query);
        
        asio::ip::tcp::endpoint server(iter->endpoint());
        cout << "Connecting to " << server << endl;
        asio::ip::tcp::socket socket(service, asio::ip::tcp::v4());

        socket.connect(server);
        string message = "Hello from client";
        asio::write(socket, asio::buffer(message.c_str(), message.size()));
        socket.shutdown(asio::ip::tcp::socket::shutdown_send);

        char msg[BUFSIZ];
        boost::system::error_code ec;
        size_t sz = asio::read(socket,
            asio::buffer(msg, BUFSIZ), ec);
        if(!ec || ec == asio::error::eof){
            msg[sz] = 0;
            cout << "Received: " << msg << endl;
        }else{
            cerr << "Error reading response from server: "
                << ec.message() << endl;
        }

    }catch(exception& e){
        cerr << e.what() << endl;
    }


    return 0;
}