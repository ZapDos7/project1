
#ifndef MYVECTOR_H
#define MYVECTOR_H

#include <string>
#include <vector>

class my_vector {
private:
    std::string id;
    std::vector<int> vec;
public:
    my_vector(std::string inp); // o conustructor gia parametropoihsh
    void set_id(std::string idd);
    void set_v(std::vector<int> vv);
    std::string get_id();
    std::vector<int> get_v();
};

#endif
