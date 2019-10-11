#ifndef _A_H_
#define _A_H_

#include <cmath> //floor
#include <iostream>
#include <random> // uniform_real_distribution

class a
{
private:
    double w; //paronomastis - cell size
    double si; //to si tou kathe ai
public:
    a(double w_to_be);
    ~a();
    int get_a(double coordinate);
};
/*
a::a(double w_to_be) {
    w = w_to_be;

    const double range_from  = 0; //[
    const double range_to = w; //)
    std::random_device rand_dev;
    std::mt19937 generator(rand_dev());
    std::uniform_int_distribution<double>  distr(range_from, range_to);
    si = distr(generator); //http://www.cplusplus.com/reference/random/uniform_real_distribution/
}

a::~a() {}


int a::get_a(double coordinate) {
    double result = 0;
    result = coordinate - si;
    return floor(result / w);
}*/

#endif