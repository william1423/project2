#include "datapoint.h"
#include <sstream>

DataPoint::DataPoint(string input) {
    istringstream iss(input);
    string cur;
    float convert;
    int count = 0;
    while (iss) {
        iss >> cur;
        if (count == 0) {
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
        }
        else if (count <= 10) {
            this->features.push_back(stof(cur));
        }
        count++;

    }
}

int DataPoint::getClassName() {
    return this->className;
}