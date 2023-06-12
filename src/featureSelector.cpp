#include "featureSelector.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_set>
#include <cmath>

using namespace std;

void FeatureSelector::Start(){
    // string input;
    // cout << "Enter filepath: ";
    // cin >> input;
    // this->ParseData(input);
    this->Train("../dataset_large.txt");
    this->NearestNeighborFeatures();
    this->Validate();
}

void FeatureSelector::Train(string path) {
    fstream file(path);
    string input, output;
    while (getline(file, input)) {
        vec.push_back(DataPoint(input));
    }
}

int FeatureSelector::Test() {
    int option = -1;
    int vecIndex = -1;
    float min;
    int testClass = -1;
    float cur;

    while (option < 1 || option > 2) {
        cout << "Enter 1 to test using a datapoint from training data" << endl;
        cout << "Enter 2 to test using a new datapoint" << endl;
        cin >> option;
        cin.ignore();
        cout << endl;
    }

    if (option == 1) {
        if (this->vec.size() == 1) {
            cout << "Cannot test with option 1 when there is only one datapoint in training data" << endl;
            return -1;
        }
        while (vecIndex < 0 || vecIndex >= this->vec.size()) {
            cout << "Select the index of the datapoint, which is any number from 0 to " << this->vec.size() - 1 << endl;
            cin >> vecIndex;
            cout << endl;
        }

        DataPoint testPoint(this->vec[vecIndex].getPreParsedForm());

        if(vecIndex != 0) {
            min = this->getEuclideanDistance(testPoint, this->vec[0]);
            testClass = this->vec[0].getClassName();
        }
        else {
            min = this->getEuclideanDistance(testPoint, this->vec[1]);
            testClass = this->vec[1].getClassName();
        }

        for (int i = 0; i < this->vec.size(); i++) {
            if (i == vecIndex) {
                continue;
            }
            cur = this->getEuclideanDistance(testPoint, this->vec[i]);
            if (cur < min) {
                min = cur;
                testClass = this->vec[i].getClassName();
            }
        }
        return testClass;
    }
    else if (option == 2) {
        string newDatapoint;
        cout << "Enter a new datapoint in the same format as the ones in the text files" << endl;
        getline(cin, newDatapoint);
        DataPoint testPoint(newDatapoint);
        min = this->getEuclideanDistance(testPoint, this->vec[0]);
        testClass = this->vec[0].getClassName();
        for (int i = 1; i < this->vec.size(); i++) {
            cur = this->getEuclideanDistance(testPoint, this->vec[i]);
            if (cur < min) {
                min = cur;
                testClass = this->vec[i].getClassName();
            }
        }
        return testClass;
    }
    else {
        cout << "ERROR in feature selector test" << endl;
        return -1;
    }
}

bool FeatureSelector::NearestNeighborFeatures() {
    string input, cur;
    int select;
    unordered_set<int> chosen;
    bool duplicate = false;

    cout << "Choose features separated by a space (ex. 1 4 9)" << endl;
    getline(cin, input);
    istringstream iss(input);

    while (iss >> cur) {
        select = stoi(cur);
        if (select < 1 || select > this->vec[0].getVectorSize()) {
            cout << "ERROR: An entered feature(s) is outside the range of 1 to " << this->vec[0].getVectorSize() << endl;
            return false;
        }
        else if (chosen.find(select) != chosen.end()){
            duplicate = true;
        }
        else {
            this->selectedFeatures.push_back(select - 1);
            chosen.insert(select);
        }
    }

    if (duplicate == true) {
        cout << "Warning: Duplicate feature(s) detected, removing duplicates" << endl;
    }

    return true;
}

float FeatureSelector::getEuclideanDistance(DataPoint input, DataPoint data) {
    float sum = 0;
    if (this->selectedFeatures.size() == 0) {
        cout << "ERROR: no selected features";
        return -1;
    }

    int featureNum = -1;
    for (int i = 0; i < this->selectedFeatures.size(); i++) {
        featureNum = this->selectedFeatures[i];
        sum += pow((input.getFeatureVal(featureNum) - data.getFeatureVal(featureNum)), 2);
    }
    return sqrt(sum);
}

int FeatureSelector::TestOption1(int vecIndex, DataPoint testPoint) {
    float min;
    int testClass = -1;
    float cur;

    if (this->vec.size() == 1) {
        cout << "Cannot test with option 1 when there is only one datapoint in training data" << endl;
        return -1;
    }

    if(vecIndex != 0) {
        min = this->getEuclideanDistance(testPoint, this->vec[0]);
        testClass = this->vec[0].getClassName();
    }
    else {
        min = this->getEuclideanDistance(testPoint, this->vec[1]);
        testClass = this->vec[1].getClassName();
    }
    
    for (int i = 0; i < this->vec.size(); i++) {
        if (i == vecIndex) {
            continue;
        }
        cur = this->getEuclideanDistance(testPoint, this->vec[i]);
        if (cur < min) {
            min = cur;
            testClass = this->vec[i].getClassName();
        }
    }
    return testClass;
    
}

void FeatureSelector::Validate() {
    float numCorrect = 0;

    for (int i = 0; i < this->vec.size(); i++) {
        DataPoint testPoint(this->vec[i].getPreParsedForm());
        if (this->TestOption1(i, testPoint) == testPoint.getClassName()) {
            numCorrect += 1;
        }
    }

    cout << "Accuracy: " << numCorrect / this->vec.size() << endl; 
}


