#include "grid.h"

template <class T>
grid<T>::grid(double d_to_be, int dimensions)
{
    delta = d_to_be;
    //uniform distr gia t
    std::random_device rand_dev;
    std::mt19937 generator(rand_dev());
    std::uniform_real_distribution<double> distr(0, dimensions); //distr(0, delta)
    for (int i = 0; i < dimensions; ++i)
    {
        t.push_back(distr(generator));
    }
}

template <class T>
grid<T>::~grid() {}

template <class T>
curve<int> grid<T>::gridify(curve<T> *c)
{
    curve<int> gc;
    gc.set_id(c->get_id()); //diathrw to id giati eimai magkas
    //gia kathe shmeio ths c briskw to a = floor(c[i])/delta, kanw a * delta gia na brw to coordinate (se kathe aksona)
    std::set<curve_point<int>> uniques;
    for (unsigned int i = 0; i < c->get_size(); i++)
    {
        x1 = c->get_points()[i].get_x();
        int x2 = floor(x1 / delta);
        x2 *= delta; //to x tou grid curve gia to shmeio c[i
        y1 = c->get_points()[i].get_y();
        int y2 = floor(y1 / delta);
        y2 *= delta; //to y tou grid curve gia to shmeio c[i]
        curve_point<int> cp(x2, y2);
        uniques.insert(cp); //ara krataei monadika
    }
    std::vector<curve_point<int>> tmp(uniques.begin(), uniques.end());
    gc.set_points(tmp);
    gc.set_num_of_pnts(tmp.size());
    return gc;
}