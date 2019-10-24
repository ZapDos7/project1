#ifndef _GRID_H_
#define _GRID_H_

#include <vector>
#include "curve.h"
#include <random> // uniform_real_distribution

template <class T>
class grid
{
private:
    std::vector<double> t;
    double delta;

public:
    grid(double, int);
    ~grid();
    curve<int> gridify(curve<T> *c);
};

#endif