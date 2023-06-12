#ifndef FEATURESELECTOR_H
#define FEATURESELECTOR_H

#include "datapoint.h"

#include <vector>

class FeatureSelector {
    public:
        void Start();
    private:
        vector<DataPoint> vec;
        vector<int> selectedFeatures;
        void ParseData(string path);
        bool NearestNeighborFeatures();
        float getEuclideanDistance(DataPoint input, DataPoint data);
};

#endif