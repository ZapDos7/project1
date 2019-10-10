#include <string>
#include <vector>
#include <sstream>
#include <stdlib.h> //atoi
#include "my_vector.h"
#include <cctype> //isdigit

using namespace std;

//to pneuma tou constructor einai na pairnei to input string - seira sto arxeio eisodou kai na kanei swsta tis arxikopoihseis
my_vector::my_vector(std::string inp){
    vector <string> tokens;
    stringstream check1(inp);

    string intermediate;
    // Tokenizing w.r.t. space ' '
    while(getline(check1, intermediate, ' ')) {
        tokens.push_back(intermediate);
    }

    string the_id = tokens[0]; //to id einai to prwto
    my_vector::set_id(the_id);

    for(int i=1; i< tokens.size(); i++){
        stringstream tool(tokens[i]);
        int dimens_i = 0;
        tool >> dimens_i;
        vec.push_back(dimens_i); //vazei sto vector kathe stoixeio-diastash tou dianusmatos apo to input string
    }
}

void my_vector::set_id(string idd) {
    id = idd;
    return;
}
void my_vector::set_v(std::vector<int> vv) {
    vector<int>::iterator it2 = vv.begin();
    for(vector<int>::iterator it = vec.begin(); it != vec.end(); ++it) {
        *it = *it2;
        ++it2;
    }
    return;
}
string my_vector::get_id() {
    return id;
}
int my_vector::get_id_as_int() {
    string tmp = id;
    int my_id=0;
    for (int i=0;i<id.length();i++) {
        if (isdigit(id[i])) {
            tmp = id.substr(i, id.length()); //isws thelei length -i -1
            my_id = atoi(tmp.c_str());
        }
    }
    return my_id;
}
std::vector<int> my_vector::get_v() {
    return vec;
}
