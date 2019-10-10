#include <string>
#include <vector>
#include <sstream>
#include <stdlib.h> //atoi
#include "my_vector.h"
#include <cctype> //isdigit

using namespace std;

//to pneuma tou constructor einai na pairnei to input string - seira sto arxeio eisodou kai na kanei swsta tis arxikopoihseis
template <class T>
my_vector<T>::my_vector(std::string inp){
    vector <string> tokens;
    stringstream check1(inp);

    string intermediate;
    // Tokenizing w.r.t. space ' '
    while(getline(check1, intermediate, ' ')) {
        tokens.push_back(intermediate);
    }

    string the_id = tokens[0]; //to id einai to prwto
    my_vector<T>::set_id(the_id);

    for(int i=1; i< tokens.size(); i++){
        stringstream tool(tokens[i]);
        int dimens_i = 0;
        tool >> dimens_i;
        vec.push_back(dimens_i); //vazei sto vector kathe stoixeio-diastash tou dianusmatos apo to input string
    }
}

template <class T>
void my_vector<T>::set_id(string idd) {
    id = idd;
    return;
}

template <class T>
void my_vector<T>::set_v(std::vector<T> vv) {
    typename vector< T >::iterator it2 = vv.begin();
    for(typename vector< T >::iterator it = vec.begin(); it != vec.end(); ++it) {
        *it = *it2;
        ++it2;
    }
    return;
}

template <class T>
string my_vector<T>::get_id() {
    return id;
}

template <class T>
int my_vector<T>::get_id_as_int() {
    string tmp = id;
    int my_id=0;
    for (int i=0;i<id.length();i++) {
        if (isdigit(id[i])) {
            tmp = id.substr(i, id.length()-1);
            my_id = atoi(tmp.c_str());
        }
    }
    return my_id;
}

template <class T>
vector<T> my_vector<T>::get_v() {
    return vec;
}

template class my_vector<float>;
template class my_vector<int>;
