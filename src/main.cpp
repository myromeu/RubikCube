#include <iostream>
using namespace std;
#include "cube.h"

int main()
{
    RubikCube rubi = RubikCube();
    cout << rubi;
    rubi.rotate_col(1, c_w);
    cout << rubi;
    rubi.set_down();
    cout << rubi;
    rubi.rotate_row(3, counter_c_w);
    cout << rubi;
    rubi.rotate_row(3, c_w);
    cout << rubi;


    rubi.shuffle();
    cout << rubi;
    return 0;
}
