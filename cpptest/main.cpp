#include <iostream>

#include "main.h"
#include "study.h"


using namespace std;

int main(int argc, char **argv){
    cout << "hello from main" << endl;

    Study::hello();
    Study::testRatio();
    Study::testString();

    Study::point p(10.0, -5.0);
    cout << p << endl;

    Study::testIns();
    Study::testRegex();

    return 0;
}