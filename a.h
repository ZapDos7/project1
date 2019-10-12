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
    a(double w_to_be); //pairnei san orisma to 4 * r opou r h mesi apostasi vectors
    ~a();
    int get_a(double coordinate); //pairnei san orisma ena coordinate enos vector (tupou double) kai epistrefei to ai(xi)
};
#endif