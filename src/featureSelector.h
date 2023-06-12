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
        void Train(string path);
        int Test();
        bool NearestNeighborFeatures();
        float getEuclideanDistance(DataPoint input, DataPoint data);
};

#endif