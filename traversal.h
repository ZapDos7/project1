#ifndef _TRAVERSAL_H_
#define _TRAVERSAL_H_

#include "curve.h"

template <class T>
class traversal
{
private:
    std::pair<std::string, std::string> curve_ids;
    <std::vector<std::pair<int, int>>> all_possible_travs;

public:
    traversal(curve<T> *c1, curve<T> *c2);
    ~traversal();
    std::vector<std::pair<int, int>> get_all_possible_travs();
};

#endif