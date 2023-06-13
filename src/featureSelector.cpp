#include "featureSelector.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_set>
#include <cmath>

using namespace std;

void FeatureSelector::ForwardSelection () {
    float globalAccuracy = largestClassSize / this->vec.size();
    float localAccuracy;
    vector<int> optimalPath;

    cout << endl;
    cout << "This dataset has " << this->remainingFeatures.size() << " features (not including the class attribute), ";
    cout << "with " << this->vec.size() << " instances" << endl << endl;

    cout << "Running nearest neighbor with no features (defualt rate), using \"leaving-one-out\" evaluation, ";
    cout << "I get an accuracy of " << globalAccuracy << endl << endl;
    cout << "Beginning search." << endl << endl;

    

    int position = 0;
    int pushPosition = 0;
    float cur;
    list<int>::iterator it = this->remainingFeatures.begin();
    list<int>::iterator remove;

    for(int i = 0; i < 3; i++) {// while (this->remainingFeatures.size()) {
        it = this->remainingFeatures.begin();
        localAccuracy = 0;

        while (it != this->remainingFeatures.end()) {
            this->newFeature = (*it);
            cur = this->Validate();

            cout << "   Using feature(s) {" << (*it);
            for(int j = this->path.size() - 1; j >= 0; j--) {
                cout  << ", " << this->path[j];
            }
            cout <<  "} accuracy is " << cur << endl;

            if (cur > localAccuracy) {
                localAccuracy = cur;
                remove = it;
            }
            it++;
        }

        this->path.push_back((*remove));
        this->remainingFeatures.erase(remove);

        if (localAccuracy > globalAccuracy) {
            globalAccuracy = localAccuracy;
            optimalPath = this->path;
        }

        cout << endl;
        cout << "Feature set {";
        for(int j = this->path.size() - 1; j > 0; j--) {
            cout  << this->path[j] << ", ";
        }
        cout << this->path[0];
        cout << "} was best, accuracy is " << localAccuracy;
        if (localAccuracy < globalAccuracy) {
            cout << " (Warning: Accuracy has decreased) from overall best set";
        }
        cout << endl << endl;
    }
    cout << "Finished Search!! The best feature subset is {";
    for(int i = optimalPath.size() - 1; i > 0; i--) {
            cout  << optimalPath[i] << ", ";
        }
    cout << optimalPath[0] << "}, which has an accuracy of " << globalAccuracy << endl;   
}

void FeatureSelector::BackwardElimination () {
    float globalAccuracy = largestClassSize / this->vec.size();
    float localAccuracy;
    vector<int> optimalPath;

    cout << endl;
    cout << "This dataset has " << this->remainingFeatures.size() << " features (not including the class attribute), ";
    cout << "with " << this->vec.size() << " instances" << endl << endl;

    cout << "Running nearest neighbor with no features (defualt rate), using \"leaving-one-out\" evaluation, ";
    cout << "I get an accuracy of " << globalAccuracy << endl << endl;
    cout << "Beginning search." << endl << endl;

    

    int position = 0;
    int pushPosition = 0;
    float cur;

    for (int i = 0; i < this->remainingFeatures.size(); i++) {
        this->path.push_back(i + 1);
    }

    int removeIndex;

    while (this->path.size()) {
        localAccuracy = 0;
        
        for(int j = 0; j < this->path.size(); j++) {
            this->removedFeature = this->path[j];
            cur = this->Validate();

            cout << "   Using feature(s) {";
            for(int k = 0; k < this->path.size(); k++) {
                if (this->path[k] != this->removedFeature) {
                    cout  << ", " << this->path[k];
                }
            }
            cout <<  "} accuracy is " << cur << endl;

            if (cur > localAccuracy) {
                localAccuracy = cur;
                removeIndex = j;
            }
        }

        this->path.erase(this->path.begin() + removeIndex);

        if (localAccuracy > globalAccuracy) {
            globalAccuracy = localAccuracy;
            optimalPath = this->path;
        }

        cout << endl;
        cout << "Feature set {";
        for(int j = this->path.size() - 1; j > 0; j--) {
            cout  << this->path[j] << ", ";
        }
        cout << this->path[0];
        cout << "} was best, accuracy is " << localAccuracy;
        if (localAccuracy < globalAccuracy) {
            cout << " (Warning: Accuracy has decreased) from overall best set";
        }
        cout << endl << endl;
    }
    cout << "Finished Search!! The best feature subset is {";
    for(int i = optimalPath.size() - 1; i > 0; i--) {
            cout  << optimalPath[i] << ", ";
        }
    cout << optimalPath[0] << "}, which has an accuracy of " << globalAccuracy << endl; 
}

void FeatureSelector::Start(){
    string input;
    cout << "Enter filepath: ";
    cin >> input;
    cin.ignore();
    input = "../" + input;

    this->Train(input);
    for (int i = 1; i <= this->vec[0].getVectorSize(); i++) {
        this->remainingFeatures.push_back(i);
    }

    int class1Count = 0;
    int class2Count = 0;
    for (int i = 0; i < this->vec.size(); i++) {
        if (vec[i].getClassName() == 1) {
            class1Count++;
        }
    }

    class2Count = this->vec.size() - class1Count;

    if (class1Count >= class2Count) {
        this->largestClass = 2;
        this->largestClassSize = class1Count;
    }
    else {
        this->largestClass = 2;
        this->largestClassSize = class2Count;
    }

    this->BackwardElimination();
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
            this->remainingFeatures.push_back(select - 1);
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
    int pathIndex;
    for (int i = 0; i < this->path.size(); i++) {
        if (this->path[i] != removedFeature) {
            pathIndex = this->path[i] - 1;
            sum += pow((input.getFeatureVal(pathIndex) - data.getFeatureVal(pathIndex)), 2);
        }
    }

    if (newFeature != -1) {
        sum += pow((input.getFeatureVal(this->newFeature - 1) - data.getFeatureVal(this->newFeature - 1)), 2);
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

float FeatureSelector::Validate() {
    float numCorrect = 0;

    for (int i = 0; i < this->vec.size(); i++) {
        DataPoint testPoint(this->vec[i].getPreParsedForm());
        if (this->TestOption1(i, testPoint) == testPoint.getClassName()) {
            numCorrect += 1;
        }
    }
    float result = numCorrect / this->vec.size();
    // cout << "Accuracy: " << result << endl; 
    return result;
}


