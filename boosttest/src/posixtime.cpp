#include <iostream>
#include <boost/date_time.hpp>
#include <ctime>
#include <boost/chrono/chrono.hpp>
#include <boost/chrono/chrono_io.hpp>
#include <boost/timer/timer.hpp>

using namespace std;

namespace greg = boost::gregorian;
namespace pt = boost::posix_time;
namespace dt = boost::date_time;

namespace chro = boost::chrono;

void testChrono(void){
    cout<< "Test Chrono lib" << endl;
    chro::duration<int64_t,boost::ratio<1,100>> csec(10);
    cout << csec.count() << endl;
    cout << csec << endl;

    chro::seconds sec(10);
    chro::milliseconds sum = sec + chro::milliseconds(20);

    chro::milliseconds msec = sec;

    cout << "msec: " << msec << endl;

    chro::seconds sec2 = chro::duration_cast<chro::seconds>(sum);
    
    cout << "sec2: " << sec2 << endl;

    typedef chrono::system_clock::period tick_period;
    cout << boost::ratio_string<tick_period, char>::prefix()
        << " seconds" << endl;
    
    chro::system_clock::time_point epoch;
    chro::system_clock::time_point now = chro::system_clock::now();

    cout << epoch << endl;
    cout << chro::time_point_cast<chro::hours>(now) << endl;
}
void testCPUTime(void){
    cout << endl << "Test CPU Time" << endl;
    boost::timer::cpu_timer  timer;


    timer.stop();

    cout << "running time: " << timer.format() << endl;
}
int main(){
    cout << "Test Posix Time" << endl;

    pt::ptime pt;
    cout << pt.is_not_a_date_time() << endl;

    pt::ptime now1 = pt::second_clock::universal_time();
    pt::ptime now2 = pt::from_time_t(std::time(0));

    cout << "now2: " << now2 << endl;

    // Construct from strings
    // Create time points using durations
    pt::ptime pt1(greg::day_clock::universal_day(),
        pt::hours(10) + pt::minutes(42)
        + pt::seconds(20) + pt::microseconds(30));
    cout<< "pt1: " << pt1 << endl;

    // compute durations
    pt::time_duration dur = now1 - pt1;
    cout << "dur: " << dur << endl;
    cout << "dur in us: " << dur.total_microseconds() << endl;

    pt::ptime pt2(greg::day_clock::universal_day()),
        pt3 = pt::time_from_string("2015-01-28 10:00:31.83"),
        pt4 = pt::from_iso_string("20150128T151200");
    
    cout << pt2 << endl << to_iso_string(pt3) << endl
        << to_simple_string(pt4) << endl;

    cout << "time resolution: " << pt::time_duration::resolution() << endl;
    cout << "time fractional digits: " << pt::time_duration::num_fractional_digits() << endl;
    cout << "time ticks /s: " << pt::time_duration::ticks_per_second() << endl;


    pt::ptime cnow1 = pt::second_clock::local_time();
    pt::time_period starts_now(cnow1, pt::hours(2));

    cout << "starts now length: " << starts_now.length() << endl;
    auto later1 = cnow1 + pt::hours(1);
    pt::time_period starts_in_1(later1, pt::hours(3));

    cout <<"starts in 1: " << starts_in_1.length() << endl;

    // iterator
    pt::ptime now = pt::second_clock::local_time();
    pt::ptime start_of_day(greg::day_clock::local_day());

    for(pt::time_iterator iter(start_of_day, 
        pt::hours(1)); iter< now; ++iter){
            cout << *iter << endl;
        }
    
    testChrono();

    testCPUTime();

    return 0;
}