#include <iostream>
#include <istream>
#include <fstream>
#include <boost/shared_ptr.hpp>

typedef unsigned char byte;

using namespace std;

class Foo{
public:
    Foo(){}
    ~Foo(){
        cout <<"~Foo() destructor invoked." << endl;
    }
};

typedef boost::shared_ptr<Foo> SPFoo;

int main(){
    cout << "Test memory management" << endl;
    SPFoo f1(new Foo);
    cout << "count: " << f1.use_count() << endl;

    SPFoo f2(f1); // copy
    cout << "f1 count: " << f1.use_count() << endl;
    cout << "f2 count: " << f2.use_count() << endl;



    return 0;
}