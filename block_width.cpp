#include "block_width.h"
#include <iostream>
using namespace std;
#include <vector>

void input_BLOCK_WIDTH(double &BLOCK_WIDTH, int flag)
{
    while (flag==1)
    {
        cerr<<"Please enter the width of one block of the histogram\n";
        cin>>BLOCK_WIDTH;
        if (BLOCK_WIDTH<3 || BLOCK_WIDTH>30)
            cerr << "The width of one block of the histogram cannot be more then 30 px or less then 3 px\n";
        if (BLOCK_WIDTH>=3 && BLOCK_WIDTH<=30)
            flag=0;
    }
}
