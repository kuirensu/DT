//
//  FileParser.cpp
//  DecisionTree
//
//  Created by Kuiren Su on 10/17/17.
//  Copyright © 2017 Kuiren Su. All rights reserved.
//
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <vector>
#include "FileParser.hpp"

const char* const DELIMITER = ",";
const int MAX_CHARS_PER_LINE = 46;
const int TRAINING = 0;
const int VALIDATION = 1;
const int TESTING = 2;
using namespace std;

//creating two random sets
int parseFileOne(string filename, char trainingSet [][23], char testingSet[][23], int rows80, int rows20 ){
    int MAX_ROW_TWENTYPERCENT = rows20;
    int MAX_ROW_EIGHTYPERCENT = rows80;
    ifstream fin;
    fin.open(filename);
    if (!fin.good())
        return -1;
    string dummyLine;
    getline(fin, dummyLine);
    //cout << dummyLine << endl;
    //int row = 0;
    int trainingRow = 0;
    int testingRow = 0;
    srand(time( NULL ));
    while (!fin.eof()){
        //generate set to put data randomly
        int random_integer;
        int tl = -1;
        if (trainingRow != MAX_ROW_EIGHTYPERCENT  && testingRow != MAX_ROW_TWENTYPERCENT){ //tvl: fff
            random_integer = rand()%5; //0,1,2,3,4
            if (random_integer < 4){
                tl = TRAINING;
            }else {
                tl = TESTING;
            }
            
        }else if(trainingRow == MAX_ROW_EIGHTYPERCENT && testingRow != MAX_ROW_TWENTYPERCENT){ //tvl: tff
            tl = TESTING;
        }else if(trainingRow != MAX_ROW_EIGHTYPERCENT && testingRow == MAX_ROW_TWENTYPERCENT){ //tvl: ftf or fft
            tl = TRAINING;
        }else { //tl: tt
            //cout << "should not reach" << endl;
            break;
        }
        
        char buf[MAX_CHARS_PER_LINE];
        fin.getline(buf, MAX_CHARS_PER_LINE);
        //cout<< "buf is : " << buf << endl;
        char* chars = strtok(buf, DELIMITER);
        int index = 0;
        while (chars != NULL){
            //data[row][index] = chars[0];
            if(tl == TRAINING){
                trainingSet[trainingRow][index] = chars[0];
            }else {
                testingSet[testingRow][index] = chars[0];
            }
            //cout << "Row: "<< row << " index: " << index << " token: " << data[row][index] << endl;
            chars = strtok (NULL, ",");
            index++;
        }
        //row++;
        if(tl == TRAINING){
            trainingRow += 1;
        }else {
            testingRow += 1;
        }
        //cout << "trainingRow: "<< trainingRow << " testingRow: " << testingRow << endl;
    }
    //done parsing file
    fin.close();
    return 1;
}





int parseFileTwo(string filename, char trainingSet [][23], char validationSet [][23], char testingSet[][23] ,int rows60, int rows20){
    int MAX_ROW_TWENTYPERCENT = rows20;
    int MAX_ROW_SIXTYPERCENT = rows60;
    ifstream fin;
    fin.open(filename);
    if (!fin.good())
        return -1;
    string dummyLine;
    getline(fin, dummyLine);
    //cout << dummyLine << endl;
    //int row = 0;
    int trainingRow = 0;
    int validationRow = 0;
    int testingRow = 0;
    srand(time( NULL ));
    while (!fin.eof()){
        //generate set to put data randomly
        int random_integer;
        int tvl = -1;
        if (trainingRow != MAX_ROW_SIXTYPERCENT && validationRow != MAX_ROW_TWENTYPERCENT && testingRow != MAX_ROW_TWENTYPERCENT){ //tvl: fff
            random_integer = rand()%5; //0,1,2,3,4
            if (random_integer < 3){
                tvl = TRAINING;
            }else if(random_integer == 3){
                tvl = VALIDATION;
            }else {
                tvl = TESTING;
            }
            
        }else if(trainingRow == MAX_ROW_SIXTYPERCENT && validationRow != MAX_ROW_TWENTYPERCENT && testingRow != MAX_ROW_TWENTYPERCENT){ //tvl: tff
            random_integer = rand()%2; //0,1
            if (random_integer == 0){
                tvl = VALIDATION;
            }else {
                tvl = TESTING;
            }
        }else if(trainingRow != MAX_ROW_SIXTYPERCENT && ((validationRow != MAX_ROW_TWENTYPERCENT) ^ (testingRow != MAX_ROW_TWENTYPERCENT))){ //tvl: ftf or fft
            random_integer = rand()%4; //0,1,2,3
            if (random_integer < 3){
                tvl = TRAINING;
            }else {
                if (validationRow != MAX_ROW_TWENTYPERCENT ){
                    tvl = VALIDATION;
                }else{
                    tvl = TESTING;
                }
                
            }
        }else if (! (trainingRow == MAX_ROW_SIXTYPERCENT && validationRow == MAX_ROW_TWENTYPERCENT && testingRow == MAX_ROW_TWENTYPERCENT)){ //tvl: ftt, tft, ttf
            //only one row not reached max //
            if(trainingRow != MAX_ROW_SIXTYPERCENT){
                tvl = TRAINING;
            }
            if(validationRow != MAX_ROW_TWENTYPERCENT){
                tvl = VALIDATION;
            }
            if(testingRow != MAX_ROW_TWENTYPERCENT){
                tvl = TESTING;
            }
        }else { //tvl: ttt
            //cout << "should not reach" << endl;
            break;
        }
        
        
        char buf[MAX_CHARS_PER_LINE];
        fin.getline(buf, MAX_CHARS_PER_LINE);
        //cout<< "buf is : " << buf << endl;
        char* chars = strtok(buf, DELIMITER);
        int index = 0;
        while (chars != NULL){
            //data[row][index] = chars[0];
            if(tvl == TRAINING){
                trainingSet[trainingRow][index] = chars[0];
            }else if (tvl == VALIDATION){
                validationSet[validationRow][index] = chars[0];
            }else {
                testingSet[testingRow][index] = chars[0];
            }
            //cout << "Row: "<< row << " index: " << index << " token: " << data[row][index] << endl;
            chars = strtok (NULL, ",");
            index++;
        }
        //row++;
        if(tvl == TRAINING){
            trainingRow += 1;
        }else if (tvl == VALIDATION){
            validationRow += 1;
        }else {
            testingRow += 1;
        }
        //cout << "trainingRow: "<< trainingRow << " validationRow: " << validationRow << " testingRow: " << testingRow << endl;
    }
    //done parsing file
    fin.close();
    return 1;
}

int numberOfRows(string filename){
    ifstream fin;
    fin.open(filename);
    if (!fin.good())
        return -1;
    string dummyLine; //skip description line
    getline(fin, dummyLine);
    int rows = 0;
    while (!fin.eof()){
        getline(fin, dummyLine);
        if(dummyLine != ""){
            rows ++ ;
        }
    }
    fin.close();
    return rows;
}
int numberOfColumns(string filename){
    char CDELIMITER = ',';
    ifstream fin;
    fin.open(filename);
    if (!fin.good())
        return -1;
    string fistLine; //skip description line
    getline(fin, fistLine);
    istringstream ss(fistLine);
    vector<string> vec;
    while (getline(ss, fistLine, CDELIMITER))
        vec.push_back(fistLine);
    
    for (size_t i = 0; i < vec.size(); i++)
        std::cout << "Token[" << i << "] = " << vec[i] << "\n";
    return int(vec.size());
}

