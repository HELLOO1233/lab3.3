#include "histogram.h"
#include "block_width.h"
#include <cassert>

void test_less3()
{
    double BLOCK_WIDTH=2;
    int flag=1;
    input_BLOCK_WIDTH(BLOCK_WIDTH, flag);
    assert(flag == 1);
}
void test_more30()
{
    double BLOCK_WIDTH=40;
    int flag=1;
    input_BLOCK_WIDTH(BLOCK_WIDTH, flag);
    assert(flag == 1);
}
void test_positive()
{
    double min = 0;
    double max = 0;
    find_minmax({1, 2, 3}, max, min);
    assert(min == 1);
    assert(max == 3);
}
void test_1()
{
    double min = 0;
    double max = 0;
    find_minmax({-1, -7, -10}, max, min);
    assert(min == -10);
    assert(max == -1);
}

void test_2()
{
    double min = 0;
    double max = 0;
    find_minmax({6, 6, 6}, max, min);
    assert(min == 6);
    assert(max == 6);
}

void test_3()
{
    double min = 0;
    double max = 0;
    find_minmax({6}, max, min);
    assert(min == 6);
    assert(max == 6);
}

void test_4()
{
    double min = 0;
    double max = 0;
    find_minmax({}, max, min);
    assert(min == 0);
    assert(max == 0);
}
int main()
{
    test_positive();
    test_1();
    test_2();
    test_3();
    test_4();
    test_less3();
    test_more30();
}
