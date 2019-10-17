#ifndef _G_FUNS_H
#define _G_FUNS_H

#include "h_funs.h"


/*Our class about the G-functions (k*h_functions) which produce the key which will determine where in the hash table our vector will go*/

template <class T>
class g_funs
{
private:
    int k;
    std::vector<h_funs<T>> my_h_funs;
public:
    g_funs(int k_to_be, int dimensions, int w_to_be);
    ~g_funs();
    int actual_g_function();
};

#endif