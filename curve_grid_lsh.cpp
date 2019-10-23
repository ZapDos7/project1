#include "curve.h"
#include "curve_point.h"
#include <iostream>
#include <typeinfo>
#include <chrono> // time measurements

int main(int argc, char *argv[])
{
    std::cout.precision(17);
    std::string inp = "1 2 (-6.43, 53.3) (100.10, 182.2918979)";
    curve<double> one(inp);
    std::cout << one.get_id() << '\n'
              << one.get_size() << '\n';

    ///////////////////////////////////aa/////////////////////////////////
    //read files
    //an oxi apo user:
    //$./curve_grid_lsh –d <input file> –q <query file> –k_vec <int> -L_grid <int> -ο<output file>

    //dataset: me tabs anamesa, ka8e grammi: curve_id1      m1    (x11,y11)     (x12,y12)     ...
    //N to plithos twn kampulwn
    //mi to plithos twn shmeiwn tis kampulis
    //xij einai tupou double
    //j shmeio me j <= mi
    //ids mporei na einai mondaikoi akeraioi h strings

    //queryset: toulax 1 vector & panw panw 1 8etiko double R, an R = 0 tote mono 1 NN, an R>1, tote bonus
    //ka8e grammi meta: idS1    x11     x12     x13...
    //q to plithos twn

    // PES MOU an 8es Bi - dld se kampules plegmatos alla anaparistwntai ws vectors - h Bii - dld se vectors-
    //&& PES MOU an 8es LSH h hypercube

    //define path to dataset
    //populate HTs

    //define path to output file & query file
    //queryset: ka8e grammi meta: curve_idS1    ms1    (xs11,ys11)     (xs12,ys12)     ...
    //q to plithos twn
    //pali ID = unique int or string

    //when done all, ask if repeat with other dataset or exit ektelesi

    //LSH for curves
    //int L = 4; //default timi
    //plithos kampulwn plegmatos

    //hypercube for curves
    //double e = 0.5; //default timi
    //o paragontas proseggisis

    //output.txt:
    /*
    for each curveJ in queryset:
    Query: curveJ
    Method: {LSH, Projection}
    HashFunction: {LSH, Hypercube}
    Found Nearest neighbor: curveY
    True Nearest neighbor: curveX
    distanceFound: <double>
    distanceTrue: <double>
    */
}