//
//  FileParser.hpp
//  DecisionTree
//
//  Created by Kuiren Su on 10/17/17.
//  Copyright © 2017 Kuiren Su. All rights reserved.
//
//
#ifndef FileParser_hpp
#define FileParser_hpp

#include <stdio.h>
using namespace std;
int parseFileOne(string filename,char **trainingSet, char **testingSet, int rows80, int rows20, int cols);
int parseFileTwo(string filename,char **trainingSet, char **validationSet, char **testingSet, int rows60, int rows20,int cols);
int numberOfRows(string filename);
int numberOfColumns(string filename);
#endif /* FileParser_hpp */

