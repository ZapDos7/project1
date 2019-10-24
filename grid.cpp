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
curve<double> grid<T>::gridify(curve<T> *c)
{
    curve<double> gc;
    gc.set_id(c->get_id()); //diathrw to id giati eimai magkas
    //gia kathe shmeio ths c briskw to a = floor(c[i])/delta, kanw a * delta gia na brw to coordinate (se kathe aksona)
    std::set<curve_point<double>> uniques;
    for (unsigned int i = 0; i < c->get_size(); i++)
    {
        x1 = c->get_points()[i].get_x();
        int x2 = floor(x1 / delta);
        x2 *= delta; //to x tou grid curve gia to shmeio c[i
        y1 = c->get_points()[i].get_y();
        int y2 = floor(y1 / delta);
        y2 *= delta; //to y tou grid curve gia to shmeio c[i]
        curve_point<double> cp(x2, y2);
        uniques.insert(cp); //ara krataei monadika
    }
    std::vector<curve_point<double>> tmp(uniques.begin(), uniques.end());
    gc.set_points(tmp);
    gc.set_num_of_pnts(tmp.size());
    return gc;
}

template <class T>
my_vector<double> grid<T>::vectorify(curve<double> gc) //kanw to grid curve --> vector
{
    my_vector<double> gcv;
    for (unsigned int i = 0; i < gc.get_size(); i++) //kathe curve point tis gc
    {
        gcv.push_back(gc.get_points()[i].get_x());
        gcv.push_back(gc.get_points()[i].get_y());
    }
    if (2 * gcv.get_v().size() != gc.get_size())
    {
        std::cerr << "Error pushing back grid curve's elements to vector (vectorify)\n";
        exit(-1);
    }
    gcv.set_id(gc.get_id());
    return gcv;
}

template <class T>
my_vector<double> grid<T>::add_pad(my_vector<double> gcv, double timi, unsigned int max_vec_size)
{
    //vale "timi" sto "gcv" mexri na exei megethos "max_vec_size"
    for (unsigned int i = 0; i < max_vec_size - gcv.get_v().size(); i++)
    {
        gcv.vec.push_back(timi);
    }
    if (gcv.get_v().size() != max_vec_size)
    {
        std::cerr << "Error in add_pad\n";
        exit(-1);
    }
    return gcv; //an exei error, isws thelei na kanoume ena tmp antigrafo tou gcv, na baloume ekei ta "timi" & na epistrepsoume auto
}