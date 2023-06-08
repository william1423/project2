#include <iostream>
#include <list>
#include <vector>
#include <stdlib.h>
#include <random>
#include <string>
#include <vector>

using namespace std;

mt19937 random(time(NULL));

float randEval () {
    float value = random() % 1000;
    value /= 10;
    return value;
}

void ForwardSelection (int count) {
    list<int> features;
    float globalAccuracy = 50.0; //default starting eval is 50% just to make things smoother
    float localAccuracy;
    vector<int> path;
    vector<int> optimalPath;

    for(int i = 1; i <= count; i++) {
        features.push_back(i);
    }
    cout << endl;
    cout << "Beginning search. (accuracy of a set with no features is set at 50%)" << endl << endl;

    int position = 0;
    int pushPosition = 0;
    float cur;
    list<int>::iterator it = features.begin();
    list<int>::iterator remove;

    while (features.size()) {
        it = features.begin();
        localAccuracy = 0;

        while (it != features.end()) {
            cur = randEval();

            cout << "   Using feature(s) {" << (*it);
            for(int i = path.size() - 1; i >= 0; i--) {
                cout  << ", " << path[i];
            }
            cout <<  "} accuracy is " << cur << "%" << endl;

            if (cur > localAccuracy) {
                localAccuracy = cur;
                remove = it;
            }
            it++;
        }

        path.push_back((*remove));
        features.erase(remove);

        if (localAccuracy > globalAccuracy) {
            globalAccuracy = localAccuracy;
            optimalPath = path;
        }

        cout << endl;
        cout << "Feature set {";
        for(int i = path.size() - 1; i > 0; i--) {
            cout  << path[i] << ", ";
        }
        cout << path[0];
        cout << "} was best, accuracy is " << localAccuracy << "%";
        if (localAccuracy < globalAccuracy) {
            cout << " (Warning: Accuracy has decreased) from overall best set";
        }
        cout << endl << endl;
    }
    cout << "Finished Search!! The best feature subset is {";
    for(int i = optimalPath.size() - 1; i > 0; i--) {
            cout  << optimalPath[i] << ", ";
        }
    cout << optimalPath[0] << "}, which has an accuracy of " << globalAccuracy << "%" << endl;   
}

void BackwardElimination(int count) {
    list<int> features;
    float globalAccuracy = 50;
    float localAccuracy;
    list<int> optimalPath = features;
    int listCount;

    for(int i = 1; i <= count; i++) {
        features.push_back(i);
    }
    cout << endl;
    cout << "Beginning search. (accuracy of a set containing all features is set at 50%)" << endl << endl;

    int position = 0;
    int pushPosition = 0;
    float cur;
    list<int>::iterator it = features.begin();
    list<int>::iterator remove;

    while (features.size() - 1) {
        it = features.begin();
        localAccuracy = 0;

        while (it != features.end()) {
            cur = randEval();

            listCount = 0;
            cout << "   Using feature(s) {";
            for(list<int>::iterator it2 = features.begin(); it2 != features.end(); it2++) {
                if(it2 != it) {
                    cout << (*it2);
                    listCount++;
                    if (listCount < features.size() - 1) {
                        cout  << ", ";
                    }
                }
            }
            cout <<  "} accuracy is " << cur << "%" << endl;

            if (cur > localAccuracy) {
                localAccuracy = cur;
                remove = it;
            }
            it++;
        }

        features.erase(remove);

        if (localAccuracy > globalAccuracy) {
            globalAccuracy = localAccuracy;
            optimalPath = features;
        }

        cout << endl;
        listCount = 0;
        cout << "Feature set {";
        for(list<int>::iterator it2 = features.begin(); it2 != features.end(); it2++) {
            cout << (*it2);
            listCount++;
            if (listCount < features.size()) {
                cout << ", ";
            }
        }
        cout << "} was best, accuracy is " << localAccuracy << "%";
        if (localAccuracy < globalAccuracy) {
            cout << " (Warning: Accuracy has decreased from overall best set)";
        }
        cout << endl << endl;
    }
    cout << "Finished Search!! The best feature subset is {";
    listCount = 0;
    for(list<int>::iterator it2 = optimalPath.begin(); it2 != optimalPath.end(); it2++) {
        cout << (*it2);
        listCount++;
        if (listCount < optimalPath.size()) {
            cout << ", ";
        }
    }
    cout << "}, which has an accuracy of " << globalAccuracy << "%" << endl;
}

int main () {
    int input, count;
    cout << "Welcome to William Huang's Feature Selection Algorithm." << endl << endl;
    cout << "Please enter total number of features: ";
    cin >> count;

    cout << endl << endl;
    cout << "Type the number of the algorithm you want to run" << endl << endl;
    cout << "1.   Forward Selection" << endl;
    cout << "2.   Backward Elimination" << endl;

    cin >> input;

    switch(input) {
        case 1:
            ForwardSelection(count);
            break;
        case 2:
            BackwardElimination(count);
            break;
        default:
            cout << "Input Error" << endl;
            break;
    }

    cout << "****END****";
}