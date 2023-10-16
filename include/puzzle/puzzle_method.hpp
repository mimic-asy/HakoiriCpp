#ifndef HAKOIRICPP_METHOD_H
#define HAKOIRICPP_METHOD_H

#include <Eigen/Dense>
#include <vector>
#include <queue>
#include <unordered_map>
#include <functional>
#include <fstream>


using Matrix54i = Eigen::Matrix<int, 5, 4>;

Matrix54i init_puzzle();

class find_location_return {
public:
    int val;
    int y;
    int x;

    void set_value(int yv,int xv,int v);

};


std::string to_hashable(const Matrix54i& simple_puzzle);
struct KeyHasher
{   //インスタンスを取得する->operator
    int operator()(const Matrix54i& a) const
    {
        std::string a_str = to_hashable(const_cast<Matrix54i&>(a));
        std::hash<std::string> hash_fn;
        size_t hash_value = hash_fn(a_str);
        return hash_value;
    }
};

struct KeyEqual
{
    bool operator()(const Matrix54i& a, const Matrix54i& b) const
    {
        return a == b;
    }
};


void swap(Matrix54i &puzzle, int y1, int x1, int y2, int x2);
Matrix54i init_puzzle();
std::vector<find_location_return> find_location(const Matrix54i puzzle,
const int targetValue);
bool inrange_check_right(const class find_location_return &ret);
bool inrange_check_left(const class find_location_return &ret);
bool inrange_check_up(const class find_location_return &ret);
bool inrange_check_down(const class find_location_return &ret);
bool empty_check_right(const Matrix54i puzzle,
const class find_location_return &ret);
bool empty_check_left(const Matrix54i puzzle,
const class find_location_return &ret);
bool empty_check_up(const Matrix54i puzzle,
const class find_location_return &ret);
bool empty_check_down(const Matrix54i puzzle,
const class find_location_return &ret);
void move_1x1_to_right(Matrix54i &puzzle, class find_location_return &ret);
void move_1x1_to_left(Matrix54i &puzzle, class find_location_return &ret);
void move_1x1_to_up(Matrix54i &puzzle, class find_location_return &ret);
void move_1x1_to_down(Matrix54i &puzzle, class find_location_return &ret);
void move_2x1_to_left(Matrix54i &puzzle, class find_location_return &ret,
class find_location_return &ret2);
void move_2x1_to_right(Matrix54i &puzzle, class find_location_return &ret,
class find_location_return &ret2);
void move_2x1_to_up(Matrix54i &puzzle, class find_location_return &ret,
class find_location_return &ret2);
void move_2x1_to_down(Matrix54i &puzzle,
class find_location_return &ret, class find_location_return &ret2);
void move_2x2_right(Matrix54i &puzzle, class find_location_return &ret,
class find_location_return &ret2,
class find_location_return &ret3,
class find_location_return &ret4);
void move_2x2_left(Matrix54i &puzzle, class find_location_return &ret,
class find_location_return &ret2,
class find_location_return &ret3,
class find_location_return &ret4);
void move_2x2_up(Matrix54i &puzzle, class find_location_return &ret,
class find_location_return &ret2,
class find_location_return &ret3,
class find_location_return &ret4);
void move_2x2_down(Matrix54i &puzzle, class find_location_return &ret,
class find_location_return &ret2,
class find_location_return &ret3,
class find_location_return &ret4);
bool clear(const Matrix54i puzzle);
Matrix54i num_simple(const Matrix54i puzzle, const int i);
Matrix54i board_simple(Matrix54i &puzzle);
bool range_and_emptycheck_right(Matrix54i puzzle, class find_location_return ret);
bool range_and_emptycheck_left(Matrix54i puzzle, class find_location_return ret);
bool range_and_emptycheck_up(Matrix54i puzzle, class find_location_return ret);
bool range_and_emptycheck_down(Matrix54i puzzle, class find_location_return ret);
bool check_rightside(const Matrix54i puzzle, const int checkval);
bool check_leftside(const Matrix54i puzzle, const int checkval);
bool check_upside(const Matrix54i puzzle, const int checkval);
bool check_downside(const Matrix54i puzzle, const int checkval);
std::vector<int> numbers_canmove_right(const Matrix54i puzzle);
std::vector<int> numbers_canmove_left(const Matrix54i puzzle);
std::vector<int> numbers_canmove_up(const Matrix54i puzzle);
std::vector<int> numbers_canmove_down(const Matrix54i puzzle);
Matrix54i movepuzzle_right(Matrix54i &puzzle, const int val);
Matrix54i movepuzzle_left(Matrix54i &puzzle, const int val);
Matrix54i movepuzzle_up(Matrix54i &puzzle, const int val);
Matrix54i movepuzzle_down(Matrix54i &puzzle, const int val);
std::vector<Matrix54i> move_right(Matrix54i &puzzle);
std::vector<Matrix54i> move_left(Matrix54i &puzzle);
std::vector<Matrix54i> move_up(Matrix54i &puzzle);
std::vector<Matrix54i> move_down(Matrix54i &puzzle);
std::vector<Matrix54i> moved_board_list(Matrix54i &puzzle);
std::string to_hashable(const Matrix54i& simple_puzzle);
std::string to_hashable_pluscomma(const Matrix54i& simple_puzzle);
bool exist(const std::string hash_puzzle,
const std::vector<std::string>  puzzle_state);
std::vector<Matrix54i> clearroute(std::unordered_map<Matrix54i, Matrix54i,
 KeyHasher, KeyEqual>& edges, const Matrix54i moved_puzzle);
void queue_state_append(Matrix54i before_moving, std::vector<Matrix54i> movable,
std::vector<std::string> &puzzle_state,
std::unordered_map<Matrix54i, Matrix54i, KeyHasher, KeyEqual> &edges,
std::queue<Matrix54i> &puzzle_list,
std::vector<std::vector<Matrix54i>> &c_route);
std::vector<std::vector<Matrix54i>> breadth_first_search(Matrix54i &puzzle);
std::vector<Matrix54i> shortestroute_find(const std::vector<std::vector<Matrix54i>> &c_route);

#endif