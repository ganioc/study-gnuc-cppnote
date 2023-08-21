#include<iostream>
#include "mem.h"
#include "util.h"

using namespace std;

int main(int argc, char**argv){
    cout << "Boost lib test" << endl;

    Bootest::sayHello();
    Bootest::testPtr();
    Bootest::testBridge();
    Bootest::testFactory();
    Bootest::testWeak();
    Bootest::testPool();

    Booutil::sayHello();
    Booutil::testTuple();
    Booutil::testVariant();

    return 0;
}