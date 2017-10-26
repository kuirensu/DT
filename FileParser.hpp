//
//  FileParser.hpp
//  DecisionTree
//
//  Created by Kuiren Su on 10/17/17.
//  Copyright © 2017 Kuiren Su. All rights reserved.
//

#ifndef FileParser_hpp
#define FileParser_hpp

#include <stdio.h>
using namespace std;
int parseFileOne(string filename, char trainingSet[][23], char testingSet[][23], int rows80, int rows20);
int parseFileTwo(string filename,char trainingSet[][23], char validationSet[][23], char testingSet[][23], int rows60, int rows20);
int numberOfRows(string filename);
int numberOfColumns(string filename);
#endif /* FileParser_hpp */

