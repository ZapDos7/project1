#include "dtw.h"

/*Euclidean Distance between two curve points*/
template <class T>
double dtw<T>::euclidean(curve_point<T> cp1, curve_point<T> cp2)
{
    T x1 = cp1.get_x();
    T y1 = cp1.get_y();

    T x2 = cp2.get_x();
    T y2 = cp2.get_y();

    T x = x1 - x2; //calculating number to square in next step
    T y = y1 - y2;
    double dist;

    if (typeid(x) != typeid(y))
    {
        std::cerr << "Incompatible curve point types (What are you doing?!)\n";
        exit(-1);
    }
    if (typeid(x) == typeid(int))
    {
        int x_faux = x;
        int y_faux = y;
        dist = pow((double)x_faux, 2) + pow((double)y_faux, 2); //calculating Euclidean distance
        dist = sqrt(dist);
    }
    else if (typeid(x) == typeid(double))
    {
        double x_faux = x;
        double y_faux = y;
        dist = pow(x_faux, 2) + pow(y_faux, 2); //calculating Euclidean distance
        dist = sqrt(dist);
    }

    return dist;
}

/*DTW*/

template class dtw<float>;
template class dtw<int>;
template class dtw<double>;