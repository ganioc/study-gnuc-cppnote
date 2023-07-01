#include <iostream>

#include "main.h"
#include "study.h"


using namespace std;

int main(int argc, char **argv){
    cout << "hello from main" << endl;

    Study::hello();
    Study::testRatio();
    Study::testString();

    return 0;
}