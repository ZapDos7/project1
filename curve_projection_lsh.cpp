int main()
{

    ////////////////////////////B - CURVES///////////////////////////////
    //read files

    //an oxi apo user:
    //$./curve_projection_lsh –d <input file> –q <query file> –k_vec <int> -L_vec <int>-e <double> -ο <output file>

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
    int L = 4; //default timi
    //plithos kampulwn plegmatos

    //hypercube for curves
    double e = 0.5; //default timi
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

    ////////////////////////////METRISEIS///////////////////////////////
    /*
Compare apotelesmata twn 4 parallagwn:{
LSH for curves / LSH L1,
LSH for curves / Hypercube,
Random Projection / LSH L1,
Random Projection / Hypercube}
ws pros: {
    a) max klasma proseggisis = {approx NN distance } / {actual NN distance}
    b) mean time euresis tou approx NN
}
*/
}