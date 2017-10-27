//
//  ConstructTree.cpp
//  DT
//
//  Created by Kuiren Su on 10/20/17.
//  Copyright © 2017 Kuiren Su. All rights reserved.
//
//
#include "ConstructTree.hpp"
#include <map>
#include <set>
#include "InformationGain.hpp"
#include <iostream>
using namespace std;
TreeNode::TreeNode(int result){
        this->result = result;
    }
TreeNode::TreeNode(int attribute, map<char, set<int>> features):branches() {
        this->attribute = attribute;
        this->features = features;
        //this->examples = examples;
        
    }
int TreeNode::getAttribute(){
    return this->attribute;
}
int TreeNode::getResult(){
    return this->result;
}
map<char ,TreeNode*> TreeNode::getBranches(){
    return this->branches;
}
void TreeNode::addSubtree(char feature, TreeNode* node  ){
    this->branches.insert(pair<char,TreeNode*>(feature, node));
}

int findPlurality (set<int> examples, char **trainingSet){
    int zeros = 0;
    int ones = 0;
    for (auto const& it : examples){
        if(trainingSet[it][0] == '1'){
            ones += 1;
        }else {
            zeros += 1;
        }
    }
    return (ones > zeros) ? 1 : 0;
}

bool haveSameClassification(set<int> examples,char**trainingSet){
    int zeros = 0;
    int ones = 0;
    for (auto const& it : examples){
        if(trainingSet[it][0] == '1'){ //result is one
            ones += 1;
        }else {
            zeros += 1;
        }
        if (zeros > 0 && ones > 0){
            return false;
        }
       // cout<<"zeros : " << zeros << "  ones: " << ones << endl;
    }
    return true;
}
//examples is not empty and only one result possible thus we only loop once
int findClassification(set<int> examples, char** trainingSet){
    for (auto const& it : examples){
        if(trainingSet[it][0] == '1'){
            return 1;
        }else {
            return 0;
        }
    }
    return -1;
}
//find all features of an attribute and their corresponding examples row numbers
map<char, set<int>> featuresOfAttribute(int attribute, set<int> examples, char** trainingSet){
    map<char, set<int>> features;
    for (auto const& it : examples){//all examples row numbers
        map<char, set<int>>::iterator feature = features.find(trainingSet[it][attribute]);
        if(feature == features.end() ){
            set<int> childExamples ;
            childExamples.insert(it);
            features[trainingSet[it][attribute]] = childExamples;
        }else {
            feature->second.insert(it);
        }
    }
    return features;
}
//part one
TreeNode * decisionTreeLearningOne(set<int> childExamples, set<int> parentExamples, set<int> attributes, char **trainingSet) {
    if (childExamples.size() == 0 ){
        //cout<<"childExamples.size() == 0"<<endl;
        int plurality = findPlurality(parentExamples,trainingSet);
        TreeNode *node = new TreeNode(plurality);
        return node;
    }else if (haveSameClassification(childExamples,trainingSet)){
        //cout<<"haveSameClassification"<<endl;
        TreeNode *node = new TreeNode(findClassification(childExamples,trainingSet));
        return node;
    }else if (attributes.empty()){
        //cout<<"reach3"<<endl;
        TreeNode *node = new TreeNode(findPlurality(childExamples,trainingSet));
        return node;
    }else {
        //cout << "reach 4" << endl;
        int attribute = pickNextAttribute(trainingSet, childExamples ,attributes); 
        //cout <<"pickNextAttribute: " <<attribute << endl;
        //attributes = attributes - A;
        attributes.erase(attribute);
        if(attributes.empty()){
            //cout <<"attributes is empty"<< endl;
        }else {
            //cout<<"attributes size is " <<attributes.size() << endl;
        }
        map<char, set<int>> features = featuresOfAttribute(attribute, childExamples, trainingSet);
        //cout<< "number of features at attribute " <<attribute << " is " <<features.size() << endl;
        TreeNode *node = new TreeNode(attribute, features);
        for (auto const& it : features){
            set<int> exs = it.second;
            TreeNode * subTree = decisionTreeLearningOne(exs,childExamples,attributes,trainingSet);
            node->addSubtree(it.first, subTree);
        }
        return node;
    }
}

//part two*****************
TreeNode * decisionTreeLearningTwo(set<int> childExamples, set<int> parentExamples, set<int> attributes, char** trainingSet, int depth, int currentDepth) {
    
    if (childExamples.size() == 0 ){
        //cout<<"childExamples.size() == 0"<<endl;
        int plurality = findPlurality(parentExamples,trainingSet);
        TreeNode *node = new TreeNode(plurality);
        return node;
    }else if (haveSameClassification(childExamples,trainingSet)){
        //cout<<"haveSameClassification"<<endl;
        TreeNode *node = new TreeNode(findClassification(childExamples,trainingSet));
        return node;
    }else if (attributes.empty()){
        //cout<<"reach3"<<endl;
        TreeNode *node = new TreeNode(findPlurality(childExamples,trainingSet));
        return node;
    }else if (currentDepth == depth ){ //reach max depth limit
        int plurality = findPlurality(parentExamples,trainingSet);
        TreeNode *node = new TreeNode(plurality);
        return node;
    }else {
        
        int attribute = pickNextAttribute(trainingSet, childExamples ,attributes);
        //cout <<"pickNextAttribute: " <<attribute << endl;
        //attributes = attributes - A;
        attributes.erase(attribute);
        if(attributes.empty()){
            //cout <<"attributes is empty"<< endl;
        }else {
            //cout<<"attributes size is " <<attributes.size() << endl;
        }
        map<char, set<int>> features = featuresOfAttribute(attribute, childExamples, trainingSet);
        //cout<< "number of features at attribute " <<attribute << " is " <<features.size() << endl;
        TreeNode *node = new TreeNode(attribute, features);
        currentDepth += 1;
        for (auto const& it : features){
            set<int> exs = it.second;
            TreeNode * subTree = decisionTreeLearningTwo(exs,childExamples,attributes,trainingSet,depth,currentDepth);
            node->addSubtree(it.first, subTree);
        }
        return node;
    }
}


void printTree (TreeNode * node) {
    if (node != NULL){
        cout<< "Node with attribute: "<<node->getAttribute() <<" has result: " << node->getResult() << endl;
        cout<< "branches are: " << endl;
        if(node->getBranches().size() != 0){
            for (auto const& it : node->getBranches()){
                cout<<"Attribute: "<<node->getAttribute() << "'s feature :   " << it.first << "   has subtree: " <<endl ;
                printTree (it.second);
            }
        }
    }
}
bool checkCorrectness(TreeNode * node, char *example){
    if(node->getResult() != -1){
        if ((example[0] == '0' and node->getResult() == 0) || (example[0] == '1' and node->getResult() == 1) ){
            return true;
        }else{
            return false;
        }
    }
    char feature = example[node->getAttribute()];
    map<char ,TreeNode*> branches = node->getBranches();
    if (branches.find(feature) == branches.end()){
        return false;
    }
    TreeNode * nextNode = branches.find(feature)->second;
    
    return checkCorrectness(nextNode, example);
}

double percentageOfCorrectness (TreeNode * root, int rows, char **testingSet) {
    int correctness = 0;
    for (int i = 0 ; i < rows ; i++){
        if(checkCorrectness(root, testingSet[i])){
            correctness += 1;
        }
    }
    return (double(correctness)/rows);
    
}




