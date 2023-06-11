#ifndef FEATURESELECTOR_H
#define FEATURESELECTOR_H

#include "datapoint.h"

#include <vector>

class FeatureSelector {
    public:
        void Start();
        bool NearestNeighbor();
    private:
        vector<DataPoint> vec;
        vector<int> selectedFeatures;
        void ParseData(string path);
};

#endif