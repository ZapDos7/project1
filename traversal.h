#ifndef _TRAVERSAL_H_
#define _TRAVERSAL_H_

#include "curve.h"

template <class T>
class traversal
{
private:
    std::pair<std::string, std::string> curve_ids;
    std::vector<std::pair<int, int>> my_traversal;

public:
    traversal<T>(curve<T> *c1, curve<T> *c2);
    ~traversal<T>();
    std::string get_c_id_1();
    std::string get_c_id_2();
    std::vector<std::pair<int, int>> get_my_traversal();
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
    bool is_leaf();

};

template <class T>
class traversal_tree
{
private:
    traversal_node root; //h riza tou dentrou me ta traversals
    std::vector<std::vector<traversal_node *>> draft_traversals; //pinakas apo pinakes komvwn tou dentrou. Enas pinakas komvwn einai ena traversal.
public:
    traversal_tree<T>(curve<T> *c1, curve<T> *c2);
    ~traversal_tree<T>(){}; //DOULITSA

    //get all traversals
    void recursive_search(traversal_node * rut, std::vector<traversal_node *> tool);
    /*MIA ENDEIKTIKH KLHSH THS EINAI: (apo to dentro)
    std::vector<traversal_node *> vek;
    vek.clear();
    recursive_search(&root, vek);
    twra tha prepei na exei gemisei o draft_traversals
    */
};

#endif
