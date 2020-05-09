#include "histogram.h"
#include <iostream>
using namespace std;
#include <vector>
void find_minmax(const vector<double> numbers, double& max, double& min)
{
    unsigned int n=numbers.size();
    if(n!=0)
    {
        min = numbers[0];
        max = numbers[0];
        for(double x: numbers)
        {
            if(min>x)
                min=x;
            if(max<x)
                max=x;
        }
    }
}
