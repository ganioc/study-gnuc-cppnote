#pragma once
#include <iostream>
#include <boost/smart_ptr.hpp>

using namespace boost;
using namespace std;

namespace Bootest {
    struct posix_file{
        posix_file(const char *file_name){
            cout << "open file:" << file_name << endl;
        }
        ~posix_file(){
            cout << "close file" << endl;
        }
    };

    void sayHello(void);

    void testPrt(void);
}
