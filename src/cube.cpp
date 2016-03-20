#include "cube.h"
#include <iostream>

Side::Side() {	}

Side::~Side() {	}

void Side::rotate_clockwise()
{
	for (int i(0); i < S; i++)
	{
		for (int j(i); j < S; j++)
		{
			color t = cells[i][j];
			cells[i][j] = cells[j][i];
			cells[j][i] = t;
		}
	}
	
	for (int i(0); i < S; i++)
	{
		color t = cells[i][0];
		cells[i][0] = cells[i][2];
		cells[i][2] = t;
	}
}

void Side::rotate_counter_clockwise()
{
	for (int i(0); i < S; i++)
	{
		for (int j(i); j < S; j++)
		{
			color t = cells[i][j];
			cells[i][j] = cells[j][i];
			cells[j][i] = t;
		}
	}
	
	for (int i(0); i < S; i++)
	{
		color t = cells[0][i];
		cells[0][i] = cells[2][i];
		cells[2][i] = t;
	}
}

std::array<color, S> Side::get_col(int x) const
{
	std::array<color, S> col;
	for (int i(0); i < S; i++)
		col[i] = cells[i][x];
	return col;
}

std::array<color, S> Side::get_row(int x) const
{
	std::array<color, S> row;
	for (int i(0); i < S; i++)
		row[i] = cells[x][i];
	return row;
}

void Side::set_col(int x, std::array<color, S> col)
{
	for (int i(0); i < S; i++)
	{
		cells[i][x] = col[i];
	}
}

void Side::set_row(int x, std::array<color, S> row)
{
	for (int i(0); i < S; i++)
	{
		cells[x][i] = row[i];
	}
}

RubikCube::RubikCube()
{
	for (int s(0); s < 6; s++)
	{
		for (int i(0); i < 9; i++)
		{
			sides[s].cells[i/S][i%S] = color(s);
		}
	}
	
	sides[0].flanks.up = &sides[1];
	sides[0].flanks.down = &sides[2];
	sides[0].flanks.left = &sides[4];
	sides[0].flanks.right = &sides[5];
	sides[0].flanks.back = &sides[3];
	
	sides[1].flanks.up = &sides[4];
	sides[1].flanks.down = &sides[5];
	sides[1].flanks.left = &sides[0];
	sides[1].flanks.right = &sides[3];
	sides[1].flanks.back = &sides[2];
	
	sides[2].flanks.up = &sides[5];
	sides[2].flanks.down = &sides[4];
	sides[2].flanks.left = &sides[0];
	sides[2].flanks.right = &sides[3];
	sides[2].flanks.back = &sides[1];
	
	sides[3].flanks.up = &sides[1];
	sides[3].flanks.down = &sides[2];
	sides[3].flanks.left = &sides[5];
	sides[3].flanks.right = &sides[4];
	sides[3].flanks.back = &sides[0];
	
	sides[4].flanks.up = &sides[1];
	sides[4].flanks.down = &sides[2];
	sides[4].flanks.left = &sides[3];
	sides[4].flanks.right = &sides[0];
	sides[4].flanks.back = &sides[5];
	
	sides[5].flanks.up = &sides[1];
	sides[5].flanks.down = &sides[2];
	sides[5].flanks.left = &sides[0];
	sides[5].flanks.right = &sides[3];
	sides[5].flanks.back = &sides[4];
	
	front = &sides[5];
	steps = 1;
}

RubikCube::~RubikCube()
{
	// !!Not implemented!!
}

void RubikCube::shuffle()
{
	// !!Not implemented!!
}

void RubikCube::set_up()
{
	front = front->flanks.up;
}

void RubikCube::set_down()
{
	front = front->flanks.down;
}

void RubikCube::set_left()
{
	front = front->flanks.left;
}

void RubikCube::set_right()
{
	front = front->flanks.right;
}

void RubikCube::rotate_col(int x)
{
	x--;
	if (x == 1)
	{
		swap_col(x);
		steps++;
	}
	else if (x == 0)
	{
		swap_col(x);
		front->flanks.left->rotate_clockwise();
		steps++;
	}
	else if (x == 2)
	{
		swap_col(x);
		front->flanks.right->rotate_counter_clockwise();
		steps++;
	}
	
	else
		std::cout << "ERR : Wrong column number\n";
}

void RubikCube::rotate_row(int x)
{
	x--;
	if (x == 1)
	{
		swap_row(x);
		steps++;
	}
	else if (x == 0)
	{
		swap_row(x);
		front->flanks.up->rotate_clockwise();
		steps++;
	}
	else if (x == 2)
	{
		swap_row(x);
		front->flanks.down->rotate_counter_clockwise();
		steps++;
	}
	
	else
		std::cout << "ERR : Wrong column number\n";
}

std::ostream& operator<<(std::ostream &os, RubikCube &rc)
{
	using namespace std;
	cout << endl;
	cout << "Step #" << rc.steps << endl;
	{ // Верхняя часть кубика
		for (int i(0); i < S; i++)
		{
			cout << "          ";
			for (int j(0); j < S; j++)
			{
				cout << "[" << rc.prt_clr(i,j, rc.front->flanks.up) << "]";
			}
			cout << endl;
		}
		cout  << "          ---------\n";
	}
	{ // Три средние части
		for (int i(0); i < S; i++)
		{
			for (int j(0); j < S; j++)
			{
				cout << "[" << rc.prt_clr(i,j,rc.front->flanks.left) << "]";
			}
			cout << "|";
			for (int j = 0; j < S; j++)
			{
				cout << "[" << rc.prt_clr(i,j,rc.front) << "]";
			}
			cout << "|";
			for (int j = 0; j < S; j++)
			{
				cout << "[" << rc.prt_clr(i,j,rc.front->flanks.right) << "]";
			}
			cout << "|";
			for (int j = 0; j < S; j++)
			{
				cout << "[" << rc.prt_clr(i,j, rc.front->flanks.back) << "]";
			}
			cout << endl;
		}
		cout << "          ---------\n";
	}
	{ // Нижняя часть
		for (int i(0); i < S; i++)
		{
			cout << "          ";
			for (int j(0); j < S; j++)
			{
				cout  << "[" << rc.prt_clr(i,j,rc.front->flanks.down) << "]";
			}
			cout << endl;
		}
	}
	cout << "<------------------------------------------------>" << endl;
	
	return os;
}


void RubikCube::swap_col(int x)
{
	std::array<color, S> t = front->get_col(x);
	front->set_col(x, front->flanks.up->get_col(x));
	front->flanks.up->set_col(x, front->flanks.back->get_col(x));
	front->flanks.back->set_col(x, front->flanks.down->get_col(x));
	front->flanks.down->set_col(x, t);
}

void RubikCube::swap_row(int x)
{
	std::array<color, S> t = front->get_row(x);
	front->set_row(x, front->flanks.right->get_row(x));
	front->flanks.right->set_row(x, front->flanks.back->get_row(x));
	front->flanks.back->set_row(x, front->flanks.left->get_row(x));
	front->flanks.left->set_row(x, t);
}

color RubikCube::get_clr(int x, int y, Side *side)
{
	return side->cells[x][y];
}

std::string RubikCube::prt_clr(int x, int y, Side *side)
{
	using namespace std;
	color elem = get_clr(x, y, side);
	switch (elem)
	{
		case red:
			return string("к");
			break;
		case green:
			return string("з");
			break;
		case blue:
			return string("с");
			break;
		case orange:
			return string("о");
			break;
		case yellow:
			return string("ж");
			break;
		case white:
			return string("б");
			break;
	}
}