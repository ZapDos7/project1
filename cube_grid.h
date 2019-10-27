#ifndef CUBE_GRID_H_
#define CUBE_GRID_H_

#include <vector>
#include "curve.h"
#include <random> // uniform_real_distribution
#include "my_vector.h"
#include <set>
#include "curve_cube_ht.h"
#include <algorithm>
//#include "my_vector.cpp"

template <class T>
class cube_grid
{
private:
    std::vector<double> t;
    double delta;
    //curve_cube_ht<T> my_cube;
    //pithanws deutero antikeimeno edw gia kybo

public:
    curve_cube_ht<T> my_cube;
    cube_grid<T>(double, int);
    cube_grid<T>(){};
    ~cube_grid();
    curve<double> gridify(curve<T> *);
    void define_cube_table(int d_ton, int vector_dimensions, double w_to_be);
};

my_vector<double> vectorify(curve<double>);
void add_pad(my_vector<double> *, double, unsigned int);

#endif
