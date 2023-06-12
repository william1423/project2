#include "datapoint.h"
#include <sstream>

DataPoint::DataPoint(string input) {
    this->preParsedForm = input;
    istringstream iss(input);
    string cur;
    float convert;
    bool first = true;
    while (iss >> cur) {
        if (first == true) {
            if (stof(cur) == 1) {
               this->className = 1; 
            }
            else if(stof(cur) == 2) {
                this->className = 2;
            }
            else {
                cout << "Class error" << endl;
                break;
            }
            first = false;
        }
        else {
            this->features.push_back(stof(cur));
        }
    }
}

int DataPoint::getClassName() {
    return this->className;
}

float DataPoint::getFeatureVal(int input) {
    return this->features[input];
}

string DataPoint::getPreParsedForm() {
    return this->preParsedForm;
}

int DataPoint::getVectorSize() {
    return this->features.size();
}