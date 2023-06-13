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
        void BackwardElimination();

        int newFeature = -1;
        int removedFeature = -1;

        int largestClass;
        float largestClassSize;

        float preSqrtTotal = 0;

};

#endif