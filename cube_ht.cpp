#include "cube_ht.h"
#include <string>


template <class T>
cube_ht<T>::cube_ht(int d_ton, int vector_dimensions, int w_to_be){
    d_tonos = d_ton;
    size = (int) floor(pow(2,(double)d_ton ));
    cube.clear();
    cube.resize(size);
    for (unsigned int i = 0; i < size; i++) {
        cube[i].clear();
    }

    fi_seeds.clear();

    for(unsigned int i = 0; i < d_ton; i++){
      std::random_device rand_dev;
      std::mt19937 generator(rand_dev());
      std::uniform_real_distribution<int>  distr(0, w_to_be);
      fi_seeds.push_back(distr(generator)); //pairnei times o pinakas

    }

    my_gs.clear();
    for(unsigned int i=0; i<d_ton; i++){
      g_funs<T> a_g_fun(k_ys, vector_dimensions, w_to_be);
      my_gs.push_back(a_g_fun);
    }

}

template <class T>
cube_ht<T>::~cube_ht(){}


template <class T>
int cube_ht<T>::fi_function(long int gval, int index) {
    long int mix = gval + fi_seeds[index] ;
    //int fi = our_mod(mix, 2); //isws thelei %
    int fi = mix%2;
    return fi;
}



template <class T>
void cube_ht<T>::cubify_vector(my_vector<T> *v) {
    /*std::cout << "etsi hto o pinax prin hasharw to " << v->get_id_as_int() <<":";
    for(int i =0; i< table.size(); i++)
      for(int j =0; j< table[i].size(); j++)
        std::cout << table[i][j].first->get_id_as_int();
    std::cout << "\n";*/

    std::string vertex = "";
    for(unsigned int i=0; i<my_gs.size(); i++){
      long int gival = my_gs[i].actual_g_function(*v); //ypologise thn timh ths gi gia to vector v
      int fi = fi_function(gival, i);
      std::string fi_str = std::to_string(fi);
      vertex += fi_str;
    }
    unsigned long long key_vertex = std::stoull(vertex, NULL, 2); //metafrazei to bitstring-korufh yperkuvou se thesh pinaka

    std::pair<my_vector<T> * , long int> thepair;
    thepair.first = v;
    thepair.second = keyv;
    //table[modded_keyv] = tmp_ht_cell; //vale auto to ht_cell sto katallilo bucket tou table
    table[modded_keyv].push_back(thepair);
    //std::cout << "my id is " << thepair.first->get_id_as_int() << "\n";
}








//template class cube_ht<float>;
template class cube_ht<int>;
//template class cube_ht<double>;
