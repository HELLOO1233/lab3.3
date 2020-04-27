#include "histogram.h"
void find_minmax(const vector <double> numbers, double &max, double &min)
{
    max=numbers[0];
    min=numbers[0];
    for(size_t a:numbers)
    {
        if(a<min)
            min=a;
        if(a>max)
            max=a;
    }
}
