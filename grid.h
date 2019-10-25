#ifndef _GRID_H_
#define _GRID_H_

#include <vector>
#include "curve.h"
#include <random> // uniform_real_distribution
#include "my_vector.h"
#include <set>
#include <algorithm>
//#include "my_vector.cpp"

template <class T>
class grid
{
private:
    std::vector<double> t;
    double delta;

public:
    grid(double, int);
    ~grid();
    curve<double> gridify(curve<T> *);
    //my_vector<double> vectorify(curve<double>);
    //void add_pad(my_vector<double> *, double, unsigned int);
};

#endif
