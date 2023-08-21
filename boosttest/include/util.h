#pragma once

#include <iostream>
#include <boost/tuple/tuple.hpp>
#include <vector>
#include <boost/variant.hpp>
#include <string>

using namespace std;

namespace Booutil{
    void sayHello();

    boost::tuple<size_t, size_t, double> getBestTransactDays(vector<double> prices);

    void testTuple();

    template<typename T>
    size_t tuple_length(const T&){
        return boost::tuples::length<T>::value;
    }
    struct Foo{
        Foo(int n=0):id_(n){}
    private:
        int id_;
    };
    struct Bar{
        Bar(int n = 0): id_(n){} 
    private:
        int id_;
    };
    void testVariant();
}