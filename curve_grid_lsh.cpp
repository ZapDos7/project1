#include "curve.h"
#include "curve_point.h"
#include <iostream>
#include <typeinfo>
#include <chrono> // time measurements

int main(int argc, char *argv[])
{
    //test chamber
    std::cout.precision(17);
    std::string inp = "1	7	(-6.4227999999999996, 53.288000000000004) (-6.4257099999999996, 53.289299999999997) (-6.4268099999999997, 53.290300000000002) (-6.4268099999999997, 53.290300000000002) (-6.4268099999999997, 53.290300000000002) (-6.4271699999999994, 53.290599999999998) (-6.4271699999999994, 53.290599999999998)";
}

/*
Ekdoxi #3:
curve<T>::curve(string inp)
{
    vector<string> tokens; //edw bazoume kathe mh whitespace xarakthra, theorontas oti to format tou input file einai id<tab>mi<tab>(x0, x0) (x1, y1)...

    std::stringstream stringStream(inp);
    std::string line;
    while (std::getline(stringStream, line))
    {
        std::size_t prev = 0, pos;
        while ((pos = line.find_first_of("\t ", prev)) != std::string::npos)
        {
            if (pos > prev)
                tokens.push_back(line.substr(prev, pos - prev));
            prev = pos + 1;
        }
        if (prev < line.length())
            tokens.push_back(line.substr(prev, std::string::npos));
    }

    //stringstream file(inp);
    //string line;
    //getline(file, line, '\t'); //file holds line = id \t (m \t (x0, y0)...)
    //tokens[0] = line;

    id = tokens[0]; //to id einai to prwto
    num_of_points = atoi(tokens[1].c_str());

    for (unsigned int i = 2; i < tokens.size(); i++) //edw prepei na ginetai h malakiaaaa
    {
        stringstream tool(tokens[i]);
        string tmp;
        T coordx;
        T coordy;
        std::string::size_type sz; // alias of size_t
        bool x_done = false;       //elegxei an exoume grapsei kai to x
        bool y_done = false;       //elegxei an exoume grapsei kai to y
        curve_point<T> temp;       //constructor xwris orismata
        //tha paei seiriaka: i=2 (x0), i=3(x1) kai 8a ta valei
        if (i % 2 == 0)                                          //x
        {                                                        //tis morfis: "(-6.4227999999999996," => afairw 1st kai last char
            tmp = tool.str().substr(1, tool.str().length() - 1); //x = -6.4227999999999996
            if (typeid(coordx) == typeid(double))
            {
                coordx = stod(tmp, &sz);
            }
            else if (typeid(coordx) == typeid(float))
            {
                coordx = stof(tmp, &sz);
            }
            else if (typeid(coordx) == typeid(int))
            {
                coordx = stoi(tmp);
            }
            //std::cout << coordx << '\n';
            temp.set_x(coordx);
            //std::cout << temp.get_x() << '\n';
            x_done = true;
        }
        else                                                     //y
        {                                                        //tis morfis "53.288000000000004)" => afairw last char
            tmp = tool.str().substr(0, tool.str().length() - 1); //y = 53.288000000000004
            if (typeid(coordy) == typeid(double))
            {
                coordy = stod(tmp, &sz);
            }
            else if (typeid(coordy) == typeid(float))
            {
                coordy = stof(tmp, &sz);
            }
            else if (typeid(coordy) == typeid(int))
            {
                coordy = stoi(tmp);
            }
            ////std::cout << coordy << '\n';
            temp.set_y(coordy);
            //std::cout << temp.get_y() << '\n';
            y_done = true;
        }
        if ((x_done == true) && (y_done == true))
        {
            my_points.push_back(temp);
            x_done = false;
            y_done = false;
        }
    }
}
*/