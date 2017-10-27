//
//  InformationGain.hpp
//  DesicionTree
//
//  Created by Kuiren Su on 10/17/17.
//  Copyright © 2017 Kuiren Su. All rights reserved.
//
//
#ifndef InformationGain_hpp
#define InformationGain_hpp
#include <set>
#include <utility>
#include <map>
#include <stdio.h>
using namespace std;

int pickNextAttribute(char **trainningSet, set<int> examples, set<int> hashsetCol );


#endif /* InformationGain_hpp */

