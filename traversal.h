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
    traversal<T>(curve<T> *c1, curve<T> *c2);
    ~traversal<T>();
    std::vector<std::pair<int, int>> get_all_possible_travs();
};

class traversal_node
{
public:
    std::pair<int, int> zeugos;
    traversal_node *left;   //aristera shmainei kineitai o first
    traversal_node *center; //kentro shmainei kinountai kai oi 2
    traversal_node *right;  //deksia shmainei kineitai o second

    traversal_node(){};
    ~traversal_node(){};                                          //DOULITSA
    void recursive_builder(int curve1_length, int curve2_length); //sunexizei to dentro me riza ton idio ton komvo
};

class traversal_tree
{
private:
    traversal_node root; //h riza tou dentrou me ta traversals
public:
    traversal_tree(int curve1_length, int curve2_length);
    ~traversal_tree(){}; //DOULITSA

    //get all traversals
};

#endif
