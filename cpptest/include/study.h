#pragma once

#include <iostream>

using namespace std;

namespace Study {
    void hello(void);
    void testRatio(void);
    void testString(void);
    struct point{
        double x = 0.0, y = 0.0;
        point(){}
        point(double _x, double _y):x(_x), y(_y){}

    };
    ostream& operator<<(ostream& out, const point& p);

    void testIns(void);
    void testRegex(void);
}