#include <iostream>
using namespace std;
#include "cube.h"

int main()
{
	RubikCube rubi = RubikCube();
	cout << rubi;
	rubi.rotate_col(1);
	cout << rubi;
	rubi.set_down();
	cout << rubi;
	rubi.rotate_row(3);
	cout << rubi;
	return 0;
}