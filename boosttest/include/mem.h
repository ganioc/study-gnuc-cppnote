#pragma once
#include <iostream>
#include <boost/smart_ptr.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/pool/pool.hpp>

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

    void testPtr(void);

    class Sample{
        private:
            class impl; // incomplete internal declaration
            boost::shared_ptr<impl> p;
        public:
            Sample();
            void print();
    };
    class Sample::impl{
        public:
            void print(){
                cout << "impl print" << endl;
            }
    };

    void testBridge();

    // factory mode
    class Abstract{
        public:
            virtual void f() = 0;
            virtual void g() = 0;
        protected:
            virtual ~Abstract(){}
    };
    class Impl: public Abstract{
        public:
            virtual void f(){
                cout << "class Impl f" << endl;
            }
            virtual void g(){
                cout << "class Impl g" << endl;
            }
    };
    boost::shared_ptr<Abstract> createFactory();
    void testFactory();

    void testWeak();

    void testPool();
}
