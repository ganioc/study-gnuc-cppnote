#include <iostream>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/date_time.hpp>
#include <memory>

#define PRINT_ARGS(msg) do{ \
    boost::lock_guard<boost::mutex> lg(mtx); \
    cout << '[' << boost::this_thread::get_id() \
        << "] " << msg << endl; \
}while(0)


#define PRINT_ARGS2(msg) do{ \
    boost::lock_guard<boost::mutex> lg(mtx2); \
    cout << '[' << boost::this_thread::get_id() \
        << "] " << msg << endl; \
}while(0)

using namespace std;
namespace asio = boost::asio;



void testDispatch(){
    cout << "Test dispatch" << endl;
    asio::io_service service;

    service.dispatch([]{ cout << "hello again" << endl;});

    service.post(
        [&service]{
            cout << "Hello world post" << endl;
            service.post([]{
                cout << "Hello inside" << endl;
            });
        }
    );

    service.post([&service]{
        cout << "Hallo end task" << endl;
    });

    service.run();
}
// void testConcurrent(){
//     cout << "Test Concurrent threads" << endl;
//     asio::io_service service;
//     boost::mutex mtx;

//     for(int i = 0; i< 20; i++){
//         service.post([i,&mtx]{
//             PRINT_ARGS("Handler[" << i << "] ");
//             boost::this_thread::sleep(
//                 boost::posix_time::seconds(1)
//             );
//         });
//     }

//     boost::thread_group pool;
//     for(int i =0; i< 10; i++){
//         pool.create_thread([&service](){
//             service.run();
//         });
//     }

//     pool.join_all();
// }
typedef unique_ptr<asio::io_service::work> work_ptr;
void testWork(){
    cout << "Test work" << endl;
    asio::io_service service;

    // keep the workers occupied
    work_ptr work(new asio::io_service::work(service));
    boost::mutex mtx;

    // set up the worker threads in a thread group
    boost::thread_group workers;
    for(int i=0; i< 3; i++){
        workers.create_thread([&service,&work, &mtx](){
            PRINT_ARGS("Starting worker thread ");
            service.run();
            PRINT_ARGS("Worker thread done");
        });
    }

    // Post work
    for(int i =0; i< 20; i++){
        service.post(
            [&service,&mtx](){
                PRINT_ARGS("hello world");
                service.post([&mtx](){
                    PRINT_ARGS("Hola, mundo!");
                });
            }
        );
    }

    work.reset(); // destroy work object, signals end of work
    workers.join_all(); // wait for all worker threads to finish


}
void testStrand(void){
    cout << endl    
        << "Test Strand" << endl;
    
    srand(time(0));
    asio::io_service service;
    asio::io_service::strand strand(service);
    boost::mutex mtx;
    size_t regular = 0, on_strand = 0;

    auto workFuncStrand = [&mtx, &on_strand]{
        ++on_strand;
        PRINT_ARGS(on_strand << ". Hello from strand!");
        boost::this_thread::sleep(
            boost::posix_time::seconds(2)
        );
    };

    auto workFunc = [&mtx, &regular]{
        PRINT_ARGS(++regular << ". Hello world!");
        boost::this_thread::sleep(
            boost::posix_time::seconds(2)
        );
    };

    // Post work
    for(int i = 0; i< 15; ++i){
        if(rand()%2 == 0 ){
            service.post(strand.wrap(workFuncStrand));
        }else{
            service.post(workFunc);
        }
    }

    // set up the worker threads in a thread group
    boost::thread_group workers;
    for(int i = 0; i< 3; i++){
        workers.create_thread([&service, &mtx](){
            PRINT_ARGS("Starting worker thread");
            service.run();
            PRINT_ARGS("Worker thread done");
        });
    }
    workers.join_all();
    
}
int main(void){
    cout << "Test asio lib" << endl;

    asio::io_service service;

    service.post([]{
        cout << "Hello Asio" << endl;
    });

    cout << "Greetings: " << endl;
    service.run();

    testDispatch();

    // testConcurrent();

    testWork();

    testStrand();

    return 0;
}