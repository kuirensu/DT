//
//  ConstructTree.hpp
//  DT
//
//  Created by Kuiren Su on 10/20/17.
//  Copyright © 2017 Kuiren Su. All rights reserved.
//
//
#ifndef ConstructTree_hpp
#define ConstructTree_hpp
#include <map>
#include <set>
#include <stdio.h>
using namespace std;
class TreeNode {
private:
    int attribute = -1;      // col number
    map<char, set<int>> features;  //Vk and set of row numbers(child examples)
    //set<int> examples ; //parent examples
    int result = -1;
    map<char, TreeNode*> branches; //char = feature
public:
    TreeNode(int result);
    TreeNode(int attribute, map<char, set<int>> features);
    ~TreeNode();
    int getAttribute();
    int getResult();
    map<char ,TreeNode*> getBranches();
    void setResult(int result);
    void addSubtree(char feature, TreeNode* node);
};
TreeNode * decisionTreeLearningOne(set<int> childExamples, set<int> parentExamples, set<int> attributes, char **trainingSet) ;
TreeNode * decisionTreeLearningTwo(set<int> childExamples, set<int> parentExamples, set<int> attributes, char **trainingSet, int depth, int currentDepth);
void printTree(TreeNode *node);
double percentageOfCorrectness (TreeNode * root, int rows, char **testingSet);
#endif /* ConstructTree_hpp */
