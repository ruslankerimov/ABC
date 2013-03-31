#include "../src/ABC.h"
#include <iostream>
#include <vector>

using namespace std;

double fitness(vector <double> cords)
{
    double x = cords[0];
    double y = cords[1];

    return 100 * (x - y * y) * (x - y * y) + (x - 1) * (x - 1);
}

int main(int argc, char** argv)
{
    vector < pair <double, double> > limits;
    limits.push_back(make_pair(-10, 10));
    limits.push_back(make_pair(-10, 10));

    ABCconfig config;
    config.limits = limits;
    config.fitness = fitness;
    config.max_iterations = 500;

    ABC * algorithm = new ABC(config);
    vector <double> best = algorithm->solve();

    cout << "x = " << best[0] << endl << "y = " << best[1] << endl;

    return 0;
}
