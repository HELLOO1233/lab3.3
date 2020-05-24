#include <iostream>
#include <curl/curl.h>
#include <vector>
#include <conio.h>
#include "histogram.h"
#include "svg.h"
using namespace std;
struct Input {
    vector<double> numbers;
    size_t bin_count;
};
vector<double>
input_numbers (istream& in, size_t count)
{
    vector <double> result(count);
    for (size_t i=0; i<count; i++)
    {
        in>>result[i];
    }
return result;
}
vector<size_t>
make_histogram(struct Input data)
{
    double max=0, min=0;
    find_minmax (data.numbers,max,min);
    vector<size_t>bins(data.bin_count,0); /* массив из индексов корзин */
    for(double x : data.numbers) /* мы каждому x присваиваем последовательно каждый элемент массива "numbers" */
    {
        size_t bin_index=(size_t)((x-min)*data.bin_count/(max-min));
        if (bin_index==data.bin_count) /* индекс корзины "bin_index"*/
        {
            bin_index=bin_index-1; /* нумирация идет с 0*/
        }
        bins[bin_index]++;
    }
    return bins;
}
Input
read_input(istream& in , bool promt)
{
    size_t number_count;
    Input data;
    if(promt)
    {
        cerr << "Enter number count: ";
        in >> number_count;
        cerr << "Enter numbers: ";
        data.numbers = input_numbers(in, number_count);
        cerr <<" Enter bin_count: ";
        in >>data.bin_count;
    }
    else
    {
        in >> number_count;
        data.numbers = input_numbers(in, number_count);
        in >> data.bin_count;
    }
    return data;
}
int main(int argc, char* argv[])
{
    curl_global_init(CURL_GLOBAL_ALL);
    if(argc>1)
    {
        CURL *curl = curl_easy_init();
        if(curl)
        {
           CURLcode res;
            curl_easy_setopt(curl, CURLOPT_URL,argv[1]);
            res = curl_easy_perform(curl);
            curl_easy_cleanup(curl);
        }
        return 0;
    }
    const auto input = read_input(cin, true);
    const auto bins = make_histogram(input);
    show_histogram_svg(bins);
    return 0;
}
