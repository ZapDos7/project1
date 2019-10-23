#include "traversal.h"

template <class T>
traversal<T>::traversal(curve<T> *c1, curve<T> *c2)
{
    curve_ids.first = c1->get_id();
    curve_ids.second = c2->get_id();
    unsigned int m1 = c1->get_size(); //size of posa traversals exw?
    unsigned int m2 = c2->get_size();
    if ((m1 == 0) || (m2 == 0)) //at least one is empty
    {
        std::cerr << "Curves have no points, therefore there are no traversals\n";
        indices.clear();
    }
    else if ((m1 == 1) && (m2 == 1))
    {
        std::pair<int, int> temppair;
        temppair.first = m1;
        temppair.second = m2;
        indices.push_back(temppair);
    }
    else //m1 >= 1 && m2 >= 1
    {
        std::pair<int, int> temppair;
        for (unsigned int i = 0; i < m1; i++)
        {
            temppair.first = i;
            for (unsigned int j = 0; j < m2; j++)
            {
                temppair.second = j;
                indices.push_back(temppair);
            }
        }
        //anadromikothta?
    }
}

template <class T>
traversal<T>::~traversal() {}

template <class T>
std::vector<std::pair<int, int>> traversal<T>::get_all_possible_travs()
{
    return indices;
}