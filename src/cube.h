#ifndef CUBE_H_
#define CUBE_H_

#include <iostream>
#include <array>
#include <string>

enum color  {red, green, blue, orange, yellow, white};
enum rotate {c_w, counter_c_w};
#define S 3

class Side
{
public:
    color cells[S][S];
    struct flank
    {
        Side *up, *down, *left, *right, *back;
    } flanks;

    Side();
    ~Side();
    void rotate_clockwise();
    void rotate_counter_clockwise();
    std::array<color, S> get_col(int x) const;
    std::array<color, S> get_row(int x) const;
    void set_col(int x, std::array<color, S> col);
    void set_row(int x, std::array<color, S> row);
};

class RubikCube
{
    Side sides[6];
    Side *front;
    int steps;
    void swap_col(int x, rotate r);
    void swap_row(int x, rotate r);
    color get_clr(int x, int y, Side *side);
    std::string prt_clr(int x, int y, Side *side);

public:
    RubikCube();
    ~RubikCube();
    void shuffle();
    void set_up();
    void set_down();
    void set_left();
    void set_right();
    void rotate_col(int x, rotate r);
    void rotate_row(int x, rotate r);

    friend std::ostream& operator<<(std::ostream &os, RubikCube &rc);
};

#endif
