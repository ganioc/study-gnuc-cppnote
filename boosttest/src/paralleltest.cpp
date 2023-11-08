#define BOOST_THREAD_PROVIDES_FUTURE

#include <iostream>
#include <boost/thread.hpp>
#include <boost/chrono/duration.hpp>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <boost/move/move.hpp>
#include <boost/filesystem.hpp>
#include <boost/thread/future.hpp>
#include <boost/chrono.hpp>
#include <ctime>
#include <cassert>
#include <cstdlib>
#include <boost/thread/mutex.hpp>
#include <set>
#include <boost/thread/condition_variable.hpp>
#include <boost/array.hpp>

using namespace std;

typedef vector<string> strvec;

void printGreets(const strvec &greets)
{
    for (const auto &greet : greets)
    {
        cout << greet << endl;
    }
}

void doStuff(const string &name)
{
    stringstream sout;
    sout << "[name=" << name << "]"
         << "[id=" << boost::this_thread::get_id() << "]"
         << " doing work" << endl;
    cout << sout.str();
    boost::this_thread::sleep_for(boost::chrono::seconds(2));
}

void testFuture()
{
    cout << "Test Future" << endl;
    boost::promise<void> promise;
    boost::future<void> future = promise.get_future();

    cout << "Main thread id="
         << boost::this_thread::get_id() << endl;

    boost::thread thr([&promise]
                      {
        srand(time(0));
        int secs = 10 + rand() % 10;
        cout << "Tread " << boost::this_thread::get_id()
            << " sleeping for "
            << secs << " seconds" << endl;
        boost::this_thread::sleep_for(
            boost::chrono::seconds(secs)
        );
        promise.set_value(); });
    size_t timeout_count = 0;
    size_t secs = 2;

    while (future.wait_for(boost::chrono::seconds(secs)) == boost::future_status::timeout)
    {
        cout << "Main thread timed out" << endl;
        ++timeout_count;
    }
    cout << "future is ready: " << future.is_ready() << endl;

    cout << "Timed out for " << timeout_count * secs << " seconds" << endl;

    thr.join();
}
void testRace()
{
    int x = 0;
    const int max = 1000000;
    boost::mutex mtx;

    auto thrFunc = [&x, &mtx]()
    {
        for (int i = 0; i < max; ++i)
        {
            mtx.lock();
            ++x;
            mtx.unlock();
        }
    };
    boost::thread t1(thrFunc);
    boost::thread t2(thrFunc);
    t1.join();
    t2.join();

    cout << "Value of x: " << x << endl;
}
void testLockGuard()
{
    int x = 0;
    static const int max = 1000000;
    boost::mutex mtx;

    auto thrFunc = [&x, &mtx]()
    {
        for (int i = 0; i < max; i++)
        {
            boost::lock_guard<boost::mutex> lg(mtx);
            ++x;
        }
    };
    boost::thread t1(thrFunc);
    boost::thread t2(thrFunc);

    t1.join();
    t2.join();

    cout << "Value of x: " << x << endl;
}
struct Player
{
    /* data */
    int id;
    bool operator<(const Player &that) const
    {
        return id < that.id;
    }
};

void testDeadlock(void)
{
    cout << "Test Deadlock" << endl;
    set<Player> armed, unarmed;
    boost::mutex amtx, umtx;
    auto a2u = [&](int playerId)
    {
        boost::lock_guard<boost::mutex> lka(amtx);
        auto it = armed.find(Player{playerId});
        if (it != armed.end())
        {
            auto plyr = *it;
            boost::unique_lock<boost::mutex> lku(umtx);
            unarmed.insert(plyr);
            lku.unlock();
            armed.erase(it);
        }
    };
    auto u2a = [&](int playerId)
    {
        boost::lock_guard<boost::mutex> lku(umtx);
        auto it = unarmed.find(Player{playerId});
        if (it != unarmed.end())
        {
            auto plyr = *it;
            boost::unique_lock<boost::mutex> lka(amtx);
            armed.insert(plyr);
            lka.unlock();
            unarmed.erase(it);
        }
    };

    // event callback
    // void onAmmoExhausted(int playerId)
    // {
    //     boost::thread exhausted(a2u, playerId);
    //     exhausted.detach();
    // }
    // void onAmmoReplenished(int playerId)
    // {
    //     boost::thread replenished(u2a, playerId);
    //     replenished.detach();
    // }
}
template <typename T, size_t maxsize>
struct CircularQueue
{
    /* data */
    CircularQueue():head_(0), tail_(0){}

    void pop(){
        boost::unique_lock<boost::mutex> lock(qlock);
        if(size() == 0){
            canRead.wait(lock, [this]{
                return size() > 0;
            });
        }
        ++head_;
        lock.unlock();
        canWrite.notify_one();
    }
    T top(){
        boost::unique_lock<boost::mutex> lock(qlock);
        if(size() == 0){
            canRead.wait(lock,[this]{return size() > 0;});
        }
        T ret = data[head_%maxsize];
        lock.unlock();

        return ret;
    }
    void push(T&& obj){
        boost::unique_lock<boost::mutex> lock(qlock);
        if(size() == capacity()){
            canWrite.wait(lock, [this]{
                return size() < capacity();
            });
        }
        data[tail_++ % maxsize] = move(obj);
        lock.unlock();
        canRead.notify_one();
    }
    size_t head() const {return head_; }
    size_t tail() const {return tail_; }
    size_t count() const{
        boost::unique_lock<boost::mutex> lock(qlock);
        return(tail_ - head_);
    }
private:
    boost::array<T, maxsize> data;
    size_t head_, tail_;

    size_t capacity() const {return maxsize;}
    size_t size() const { return (tail_ - head_);}

    mutable boost::mutex qlock;
    mutable boost::condition_variable canRead;
    mutable boost::condition_variable canWrite;
};

void testConditionVariable(){
    cout << "Test Condition variable" << endl;
    CircularQueue<int, 200> ds;

    boost::thread producer([&ds]{
        for(int i = 0; i< 10000; i++){
            ds.push(move(i));
            cout << i << "-->"
                << " [" << ds.count() 
                << " ]" << endl;
        }
    });

    auto func = [&ds]{
        for(int i = 0; i< 2500; ++i){
            cout << "\t\t<--" << ds.top() << endl;
            ds.pop();
        }
    };

    boost::thread_group consumers;
    for(int i = 0; i< 4; ++i){
        consumers.create_thread(func);
    }
    producer.join();
    consumers.join_all();
}
int main()
{
    cout << "Test threads test" << endl;

    strvec angloSaxon{"Guten Morgen", "Godmorgen",
                      "Good morning", "goedemorgen"};
    strvec romance{"Buenos dias", "Bonjour",
                   "Bom dia", "Buongiorno"};

    boost::thread t1(printGreets, romance);

    printGreets(angloSaxon);

    cout << "t1 id: " << t1.get_id() << endl;

    t1.join();

    cout << "core nums: " << boost::thread::hardware_concurrency() << endl;

    typedef map<boost::thread::id, boost::thread> threadmap;
    threadmap tmap;

    vector<string> tnames{"thread1", "thread2",
                          "thread3", "thread4", "thread5"};
    for (auto name : tnames)
    {
        boost::thread thr(doStuff, name);
        tmap[thr.get_id()] = boost::move(thr);
    }

    for (auto &thrdEntry : tmap)
    {
        thrdEntry.second.join();
        cout << thrdEntry.first << " returned" << endl;
    }

    // testFuture();

    testRace();

    testLockGuard();

    testDeadlock();

    testConditionVariable();

    return 0;
}