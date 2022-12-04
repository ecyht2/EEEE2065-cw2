#include <iostream>
#include <list>
#include <numeric>
#include <fstream>
#include <cstdlib>
#include <cmath>

#include "number-guesser.h"

using namespace std;

int main(int argc, char *argv[]) {
    // Setting up
    int min;
    int max;
    int step;
    int iteration;
    switch (argc) {
        case 1:
            min = 100;
            max = 5000;
            step = 100;
            iteration = 500;
            break;
        case 2:
            min = atoi(argv[1]);
            max = 5000;
            step = 100;
            iteration = 500;
            break;
        case 3:
            min = atoi(argv[1]);
            max = atoi(argv[2]);
            step = 100;
            iteration = 500;
            break;
        case 4:
            min = atoi(argv[1]);
            max = atoi(argv[2]);
            step = atoi(argv[3]);
            iteration = 500;
            break;
        case 5:
            min = atoi(argv[1]);
            max = atoi(argv[2]);
            step = atoi(argv[3]);
            iteration = atoi(argv[4]);
            break;
        default:
            min = atoi(argv[1]);
            max = atoi(argv[2]);
            step = atoi(argv[3]);
            break;
    }

    // Initializing data
    AutoNumberGuesser guesser(1, min);
    list<int> data;
    ofstream csv("data.csv");
    csv << "Max Number,Mean,Standard Deviation" << endl;
    // Looping over all ranges
    for (int i = min; i <= max; i+=step) {
        guesser.setMax(i);
        guesser.resetNumber();
        // Sampling all the data
        for (int j = 0; j < iteration; j++) {
            data.push_back(guesser.start());
            guesser.resetNumber();
        }

        // Calculating mean
        int sz = data.size();
        int sum = accumulate(data.begin(), data.end(), 0);
        float mean = (float) sum / (float) sz;

        // Calculating Variance and Standard Deviation
        auto x_square = [](int accumulator, const int& val) {
            return accumulator + val * val;
        };
        float mean2 = std::accumulate(data.begin(), data.end(), 0.0, x_square) / (float) sz;
        float var = mean2 - mean * mean;
        float std = sqrt(var);

        // Wrting to csv
        csv << i << "," << mean << "," << std << endl;

        // Clearing data for next range
        data.clear();
    }

    return 0;
}
