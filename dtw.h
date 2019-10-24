#ifndef _DTW_H_
#define _DTW_H

#include "curve.h"
#include "curve_point.h"
#include <cmath>
#include <limits>
#include "traversal.h"

template <class T>
class dtw
{
private:
    /* data */
public:
    dtw(){};
    ~dtw(){};
    double euclidean(curve_point<T> cp1, curve_point<T> cp2);
    double actual_dtw(curve<T> *c1, curve<T> *c2);
};

template <class T>
double dtw<T>::actual_dtw(curve<T> *c1, curve<T> *c2)
{
    //gia kathe pithano traversal metaksu twn 2 kampulwn
    //pairnw to min sum twn apolutwn diaforwn kapoiwn shmeiwn pk, qk (idio indice gia ta 2 curves)
    traversal_tree<T> my_tree(c1, c2);
    std::vector<traversal_node *> tool;
    tool.clear();
    my_tree.recursive_search(my_tree.access_root(), tool); //gemise o draft_traversals mou
    std::vector<traversal<T>> vec_trav;
    vec_trav = my_tree.objectify_travs(c1, c2);
    std::vector<double> apostaseis;
    for (unsigned int i = 0; i < vec_trav.size(); i++) //gia kathe pithano traversal metaksu twn 2 kampulwn
    {
        std::vector<std::pair<int, int>> ena_traversal;
        ena_traversal = vec_trav[i].get_my_traversal();
        double sum_eucl = 0.0;
        double eucl = 0.0;
        for (unsigned int j = 0; j < ena_traversal.size(); j++) //gia kathe zeugari apo indices
        {
            curve_point<T> shmeio_ths_c1 = c1->get_points()[ena_traversal[j].first];  //c1[first] = curvepoimt1
            curve_point<T> shmeio_ths_c2 = c2->get_points()[ena_traversal[j].second]; //c2[second] = curvepoint2
            eucl = euclidean(shmeio_ths_c1, shmeio_ths_c2);                           //euclidean apostasi (cp1, cp2)
            sum_eucl += eucl;                                                         //a8roizw tis euclidean ana index gia auto to traversal
        }
        eucl = 0.0; //ksanamhdenizw to eucl pou einai o metritis kathe apostasis
        apostaseis.push_back(sum_eucl);
        sum_eucl = 0.0;
    }
    double result = std::numeric_limits<double>::max();  //pairnei timh apeiro;
    for (unsigned int i = 0; i < apostaseis.size(); i++) //get min of apostaseis
    {
        if (apostaseis[i] <= apostaseis[i + 1])
        {
            if (result < apostaseis[i])
            {
                result = apostaseis[i];
            }
        }
        else //(apostaseis[i] > apostaseis[i+1])
        {
            if (result < apostaseis[i + 1])
            {
                result = apostaseis[i + 1];
            }
        }
    }
    return result;
}

#endif