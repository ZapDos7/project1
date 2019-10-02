#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>

double my_inner_product(std::vector<int> v1, std::vector<int> v2) { //vi * v2 = sum(v1i * v2i) gia kathe i
	if (v1.size() != v2.size()) {
		//cerr << "Can't calculate distance, need same dimensions! Aborting...\n";
        exit(-1);
	}
	double temp=0.0;
	std::vector<int> products;
	for (unsigned int i = 0; i < v1.size(); ++i) { //std::inner_product
		temp = v1[i]*v2[i];
		products.push_back(temp);
	}
	temp = 0.0; 
	for(std::vector<int>::iterator it = products.begin(); it != products.end(); ++it) {
		temp += *it; //to athroisma twn ginomenwn
	}
	return temp;
}

double my_vector_metro(std::vector<int> v) {
	double temp=0.0;
	std::vector<int> squared;
	for (unsigned int i = 0; i < v.size(); ++i) {
		temp = v[i]*v[i];
		squared.push_back(temp);//tetragwna kathe thesis
	}
	temp = 0.0; 
	for(std::vector<int>::iterator it = squared.begin(); it != squared.end(); ++it) {
		temp += *it; //to athroisma twn tetragwnwn
	}
	return sqrt(temp); //sqrt autwn
}

double manhattan_distance(std::vector<int> v1, std::vector<int> v2) {
    if (v1.size() != v2.size()) {
		//cerr << "Can't calculate distance, need same dimensions! Aborting...\n";
        exit(-1);
	}
    //sum twn (apoluti timi twn diaforwn twn  (suntetagmeni i tou v1, syntetagmeni i tou v2) )
    double result=0.0;
	std::vector<int> diffs;
	for (unsigned int i = 0; i < v1.size(); ++i) {
		result = abs(v1[i]-v2[i]);
		diffs.push_back(result);
	}
	result = 0.0; 
	for(std::vector<int>::iterator it = diffs.begin(); it != diffs.end(); ++it) {
		result += *it; //to athroisma twn apol. diaforwn
	}
	return result;
}