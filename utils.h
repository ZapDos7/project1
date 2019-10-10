#ifndef _UTILS_H_
#define _UTILS_H_

#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>
#include "my_vector.h"

double my_inner_product(std::vector<int> v1, std::vector<int> v2);
double my_vector_metro(std::vector<int> v);
template <class T>
T manhattan_distance(std::vector<T> v1, std::vector<T> v2);


#endif