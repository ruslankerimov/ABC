#include "ABC.h"
#include <iostream>

using namespace std;

ABC::ABC(ABCconfig config)
{
    ABC::config = config;
    dimension = config.limits.size();
}

vector <double> ABC::solve()
{
    int count_of_bees = config.count_of_scout_bees +
                    config.count_of_bees_to_best_area * config.count_of_best_areas +
                    config.count_of_bees_to_perspective_area * config.count_of_perspective_areas;

    vector <Bee *> bees;

    for (int i = 0; i < count_of_bees; ++i)
    {
        vector <double> cords = get_random_cords();
        bees.push_back(
            new Bee(cords, config.fitness(cords)));
    }

    sort(bees.begin(), bees.end(), compare);

    for (int i = 0; i < config.max_iterations; ++i)
    {
        int j = 0, size, l = config.count_of_best_areas + config.count_of_perspective_areas;

        for (size = config.count_of_best_areas; j < size; ++j)
        {
            for (int k = 0; k < config.count_of_bees_to_best_area - 1; ++k)
            {
                bees[l]->cords = get_random_neighbor_cords(bees[j]->cords);
                bees[l]->value = config.fitness(bees[l]->cords);
                l++;
            }
        }

        for (size += config.count_of_perspective_areas; j < size; ++j)
        {
            for (int k = 0; k < config.count_of_bees_to_perspective_area - 1; ++k)
            {
                bees[l]->cords = get_random_neighbor_cords(bees[j]->cords);
                bees[l]->value = config.fitness(bees[l]->cords);
                l++;
            }
        }

        for (;l < count_of_bees;)
        {
            bees[l]->cords = get_random_cords();
            bees[l]->value = config.fitness(bees[l]->cords);
            l++;
        }

        sort(bees.begin(), bees.end(), compare);


        for (int i = 0, size = bees.size(); i < size; ++i)
        {
            vector <double> cords = bees[i]->cords;

            cout << i << ")" << bees[i]->value << ";" << 1 / bees[i]->value << ";";

            for (int j = 0, size_j = cords.size(); j < size_j; ++j)
            {
                cout << " " << cords[j];
            }

            cout << endl;
        }

        cout << "opa" << endl;

    }

    return bees[0]->cords;
}

bool ABC::is_rand_inited = false;

double ABC::get_random_double(double min, double max)
{
    if ( ! is_rand_inited)
    {
        srand(time(NULL));
        is_rand_inited = true;
    }

    return (rand() / ((double) RAND_MAX + 1.0)) * (max - min) + min;
}

vector <double> ABC::get_random_cords()
{
    vector <double> new_cords;

    for (int i = 0; i < dimension; ++i)
    {
        double min = config.limits[i].first;
        double max = config.limits[i].second;

        new_cords.push_back(get_random_double(min, max));
    }

    return new_cords;
}

vector <double> ABC::get_random_neighbor_cords(vector <double> cords)
{
    vector <double> new_cords;

    for (int i = 0; i < dimension; ++i)
    {
        double min = cords[i] - config.neighbourhood_value;
        double max = cords[i] + config.neighbourhood_value;

        if (min < config.limits[i].first)
        {
            min = config.limits[i].first;
        }

        if (max > config.limits[i].second)
        {
            max = config.limits[i].second;
        }

        new_cords.push_back(get_random_double(min, max));
    }

    return new_cords;
}

ABC::Bee::Bee(vector <double> cords, double value)
{
    Bee::cords = cords;
    Bee::value = value;
}

bool ABC::compare(Bee * a, Bee * b)
{
    return a->value > b->value;
}
