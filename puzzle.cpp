#include <Eigen/Dense>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
#include "puzzle/puzzle_logic.hpp"


void swap(Matrix54i &puzzle, int y1, int x1, int y2, int x2) {
    int stock = puzzle(y1, x1);
    puzzle(y1, x1) = puzzle(y2, x2);
    puzzle(y2, x2) = stock;
}

Matrix54i init_puzzle() {
    Matrix54i puzzle = Matrix54i::Zero(5, 4);

    puzzle(0, 0) = 1;
    puzzle(1, 0) = 1;
    puzzle(0, 3) = 2;
    puzzle(1, 3) = 2;
    puzzle(2, 0) = 3;
    puzzle(3, 0) = 3;
    puzzle(2, 3) = 4;
    puzzle(3, 3) = 4;
    puzzle(2, 1) = 5;
    puzzle(2, 2) = 5;
    puzzle(3, 1) = 6;
    puzzle(3, 2) = 7;
    puzzle(4, 0) = 8;
    puzzle(4, 3) = 9;
    puzzle(4, 1) = 10;
    puzzle(4, 2) = 10;

    return puzzle;
}

void find_location_return::set_value(int yv, int xv, int v) {
    y = yv;
    x = xv;
    val = v;
}

std::vector<find_location_return> find_location(const Matrix54i &puzzle,
const int targetValue) {
    std::vector<find_location_return> ret_list;
    int rows = puzzle.rows();
    int cols = puzzle.cols();
    for (int i = 0; i < rows; i++) {
        for (int c = 0; c < cols; c++) {
            if (puzzle(i, c) == targetValue) {
                find_location_return ret;
                ret.y = i;
                ret.x = c;
                ret.val = targetValue;
                ret_list.push_back(ret);
            }
        }
    }
    return ret_list;
}

bool inrange_check_right(const class find_location_return &ret) {
    return ret.x >= 0 && ret.x <= 2;
}

bool inrange_check_left(const class find_location_return &ret) {
    if (ret.x > 0 && ret.x < 4) {
        return true;
    } else {
        return false;
    }
}

bool inrange_check_up(const class find_location_return &ret) {
    if (ret.y < 5 && ret.y > 0) {
        return true;
    } else {
        return false;
    }
}

bool inrange_check_down(const class find_location_return &ret) {
    if (ret.y > -1 && ret.y < 4) {
        return true;
    } else {
        return false;
    }
}

bool empty_check_right(const Matrix54i puzzle,
const class find_location_return &ret) {
    int x = ret.x;
    x = x+1;
    if (x > -1 && x < 4) {
        if (puzzle(ret.y, x) == 10) {
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}

bool empty_check_left(const Matrix54i puzzle,
const class find_location_return &ret) {
    int x = ret.x;
    x = x-1;
    if (x > -1 && x < 4) {
        if (puzzle(ret.y, x) == 10) {
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}

bool empty_check_up(const Matrix54i puzzle,
const class find_location_return &ret) {
    int y = ret.y;
    y = y-1;
    if (ret.y < 5 &&ret.y > -1) {
        if (puzzle(y, ret.x) == 10) {
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}

bool empty_check_down(const Matrix54i puzzle,
const class find_location_return &ret) {
    int y = ret.y;
    y = y+1;
    if (ret.y < 4 &&ret.y > -1) {
        if (puzzle(y, ret.x) == 10) {
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}

void move_1x1_to_right(Matrix54i &puzzle, class find_location_return &ret) {
    int xt = ret.x +1;
    swap(puzzle, ret.y, ret.x, ret.y, xt);
}
void move_1x1_to_left(Matrix54i &puzzle, class find_location_return &ret) {
    int xt = ret.x -1;
    swap(puzzle, ret.y, ret.x, ret.y, xt);
}

void move_1x1_to_up(Matrix54i &puzzle, class find_location_return &ret) {
    int yt = ret.y -1;
    swap(puzzle, ret.y, ret.x, yt, ret.x);
}

void move_1x1_to_down(Matrix54i &puzzle, class find_location_return &ret) {
    int yt = ret.y +1;
    swap(puzzle, ret.y, ret.x, yt, ret.x);
}

void move_2x1_to_left(Matrix54i &puzzle, class find_location_return &ret,
class find_location_return &ret2) {
    int xt = ret.x -1;
    int xtt = ret2.x -1;
    swap(puzzle, ret.y, ret.x, ret.y, xt);
    swap(puzzle, ret2.y, ret2.x, ret2.y, xtt);
}

void move_2x1_to_right(Matrix54i &puzzle, class find_location_return &ret,
class find_location_return &ret2) {
    int xt = ret.x +1;
    int xtt = ret2.x +1;
    swap(puzzle, ret2.y, ret2.x, ret2.y, xtt);
    swap(puzzle, ret.y, ret.x, ret.y, xt);
}

void move_2x1_to_up(Matrix54i &puzzle, class find_location_return &ret,
class find_location_return &ret2) {
    int yt = ret.y -1;
    int ytt = ret2.y -1;
    swap(puzzle, ret.y, ret.x, yt, ret.x);
    swap(puzzle, ret2.y, ret2.x, ytt, ret2.x);
}

void move_2x1_to_down(Matrix54i &puzzle,
class find_location_return &ret, class find_location_return &ret2) {
    int yt = ret.y +1;
    int ytt = ret2.y +1;
    swap(puzzle, ret2.y, ret2.x, ytt, ret2.x);
    swap(puzzle, ret.y, ret.x, yt, ret.x);
}

void move_2x2_right(Matrix54i &puzzle, class find_location_return &ret,
class find_location_return &ret2,
class find_location_return &ret3,
class find_location_return &ret4) {
    swap(puzzle, ret4.y, ret4.x, ret4.y, ret4.x + 1);
    swap(puzzle, ret2.y, ret2.x, ret2.y, ret2.x + 1);
    swap(puzzle, ret.y, ret.x, ret.y, ret.x + 1);
    swap(puzzle, ret3.y, ret3.x, ret3.y, ret3.x + 1);
}


void move_2x2_left(Matrix54i &puzzle, class find_location_return &ret,
class find_location_return &ret2,
class find_location_return &ret3,
class find_location_return &ret4) {
    swap(puzzle, ret.y, ret.x, ret.y, ret.x-1);
    swap(puzzle, ret3.y, ret3.x, ret3.y, ret3.x-1);
    swap(puzzle, ret4.y, ret4.x, ret4.y, ret4.x-1);
    swap(puzzle, ret2.y, ret2.x, ret2.y, ret2.x-1);
}


void move_2x2_up(Matrix54i &puzzle, class find_location_return &ret,
class find_location_return &ret2,
class find_location_return &ret3,
class find_location_return &ret4) {
    swap(puzzle, ret.y, ret.x, ret.y-1, ret.x);
    swap(puzzle, ret2.y, ret2.x, ret2.y-1, ret2.x);
    swap(puzzle, ret3.y, ret3.x, ret3.y-1, ret3.x);
    swap(puzzle, ret4.y, ret4.x, ret4.y-1, ret4.x);
}

void move_2x2_down(Matrix54i &puzzle, class find_location_return &ret,
class find_location_return &ret2,
class find_location_return &ret3,
class find_location_return &ret4) {
    swap(puzzle, ret3.y, ret3.x, ret3.y+1, ret3.x);
    swap(puzzle, ret4.y, ret4.x, ret4.y+1, ret4.x);
    swap(puzzle, ret.y, ret.x, ret.y+1, ret.x);
    swap(puzzle, ret2.y, ret2.x, ret2.y+1, ret2.x);
}

