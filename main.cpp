//
//  main.cpp
//  DecisionTree
//
//  Created by Kuiren Su on 10/17/17.
//  Copyright © 2017 Kuiren Su. All rights reserved.
//
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
    int cols = numberOfColumns(argv[1]);
    //cout << rows20 <<  " " << rows60<<" " << rows80<<  endl;
    char **trainingSetOne = new char* [rows80]; //80%
    for (int i = 0; i < rows80; i++) {
        trainingSetOne[i] = new char [cols];
    }
    char **testingSetOne = new char *[rows20]; //20%
    for (int i = 0; i < rows20; i++) {
        testingSetOne[i] = new char [cols];
    }
    int successOne = parseFileOne(argv[1], trainingSetOne,  testingSetOne, rows80, rows20 , cols); 

    if (!successOne){
        cout << "failed parsing file..." << endl;
    }
    set<int> examplesOne;
    for (int i = 0; i < rows80; i ++ ){
        examplesOne.insert(i);
    }
    set<int> attributesOne;
    for (int i = 1; i < cols; i ++ ){
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
    for (int i = 0; i < rows80; i++) {
        delete[] trainingSetOne[i];
    }
    delete[] trainingSetOne;
    for (int i = 0; i < rows20; i++) {
        delete[] testingSetOne[i];
    }
    delete []testingSetOne;
    //part 2
    cout << "********Part 2*********" <<endl;
    cout << "depth train% valid%" << endl;
    double maxValidationAccuracy = 0.0;
    int bestDepth = 0;
    double maxTestingAccuracy = 0.0;
    
    //allocate arrays 
    char** trainingSetTwo ; // 60%
    trainingSetTwo = new char *[rows60];
    for (int j = 0; j < rows60;j++) {
        trainingSetTwo[j] = new char [cols];
    }
    char** validationSetTwo ; // 20%
    validationSetTwo = new char *[rows20];
    for (int j = 0; j < rows20; j++) {
        validationSetTwo[j] = new char [cols];
    }
    char** testingSetTwo ; //20%
    testingSetTwo = new char *[rows20];
    for (int j = 0; j < rows20; j++) {
        testingSetTwo[j] = new char [cols];
    }
    
    
    
    for (int i = 1; i < 16; i++){
        cout << " " << i << "\t" ;
        
        int successTwo = parseFileTwo(argv[1], trainingSetTwo, validationSetTwo, testingSetTwo, rows60, rows20,cols);
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
        //printTree(rootTwo);

    }
    stringstream maxTestingAccuracyCorrectness;
    maxTestingAccuracyCorrectness<<fixed<< setprecision(2) <<100*maxTestingAccuracy;
    cout << "The best depth is at depth: " <<bestDepth << endl ;
    cout << "Here the testing set accuracy is: " << maxTestingAccuracyCorrectness.str() <<"%"<< endl;
    
    
    for (int j = 0; j < rows60;j++) {
        delete[] trainingSetTwo[j] ;
    }
    delete [] trainingSetTwo;
    for (int j = 0; j < rows20; j++) {
        delete[] validationSetTwo[j];
    }
    delete []validationSetTwo;
    for (int j = 0; j < rows20; j++) {
        delete[] testingSetTwo[j] ;
    }
    delete []testingSetTwo;
    return 0;
}


