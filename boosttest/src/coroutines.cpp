#include <iostream>
#include <boost/coroutine/all.hpp>
#include <boost/bind.hpp>
#include <vector>
#include <string>

using namespace std;

template <typename T>
using pull_type = typename boost::coroutines::asymmetric_coroutine<T>::pull_type;

template <typename T>
using push_type = typename boost::coroutines::asymmetric_coroutine<T>::push_type;

template <typename T>
void getNextElem(push_type<T>& sink, const vector<T>& vec){
    for(const auto& elem: vec){
        sink(elem);
    }
}

int main(void){
    cout << "Test coroutines" << endl;

    vector<string> vec{"hello", "hi", "hola", "servus"};

    pull_type<string> greet_func(
        boost::bind(getNextElem<string>, ::_1, boost::cref(vec))
    );

    while (greet_func)
    {
        /* code */
        cout << greet_func.get() << endl;
        greet_func();
    }
    

    return 0;
}