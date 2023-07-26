#include <iostream>
#include <vector>

#include "mem.h"

using namespace std;

namespace Bootest{
    void sayHello(void){
        cout << "Bootest say: hello!" << endl;
    }
    void testPtr(void){
        cout << "scoped_ptr test =>" << endl;
        scoped_ptr<int> p(new int);
        if(p){
            *p = 100;
            cout << *p << endl;
        }
        p.reset();

        assert(p == 0);
        if(!p){
            cout << "scoped_ptr == null" << endl;
        }

        cout << "scoped_array test =>" << endl;
        scoped_array<int> sa(new int[100]);
        sa[0] = 10;
        *(&sa[1]) = 20;


        cout << "unique_ptr test =>" << endl;
        unique_ptr<int> up(new int);
        assert(up);
        *up = 10;
        cout << *up << endl;

        cout << "shared_ptr test =>" << endl;
        boost::shared_ptr<int> spi(new int);
        assert(spi);
        *spi=253;
        boost::shared_ptr<string> sps(new string("smart string"));
        assert(sps->size() == 12);

        boost::shared_ptr<int> sp(new int(10));
        assert(sp.unique());

        boost::shared_ptr<int> sp2 = sp;
        assert(sp == sp2 && sp.use_count() == 2);

        *sp2 = 100;
        assert(*sp == 100);

        sp.reset();
        assert(!sp);

        boost::shared_ptr<string> spm = boost::make_shared<string>("make_shared");
        boost::shared_ptr<std::vector<int>> spv = \
            boost::make_shared<std::vector<int>>(10,2);
        cout << "vector size: " << spv->size() << endl;

        typedef vector<boost::shared_ptr<int>> vs;
        vs v(10);

        int i = 0;
        for(vs::iterator pos = v.begin(); pos != v.end(); ++pos){
            (*pos) = boost::make_shared<int>(++i);
            cout << *(*pos) << ",";
        }
        cout << endl;

        boost::shared_ptr<int> p9 = v[9];
        *p9 = 100;
        cout << *v[9] << "" << endl;
        

    }
    Sample::Sample():p(new impl){}

    void Sample::print(){
        p->print();
    }
    void testBridge(){
        Sample s;
        s.print();
    }
    void any_function(void *p){
        cout << "some operation " << endl;
    }
    void testFactory(){
        boost::shared_ptr<Abstract> p = createFactory();
        p->f();
        p->g();
        boost::shared_ptr<void> p2((void *) 0, any_function);

        int *p3 = new int[1000];
        boost::shared_array<int> sa(p3);
        boost::shared_array<int> sa2 = sa;

        sa[0] = 10;
        cout << "sa2[0]: " << sa2[0] << endl;
    }
    boost::shared_ptr<Abstract> createFactory(){
        return boost::shared_ptr<Abstract>(new Impl);
    }

    void testWeak(){
        boost::shared_ptr<int> sp(new int(10));
        cout << "testWeak =>" << endl;
        cout << "sp.use_count: " << sp.use_count() << endl;

        boost::weak_ptr<int> wp(sp);
        if(!wp.expired()){
            boost::shared_ptr<int> sp2 = wp.lock();
            *sp2 = 100;
            cout << "wp.use_count: " << wp.use_count() << endl;
        }
    }

    void testPool(){
        pool<> pl(sizeof(int));
        int *p = static_cast<int*>(pl.malloc());

        cout << "testPool =>" << endl;
        cout << "p is from pl: " << pl.is_from(p) << endl;

        pl.free(p);
        for( int i=0; i< 100; i++){
            pl.ordered_malloc(10);
        }

    }
}