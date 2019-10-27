#include "cube_grid.h"
//#include "my_vector.cpp"
template <class T>
void cube_grid<T>::define_cube_table(int d_ton, int vector_dimensions, double w_to_be){
  curve_cube_ht<T> myht(d_ton, vector_dimensions,  w_to_be);
  my_cube = myht;

}

template <class T>
cube_grid<T>::cube_grid(double d_to_be, int dimensions)
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
cube_grid<T>::~cube_grid() {}

template <class T>
curve<double> cube_grid<T>::gridify(curve<T> *c)
{
    curve<double> gc;
    gc.set_id(c->get_id()); //diathrw to id giati eimai magkas
    //gia kathe shmeio ths c briskw to a = floor(c[i])/delta, kanw a * delta gia na brw to coordinate (se kathe aksona)
    //std::set<curve_point<double>> uniques;
    std::set<std::pair<double, double>> uniques;
    for (unsigned int i = 0; i < c->get_size(); i++)
    {
        T x1 = c->get_points()[i].get_x();
        double x2 = floor((double)x1 / delta);
        x2 *= delta; //to x tou grid curve gia to shmeio c[i]
        x2 += t[0]; //h metatopish gia to x
        T y1 = c->get_points()[i].get_y();
        double y2 = floor((double)y1 / delta);
        y2 *= delta; //to y tou grid curve gia to shmeio c[i]
        y2 += t[1]; //h metatopish gia to y
        //curve_point<double> cp(x2, y2);
        std::pair<double, double> cp_rep;
        cp_rep.first = x2;
        cp_rep.second = y2;
        uniques.insert(cp_rep); //ara krataei monadika
    }
    std::vector<curve_point<double>> tmp;
    std::vector<std::pair<double, double>> temp2(uniques.begin(), uniques.end());
    for (unsigned int i = 0; i < temp2.size(); i++)
    {
        curve_point<double> cp(temp2[i].first, temp2[i].second);
        tmp.push_back(cp);
    }
    gc.set_points(tmp);
    gc.set_num_of_pnts(tmp.size());
    return gc;
}


my_vector<double> vectorify(curve<double> gc) //kanw to grid curve --> vector
{
    my_vector<double> gcv;
    std::vector<double> tmp;
    tmp.clear();
    for (unsigned int i = 0; i < gc.get_v_size(); i++) //kathe curve point tis gc
    {
        tmp.push_back(gc.get_points()[i].get_x());
        tmp.push_back(gc.get_points()[i].get_y());
    }
    gcv.set_v(tmp);
    if (gcv.get_v().size() != 2 * gc.get_v_size())
    {
        std::cerr << "Error pushing back grid curve's elements to vector (vectorify)\n";
        exit(-1);
    }
    gcv.set_id(gc.get_id());
    return gcv;
}


void add_pad(my_vector<double> *gcv, double timi, unsigned int max_vec_size)
{
    //vale "timi" sto "gcv" mexri na exei megethos "max_vec_size"
    //std::cout << "maxdims is " << max_vec_size << std::endl;
    std::vector<double> tmp = gcv->get_v();
    //std::cout << "hello2\n";
    for (unsigned int i = 0; i < max_vec_size - gcv->get_v().size(); i++) //an px theloume max size = 10 kai exoume 2 8eloume na baloume 10-2=8 ara apo 0 ws 7
    {
        tmp.push_back(timi);
    }
    //std::cerr << "tmp size2 is " << tmp.size();
    //std::cout << "hello3\n";
    gcv->set_v(tmp);
    if (gcv->get_v().size() != max_vec_size)
    {
        std::cerr << "Error in add_pad\n";
        exit(-1);
    }
    //std::cerr << "tmp size3 is " << gcv->get_v().size();
    return; //an exei error, isws thelei na kanoume ena tmp antigrafo tou gcv, na baloume ekei ta "timi" & na epistrepsoume auto
}

template class cube_grid<float>;
template class cube_grid<int>;
template class cube_grid<double>;
