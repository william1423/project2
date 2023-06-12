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
    this->ParseData("../dataset_small.txt");
    this->NearestNeighborFeatures();
    DataPoint test1("2.0000000e+000  2.0000000e+000  2.0166239e+000  3.1861294e+000  2.5771315e+000  1.3274516e+000  1.7960005e+000  4.1778747e+000  2.0219016e+000  1.7237110e+000  1.5847779e+000");
    DataPoint test2("2.0000000e+000  1.0000000e+000  2.0166239e+000  3.1861294e+000  2.5771315e+000  1.3274516e+000  1.7960005e+000  4.1778747e+000  2.0219016e+000  1.7237110e+000  1.5847779e+000");
    this->getEuclideanDistance(test1, test2);
}

void FeatureSelector::ParseData(string path) {
    fstream file(path);
    string input, output;
    while (getline(file, input)) {
        vec.push_back(DataPoint(input));
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
        if (select < 1 || select > 10) {
            cout << "ERROR: An entered feature(s) is outside the range of 1 to 10" << endl;
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


