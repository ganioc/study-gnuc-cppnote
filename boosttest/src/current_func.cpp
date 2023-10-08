#include <boost/current_function.hpp>
#include <iostream>
#include <boost/core/swap.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits.hpp>
#include <boost/predef.h>

using namespace std;

namespace FoFum{
    class Foo
    {
        public:
            void bar(){
                cout << BOOST_CURRENT_FUNCTION << endl;
                bar_private(5);
            }
            static void bar_static(){
                cout << BOOST_CURRENT_FUNCTION << endl;
            }
        private:
            float bar_private(int x) const {
                cout << BOOST_CURRENT_FUNCTION << endl;
                return 0.0;
            }
    };
}
namespace{
    template <typename T>
    void baz(const T& x){
        cout << BOOST_CURRENT_FUNCTION << endl;
    }
}
template <typename T>
void process_values(T& arg1, T& arg2){
    cout << "Before swap " << arg1 << "," << arg2 << endl;
    swap(arg1, arg2);
    cout << "After swap " << arg1 << "," << arg2 << endl;

}
template <typename T>
class SmallObjectAllocator{
    BOOST_STATIC_ASSERT(sizeof(T) <= 16);
public:
    SmallObjectAllocator(){}
};
struct Foo{
    char data[32];
};

template <typename T, typename U>
T bitwise_or(const T& left, const U& right){
    BOOST_STATIC_ASSERT(boost::is_pod<T>::value &&
        boost::is_pod<U>::value);
    BOOST_STATIC_ASSERT(sizeof(T) >= sizeof(U));

    T result = left;
    unsigned char *right_array = 
        reinterpret_cast<unsigned char*>(&right);
    unsigned char *left_array =
        reinterpret_cast<unsigned char*>(&result);
    
    for(size_t i = 0; i < sizeof(U); ++i){
        left_array[i] |= right_array[i];
    }

    return result;
}
int main(){
    cout << "Test current function" << endl;

    FoFum::Foo f;
    f.bar();
    FoFum::Foo::bar_static();

    baz(f);
    
    int num1=18, num2=29;
    process_values(num1, num2);

    SmallObjectAllocator<int> intAlloc;
    // SmallObjectAllocator<Foo> fooAlloc;

    cout << "check system info:" << endl;

    #if defined(BOOST_OS_WINDOWS)
        cout << "Windows" << endl;
    #elif defined(BOOST_OS_LINUX)
        cout << "Linux" << endl;
    #elif defined(BOOST_OS_MACOS)
        cout << "MacOS" << endl;
    #elif defined(BOOST_OS_UNIX)
        cout << "Unix" << endl;
    #endif

    #if defined(BOOST_ARCH_X86)
        cout << "x86-32 bit" << endl;
    #endif
    #if defined(BOOST_ARCH_X86_64)
        cout << "x86-64 bot" << endl;
    #endif

    #if defined(BOOST_COMP_GNUC)
        cout << "GCC, Version: " << BOOST_COMP_GNUC << endl;
    #endif

    cout << "Compiler: " << BOOST_COMPILER << endl;
    cout << "Platform: " << BOOST_PLATFORM << endl;
    cout << "Library:  " << BOOST_STDLIB << endl;
    cout << "Boost version: " << BOOST_LIB_VERSION << '['
        << BOOST_VERSION << ']' << endl;

    return 0;
}