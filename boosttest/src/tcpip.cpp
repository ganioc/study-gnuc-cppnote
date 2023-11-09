#include <iostream>

#include <boost/asio.hpp>
#include <boost/date_time.hpp>
#include <boost/bind.hpp>
#include <boost/asio/spawn.hpp>
#include <cassert>
#include <vector>


using namespace std;
namespace asio = boost::asio;
namespace sys = boost::system;

using namespace asio::ip;

void printAddrProperties(const address& addr){
    cout << "\n\n" << addr << ": ";

    if(addr.is_v4()){
        cout << "netmask=" << address_v4::netmask(addr.to_v4());
    }else if(addr.is_v6()){
        cout << "v6 address";
    }
}

void testSequence(){
    cout << "\n\nTest Sequence" << endl;
    srand(time(nullptr));
    vector<char> v1(10);
    char a2[10];

    vector<asio::mutable_buffer> bufseq(2);

    bufseq.push_back(asio::mutable_buffer(v1.data(),
        v1.capacity()));
    bufseq.push_back(asio::mutable_buffer(a2,sizeof(a2)));

    for(auto cur = asio::buffers_begin(bufseq),
        end = asio::buffers_end(bufseq);
        cur != end; cur++){
            *cur = 'a' + rand()%26;
        }
    cout << "Size: " << asio::buffer_size(bufseq) << endl;

    string s1(v1.begin(), v1.end());
    string s2(a2, a2 + sizeof(a2));

    cout << s1 << endl << s2 << endl;
}
void testDeadlineTimer(){
    asio::io_service service;
    asio::deadline_timer  timer(service);

    long secs = 5;
    cout << "Waiting for " << secs << " seconds ..."
        << flush;
    timer.expires_from_now(boost::posix_time::seconds(secs));

    timer.wait();

    cout << "done" << endl;
}
void on_timer_expiry(const boost::system::error_code& ec){
    if(ec){
        cout << "error occurred while waiting" << endl;
    }else{
        cout << "Timer expired" << endl;
    }
}
void testTimerExpiry(){
    asio::io_service service;
    asio::deadline_timer timer(service);

    long secs = 3;
    timer.expires_from_now(boost::posix_time::seconds(secs));

    cout << "Before calling deadline_timer::async_wait" << endl;
    timer.async_wait(on_timer_expiry);
    cout << "After calling deadline_timer::async_wait" << endl;

    service.run();
}
void print_world(const boost::system::error_code& ec){
    cout << "world!" << endl;
}
void print_hello( asio::deadline_timer& timer,
    const boost::system::error_code& ec){
    cout << "Hello, " <<flush;
    timer.expires_from_now(boost::posix_time::seconds(10));
    timer.async_wait(print_world);
}
void testAsyncWait(void){
    asio::io_service service;
    asio::deadline_timer timer(service);
    timer.expires_from_now(boost::posix_time::seconds(3));

    timer.async_wait(boost::bind(print_hello,boost::ref(timer),
        ::_1));
    service.run();
}
void wait_and_print(asio::yield_context yield,
    asio::io_service& service){
    asio::deadline_timer timer(service);

    timer.expires_from_now(boost::posix_time::seconds(5));
    timer.async_wait(yield);
    cout << "Hello, " << flush;
    timer.expires_from_now(boost::posix_time::seconds(5));
    timer.async_wait(yield);
    cout << "world!" << endl;
}
void testCoroutine(){
    cout << "\nTest Coroutine" << endl;
    asio::io_service service;
    asio::spawn(service,
        boost::bind(wait_and_print, ::_1,
        boost::ref(service)));
    service.run();
}
int main(){
    cout << "Test TCP IP" << endl;
    sys::error_code ec;
    vector<address> addresses;

    vector<const char*> addr_strings{
        "127.0.0.1",
        "10.28.25.62",
        "137.2.33.19",
        "223.21.201.30",
        "232.28.25.62",
        "140.28.25.62/22"
    };

    addresses.push_back(address_v4());
    addresses.push_back(address_v4::any());

    for(const auto& v4str: addr_strings){
        address_v4 addr = address_v4::from_string(v4str,ec);
        if(!ec){
            addresses.push_back(addr);
        }
    }

    for(const address& addr1: addresses){
        printAddrProperties(addr1);
    }

    testSequence();

    testDeadlineTimer();

    testTimerExpiry();

    testAsyncWait();

    testCoroutine();

    return 0;
}