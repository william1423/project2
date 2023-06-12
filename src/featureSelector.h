#ifndef FEATURESELECTOR_H
#define FEATURESELECTOR_H

#include "datapoint.h"

#include <vector>
#include <list>

class FeatureSelector {
    public:
        void Start();
    private:
        vector<DataPoint> vec;
        vector<int> path;
        list<int> remainingFeatures;
        void Train(string path);
        int Test();
        int TestOption1(int vecIndex, DataPoint testPoint);
        bool NearestNeighborFeatures();
        float getEuclideanDistance(DataPoint input, DataPoint data);
        float Validate();
        void ForwardSelection();

        int newFeature;
};

#endif