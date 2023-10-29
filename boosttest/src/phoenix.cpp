#include <iostream>
#include <boost/phoenix/core.hpp>
#include <boost/phoenix/operator.hpp>
#include <vector>
#include <string>
#include <algorithm>

#include <boost/spirit/include/qi.hpp>

using namespace std;

namespace qi = boost::spirit::qi;

int main(){
    cout << "Test phoenix: "<< endl;

    namespace phx = boost::phoenix;
    double eX;
    auto x = phx::ref(eX);

    eX = 10.0;
    cout << (x+1/x)() << endl;
    cout << ((x*x-x+4)/(2*x))() << endl;

    using boost::phoenix::arg_names::arg1;
    vector<string> vec{"Lambda","Iota","Sigma", "Alpha"};
    for_each(vec.begin(), vec.end(),
        cout << arg1 << endl);
    
    string str = "Hello, world!";
    auto iter = str.begin();
    bool success = qi::parse(iter, str.end(),qi::alpha);
    cout << "qi success? "<< success << endl;

    return 0;
}