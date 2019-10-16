
#ifndef MYVECTOR_H
#define MYVECTOR_H

#include <string>
#include <vector>

template <class T>
class my_vector {
private:
    std::string id; //ids mporei na einai mondaikoi akeraioi h strings opote valame int gia na dexetai kathe periptwsi
    std::vector<T> vec;
public:
    my_vector< T >(std::string inp); // o conustructor gia parametropoihsh
    void set_id(std::string idd);
    void set_v(std::vector<T> vv);
    std::string get_id();
    int get_id_as_int();
    std::vector<T> get_v();
};

#endif
