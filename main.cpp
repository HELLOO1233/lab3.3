#include <iostream>
#include <curl/curl.h>
#include <vector>
#include <conio.h>
#include "histogram.h"
#include "svg.h"
#include <string>
#include <sstream>
#include <windows.h>
#include <cstdio>
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
size_t
write_data(void* items, size_t item_size, size_t item_count, void* ctx)
{
    const size_t data_size = item_size * item_count;
    const char* new_items = reinterpret_cast<const char*>(items);
    stringstream* buffer = reinterpret_cast<stringstream*>(ctx);
    buffer->write(new_items, data_size);
    return 0;
}
Input
download(const string& address) {
    stringstream buffer;
    curl_global_init(CURL_GLOBAL_ALL);
    CURL *curl = curl_easy_init();
        if(curl)
        {
            CURLcode res;
            curl_easy_setopt(curl, CURLOPT_URL,address);
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
            res = curl_easy_perform(curl);
            if (res != CURLE_OK)
            {
                cout << curl_easy_strerror(res) << endl;
                cout <<curl_version_info(CURLVERSION_NOW)<<"\n";
                curl_version_info_data asd;
                cout <<asd.ssl_version_num<<"\n";
                exit(1);
            }
            curl_easy_cleanup(curl);
        }
    return read_input(buffer, false);
}
int main(int argc, char* argv[])
{
    printf("Decimal version %u\n",GetVersion());
    printf("Hexadecimal version %x\n",GetVersion());
    DWORD info=GetVersion();
    DWORD mask = 0x0000ffff;
    DWORD version = info & mask;
    printf("version %u\n",version);
    DWORD platform = info >> 16;
    DWORD mask_minor = 0x000000ff;
    DWORD mask_major = 0x0000ff00;
    DWORD version_minor = info & mask_minor;
    printf("minor version %u.\n",version_minor);
    DWORD version_major1 = info & mask_major;
    DWORD version_major = version_major1 >> 8;
    printf("major version %u.\n",version_major);
    if ((info & 0x40000000) == 0)
        {
            DWORD build = platform;
            printf("build %u.\n", build);
        }
    return 0;
    Input input;
    if (argc > 1)
    {
        input = download(argv[1]);
    }
    else
    {
        input = read_input(cin, true);
    }
    const auto bins=make_histogram(input);
    show_histogram_svg(bins);
    return 0;
}

