#include <random>
#include <algorithm>
#include <ratio>
#include <locale>

#include "study.h"

namespace Study{
    void hello(void){
        cout << "hello from study" << endl;

        vector<int> vec;
        for(int i = 0; i< 10; i++){
            vec.push_back(i);
        }
        random_device rd;
        shuffle(vec.begin(), vec.end(), rd);

        for_each(vec.begin(), vec.end(), [](int i){
            cout << i << endl;
        });
    }
    void testRatio(void){
        ratio<15,20> r;
        cout << "r :" << r.num << "/" << r.den << endl;
    }
    void testString(void){
        cout << "test string" << endl;
        // locale loc("french");
        // const time_put<char> & fac = use_facet<time_put<char>>(loc);
        // time_t t = time(nullptr);
        // tm *td = gmtime(&t);
        // ostreambuf_iterator<char> it(cout);
        // fac.put(it, cout, ' ', td, 'x', '#');
        // cout << "n";
        // cout.imbue(locale("american"));
        // cout << 1.1 << "n";

        auto my_loc = locale(""); // OK
        auto posix_loc = locale("POSIX");
        auto us_loc = locale("en_US.utf8");
        cout.imbue(locale("en_US.utf8"));
        cout << 1.1 << "n";
        cout << endl;

        // auto an_loc = std::locale("en");

        double d = stod("10.5");
        d *= 4;
        cout << d << "n" << endl;

        string str = "49.5 red ballons";
        size_t idx = 0;
        double d2 = stod(str, &idx);
        d2 *= 2;
        string rest = str.substr(idx);
        cout << d2 << rest << "n" << endl;

        double d3 = 123456789.987654321;
        cout << d3 << "n" << endl;
        cout << fixed;
        cout << d3 << "n" << endl;
        cout.precision(9);
        cout << d3 << "n" << endl;
        cout << scientific;
        cout << d3 << "n" << endl;        

    }
}