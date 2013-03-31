#ifndef ABCCONFIG_H_INCLUDED

#include <vector>

using namespace std;

struct ABCconfig
{
    int count_of_scout_bees;
    int count_of_best_areas;
    int count_of_perspective_areas;
    int count_of_bees_to_best_area;
    int count_of_bees_to_perspective_area;
    vector < pair <double, double> > limits;
    double ( * fitness)(vector <double>);
    double neighbourhood_value;
    int max_iterations;
    ABCconfig();
};

#endif
