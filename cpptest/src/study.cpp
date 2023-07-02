#include <random>
#include <algorithm>
#include <ratio>
#include <locale>
#include <iomanip>
#include <istream>
#include <regex>

#include "study.h"

void testMoney(void){
    double d = 12.345678;
    cout << fixed;
    cout << setfill('#');
    cout << setw(15) <<  d << "n" << endl;

    vector<pair<string, double>> table {
        {"one", 0},
        {"two", 0},
        {"three", 0},
        {"four", 0}
    };
    double d2 =0.1;
    for(pair<string,double> &p:table){
        p.second = d2/17.0;
        d2 += 0.1;
    }

    cout << fixed << setprecision(6);
    for(pair<string, double> p: table){
        cout << setw(6) << left << p.first << setw(10) << p.second << "n" << endl;
    }

    time_t t = time(nullptr);
    tm *pt = localtime(&t);
    cout << put_time(pt, "time = %X date = %x") << "n" << endl;

}

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

        testMoney();
    }


    ostream& operator<<(ostream& out, const point& p){
        out << "(" << p.x << "," << p.y << ")";
        return out;
    }

    void testIns(void){
        std::istringstream ss("-1.0e-6");
        int i;
        ss >> i;
        string str;
        ss >> str;
        cout << "extracted " << i << " remainder " << str << endl; 
    }
    void testRegex(void){
        regex rx("[at]");

        cout << boolalpha;
        cout << regex_match("a", rx) << endl;
        cout << regex_match("at", rx) << endl;

        string str("trumpet");
        regex rx2("(trump)(.*)");
        match_results<string::const_iterator> sm;
        if(regex_match(str, sm, rx2)){
            cout << "the matches were:";
            for(unsigned i = 0; i< sm.size(); ++i){
                cout << "[" << sm[i] << "," << sm.position(i) << "]";
            }
            cout << endl;
        }
    }
}