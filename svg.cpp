#include "svg.h"
#include "block_width.h"
#include <iostream>
#include <string>
#include <sstream>
#include <windows.h>
using namespace std;
void svg_text(double left, double baseline, string text)
{
     cout << "<text x='"<<left<<"' y='"<<baseline<<"'>"<<text<<"</text>";
}
void svg_rect(double x, double y, double width, double height,string stroke, string fill)
{
    cout<< "<rect x='"<<x<<"' y='"<<y<<"' width='"<<width<<"' height='"<<height<<"' stroke='red' fill='blue'/>";
}
void svg_begin(double width, double height)
{
    cout << "<?xml version='1.0' encoding='UTF-8'?>\n";
    cout << "<svg ";
    cout << "width='" << width << "' ";
    cout << "height='" << height << "' ";
    cout << "viewBox='0 0 " << width << " " << height << "' ";
    cout << "xmlns='http://www.w3.org/2000/svg'>\n";
}

void svg_end()
{
    cout << "</svg>\n";
}
string
make_info_text() {
    stringstream buffer;
    //printf("Decimal version %u\n",GetVersion());
    //printf("Hexadecimal version %x\n",GetVersion());
    DWORD info=GetVersion();
    DWORD mask = 0x0000ffff;
    DWORD version = info & mask;
    //printf("version %u\n",version);
    DWORD platform = info >> 16;
    DWORD mask_minor = 0x000000ff;
    DWORD mask_major = 0x0000ff00;
    DWORD version_minor = info & mask_minor;
    //printf("minor version %u.\n",version_minor);
    DWORD version_major1 = info & mask_major;
    DWORD version_major = version_major1 >> 8;
    //printf("major version %u.\n",version_major);
    if ((info & 0x40000000) == 0)
        {
            DWORD build = platform;
            //printf("build %u.\n", build);
            buffer << "Windows v" << version_major << "." << version_minor << "(build " << build << ")\n";
        }
    char system[MAX_COMPUTERNAME_LENGTH + 1];
    DWORD Size = sizeof(system);
    GetComputerNameA(system, &Size);
    //printf("System: %s", system);
    buffer << "Computer name: " << system << "\n";
    return buffer.str();
}
void show_histogram_svg(const vector<size_t> bins)
{
    double BLOCK_WIDTH;
    const auto IMAGE_WIDTH = 500;
    const auto IMAGE_HEIGHT = 300;
    const auto TEXT_LEFT = 20;
    const auto TEXT_BASELINE = 20;
    const auto TEXT_WIDTH = 50;
    const auto BIN_HEIGHT = 30;
    int flag=1;
    input_BLOCK_WIDTH(BLOCK_WIDTH,flag);
    size_t MAX_ASTERISK=(size_t)(350/BLOCK_WIDTH);
    svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);
    unsigned max_count=0;
    for (size_t b : bins) /* мы присваиваем значение количества элементов */
    {
        if(max_count<b)
            max_count=b; /* здесь мы ищем максимальное количество элементов в массиве*/
    }
    double top = 0;
    for (size_t bin : bins)
    {
        size_t height=35;
            if(max_count>MAX_ASTERISK) /* Если количество будет больше 35, то уменьшаем масштаб*/
                height=MAX_ASTERISK*((static_cast<double>(bin))/max_count); /* это для того,чтобы было дробное число , получаем, используя "static_cast<double>"*/
        else
        {
            height=bin;
        }
        height = BLOCK_WIDTH * height;
        svg_text(TEXT_LEFT, top + TEXT_BASELINE, to_string(bin));
        svg_rect(TEXT_WIDTH, top, height, BIN_HEIGHT, "red", "#aaffaa");
        top += BIN_HEIGHT;


    }
    cout << "<text x='" << TEXT_LEFT << "' y='"<<top+BIN_HEIGHT<<"'>"<<make_info_text()<<"</text>";
    svg_end();
}
