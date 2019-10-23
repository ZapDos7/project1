#include "curve_point.h"
#include "curve.h"
#include "traversal.h"
#include <iostream>
#include <typeinfo>
#include <chrono> // time measurements

int main(int argc, char *argv[])
{
    //test chamber
    std::cout.precision(17);
    std::string inp = "1	7	(-6.4227999999999996, 53.288000000000004) (-6.4257099999999996, 53.289299999999997) (-6.4268099999999997, 53.290300000000002) (-6.4268099999999997, 53.290300000000002) (-6.4268099999999997, 53.290300000000002) (-6.4271699999999994, 53.290599999999998) (-6.4271699999999994, 53.290599999999998)";
    curve<double> crv(inp);
    //std::cout << crv.get_points()[0].get_x();
}