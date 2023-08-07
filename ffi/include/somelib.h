#ifndef SOMELIB_H
#define SOMELIB_H

typedef struct {
    int num;
    double dnum;
} DataPoint;

DataPoint add_data(const DataPoint* dps, unsigned n);

#endif /* SOMELIB_H  */


