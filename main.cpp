//
//  main.cpp
//  DecisionTree
//
//  Created by Kuiren Su on 10/17/17.
//  Copyright © 2017 Kuiren Su. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <set>
#include <utility>
#include <map>
#include "InformationGain.hpp"
#include "FileParser.hpp"
#include "ConstructTree.hpp"
using namespace std;
int main(int argc, const char * argv[]) {
    //char data[5644][23];
    if (argc != 2){
        return -1;
    }
    
    //part 1
    int rows = numberOfRows(argv[1]);
    int rows80 = (rows * 4)/5;
    int rows20 = rows - rows80;
    int rows60 = rows - 2*rows20;
    
    //cout << rows20 <<  " " << rows60<<" " << rows80<<  endl;
    char trainingSetOne [rows80][23]; //80%
    char testingSetOne [rows20][23]; //20%
    int successOne = parseFileOne(argv[1],trainingSetOne,  testingSetOne, rows80, rows20 );

    if (!successOne){
        cout << "failed parsing file..." << endl;
    }
    set<int> examplesOne;
    for (int i = 0; i < rows80; i ++ ){
        examplesOne.insert(i);
    }
    set<int> attributesOne;
    for (int i = 1; i < 23; i ++ ){
        attributesOne.insert(i);
    }
    TreeNode * root = decisionTreeLearningOne(examplesOne, examplesOne, attributesOne, trainingSetOne);
    
    stringstream trainingSetOneCorrectness;
     trainingSetOneCorrectness<<fixed<< setprecision(2) <<100*percentageOfCorrectness (root, rows80, trainingSetOne );
    stringstream testingSetOneCorrectness;
    testingSetOneCorrectness<<fixed<< setprecision(2) << 100*percentageOfCorrectness (root, rows20, testingSetOne );
    cout << "********Part 1*********" <<endl;
    cout << "Accuracy for trainingSet(80%) is : " <<trainingSetOneCorrectness.str() << "%"<< endl;
    cout << "Accuracy for testingSet(20%) is : " <<testingSetOneCorrectness.str()<<"%"<< endl;
     
    
    //part 2
    cout << "********Part 2*********" <<endl;
    cout << "depth train% valid%" << endl;
    double maxValidationAccuracy = 0.0;
    int bestDepth = 0;
    double maxTestingAccuracy = 0.0;
    for (int i = 1; i < 16; i++){
        cout << " " << i << "\t" ;
        char trainingSetTwo [rows60][23]; // 60%
        char validationSetTwo [rows20][23]; // 20%
        char testingSetTwo [rows20][23]; //20%
        int successTwo = parseFileTwo(argv[1], trainingSetTwo, validationSetTwo, testingSetTwo, rows60, rows20);
        // cout<< "success: " <<success << endl;
        if (!successTwo){
            cout << "failed parsing file..." << endl;
        }
        
        set<int> examplesTwo;
        for (int i = 0; i < rows60; i ++ ){
            examplesTwo.insert(i);
        }
        set<int> attributesTwo;
        for (int i = 1; i < 23; i ++ ){
            attributesTwo.insert(i);
        }
        
        TreeNode * rootTwo = decisionTreeLearningTwo(examplesTwo, examplesTwo, attributesTwo, trainingSetTwo, i, 0);
        double validationAccuracy = percentageOfCorrectness (rootTwo, rows20 , validationSetTwo );
        if (validationAccuracy > maxValidationAccuracy){
            maxValidationAccuracy = validationAccuracy;
            bestDepth = i;
            maxTestingAccuracy = percentageOfCorrectness (rootTwo, rows20, testingSetTwo );
        }
//        cout << "Percentage Of Correctness for trainingSetTwo at depth " << i << " is : " <<percentageOfCorrectness (rootTwo, (sizeof(trainingSetTwo)/sizeof(*trainingSetTwo)) , trainingSetTwo )<< endl;
//        cout << "Percentage Of Correctness for validationSetTwo at depth " << i << " is : " <<validationAccuracy<< endl;
       stringstream trainingSetTwoCorrectness;
        trainingSetTwoCorrectness <<fixed<< setprecision(2) <<  100*percentageOfCorrectness (rootTwo, rows60 , trainingSetTwo );
        stringstream validationAccuracyTwoCorrectness;
        validationAccuracyTwoCorrectness << fixed << setprecision(2)<<100*validationAccuracy;
        cout <<" "<< trainingSetTwoCorrectness.str()<< "% \t" <<validationAccuracyTwoCorrectness.str()<< "% " <<endl;

    }
    stringstream maxTestingAccuracyCorrectness;
    maxTestingAccuracyCorrectness<<fixed<< setprecision(2) <<100*maxTestingAccuracy;
    cout << "The best depth is at depth: " <<bestDepth << endl ;
    cout << "Here the testing set accuracy is: " << maxTestingAccuracyCorrectness.str() <<"%"<< endl;
    
    
    return 0;
}


