#ifndef ABC_H_INCLUDED
#define ABC_H_INCLUDED

#include <vector>
#include <algorithm>
#include <time.h>
#include "ABCconfig.h"

using namespace std;

class ABC
{
private:
    struct Bee
    {
        vector <double> cords;
        double value;
        Bee(vector <double>, double);
    };

    ABCconfig config;
    int dimension;
    vector <double> get_random_cords();
    vector <double> get_random_neighbor_cords(vector <double>);

    static double get_random_double(double, double);
    static bool is_rand_inited;

    static bool compare(Bee *, Bee *);
public:
    ABC(ABCconfig);
    vector <double> solve();
};

#endif
