#include <random>
#include <algorithm>
#include <ratio>

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
}