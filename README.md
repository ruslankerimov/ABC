#Artificial Bell Colony

There is a [ABC-algorithm](http://en.wikipedia.org/wiki/Artificial_bee_colony_algorithm) implementation in C++.

For usage you should define fitness-function, like this:
```c++
double fitness(vector <double> cords)
{
    double x = cords[0];
    double y = cords[1];
    
    return (x - 5) * (x - 5) + y * x + y * y;
}
```

For more see examples dir.