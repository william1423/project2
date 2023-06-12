#ifndef DATAPOINT_H
#define DATAPOINT_H

#include <string>
#include <vector>
#include <iostream> //temporary

using namespace std;

class DataPoint {
    public:
        DataPoint(string input);
        int getClassName();
        float getFeatureVal(int input);
    private:
        int className;
        vector<float> features;
        
};

#endif