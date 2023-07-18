#include <iostream>

#include "mem.h"

using namespace std;

namespace Bootest{
    void sayHello(void){
        cout << "Bootest say: hello!" << endl;
    }
    void testPtr(void){
        scoped_ptr<int> p(new int);
        if(p){
            *p = 100;
            cout << *p << endl;
        }
        p.reset();

        
    }
}