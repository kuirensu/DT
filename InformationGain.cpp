//
//  InformationGain.cpp
//  DesicionTree
//
//  Created by Kuiren Su on 10/17/17.
//  Copyright © 2017 Kuiren Su. All rights reserved.
////
#include <iostream>
#include <cstdlib>
#include <tgmath.h>
#include <set>
#include <utility>
#include <map>
#include <climits>
#include "InformationGain.hpp"
using namespace std;


double booleanEntropy(double q) {
    //B(q) = −(q log2 q + (1 − q) log2(1 − q)) .
    if (q == 0 || q == 1){
        return 0.0;
    }
    return -(q*log2(q) + (1-q)* log2(1-q));
};
//calculate infoGain of a feature
double informationGain(map<char, pair<int, int >> feature, int exampleSize){
    double infoGain = 1.0;
    for (auto const& it : feature){
        int nk =it.second.first; //number of 0s
        int pk =it.second.second; //number of 1s
        //cout << "pk is : " << pk << " nk is : "<< nk << endl;
        double pKRatio =  (double(pk) /(pk+nk));
        infoGain -= (double(pk+nk)/exampleSize)*booleanEntropy(pKRatio);
       // cout << "booleanEntropy is " << booleanEntropy(pKRatio) << endl;
    }
    
    return infoGain;
};

int pickNextAttribute(char **trainningSet, set<int> examples, set<int> attributes ) {
    map<int , map<char, pair<int, int >>> allAttributes;

    for (auto const& a : attributes){
        //map <feature, <0s, 1s> >  for attribute at col j
        map<char, pair<int, int >> attribute;

        for (auto const& it : examples){
            //cout<< "row : " << *it << " col: " << *a<< endl;
            //cout << "attributes size" << endl;
            map<char, pair<int, int >>::iterator feature = attribute.find(trainningSet[it][a]);
            if(feature == attribute.end() ){
                attribute[trainningSet[it][a]] = make_pair(0, 0);
                feature = attribute.find(trainningSet[it][a]);
            }
            
            if (trainningSet[it][0] == '0' ){
                feature->second.first += 1;
            }else if (trainningSet[it][0] == '1'){
                feature->second.second += 1;
            }
        }
 
        allAttributes[a] = attribute;
        
    }
    int maxColIndex = -1;
    double maxInforGain = double(INT_MIN);
    for (auto const& it : allAttributes){
        double temp = informationGain(it.second, int(examples.size()));
        //cout<< "InformationGain at col: "<< it.first <<" is: " <<temp << endl;
        if (temp > maxInforGain){
            maxInforGain = temp;
            maxColIndex = it.first;
        }
    }
    return maxColIndex;
};




