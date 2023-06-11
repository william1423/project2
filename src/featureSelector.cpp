#include "featureSelector.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_set>

using namespace std;

void FeatureSelector::Start(){
    // string input;
    // cout << "Enter filepath: ";
    // cin >> input;
    // this->ParseData(input);
    this->ParseData("../dataset_small.txt");
    this->NearestNeighbor();
}

void FeatureSelector::ParseData(string path) {
    fstream file(path);
    string input, output;
    while (getline(file, input)) {
        vec.push_back(DataPoint(input));
    }
}

bool FeatureSelector::NearestNeighbor() {
    string input, cur;
    int select;
    unordered_set<int> chosen;
    bool duplicate = false;

    cout << "Choose features separated by a space (ex. 1 4 9)" << endl;
    getline(cin, input);
    istringstream iss(input);

    while (iss) {
        iss >> cur;
        select = stoi(cur);
        if (select < 1 || select > 10) {
            cout << "ERROR: An entered feature(s) is outside the range of 1 to 10" << endl;
            return false;
        }
        else if (chosen.find(select) != chosen.end()){
            duplicate = true;
        }
        else {
            this->selectedFeatures.push_back(select);
            chosen.insert(select);
        }
    }

    if (duplicate == true) {
        cout << "Warning: Duplicate feature(s) detected, removing duplicates" << endl;
    }

    return true;
}