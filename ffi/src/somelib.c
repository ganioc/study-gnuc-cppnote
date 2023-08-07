#include "somelib.h"

DataPoint add_data(const DataPoint* dps,unsigned n){
    DataPoint out = {.num = 0, .dnum = 0.0 };

    for(unsigned i = 0; i < n; ++i){
        out.num += dps[i].num;
        out.dnum += dps[i].dnum;
    }

    return out;
}