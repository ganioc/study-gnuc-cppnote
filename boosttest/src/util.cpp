#include <limits>
#include <cassert>

#include "util.h"

namespace Booutil{
void sayHello(){
    cout << "util code:" << endl;
}
boost::tuple<size_t, size_t, double> getBestTransactDays(vector<double> prices){
    double min = numeric_limits<double>::max();
    double gain = 0.0;
    double max_gain = 0.0;
    size_t min_day, max_day;
    size_t buy_day;

    for(size_t i = 0, days = prices.size(); i< days; i++ ){
        if(prices[i] < min){
            min = prices[i];
            min_day = i;
        }else if((gain = prices[i] - min) > max_gain){
            max_gain = gain;
            buy_day = min_day;
            max_day = i;
        }
    }
    return boost::make_tuple(buy_day, max_day, max_gain);

}
void testTuple(){
    boost::tuple<int, int, string> t1 = boost::make_tuple(1,20, "hello tuple");
    boost::tuple<int, int, string> t2 = boost::make_tuple(1,2, "hi tuple");
    // assert(t1 > t2);
}
void testVariant(){
    cout << "test variant =>" <<  endl;
    boost::variant<Foo, int, string> value;
    boost::variant<string, Foo, Bar> value2;

    value = 1;
    int *pi = boost::get<int>(&value);
    value = "foo";
    value = Foo(42);

    cout << "pi is: " << *pi << endl;

    boost::variant<string, int> v1;
    v1 = "1937";
    int i1;

    try{
        i1 = boost::get<int>(v1);

    }catch(exception &e){
        cerr << e.what() << endl;
    }
    int *pi2 = boost::get<int>(&v1);
    size_t index = v1.which();
    cout << "index:" << index << endl;

}



}