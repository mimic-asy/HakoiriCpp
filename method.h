#ifndef HAKOIRICPP_METHOD_H
#define HAKOIRICPP_METHOD_H

#include <Eigen/Dense>
#include <vector>
#include <queue>
#include <unordered_map>
#include <functional>


using Matrix54i = Eigen::Matrix<int, 5, 4>;

Matrix54i init_puzzle();

class area_check_return {
public:
    int val;
    int y;
    int x;

    void Func(int yv, int xv, int v);

};




void swap(Matrix54i &puzzle,int y1,int x1,int y2,int x2);
std::vector<area_check_return> area_check(Matrix54i puzzle, int targetValue);
bool inrange_check_right(class area_check_return &ret);
bool inrange_check_left(class area_check_return &ret);
bool inrange_check_up(class area_check_return &ret);
bool inrange_check_down(class area_check_return &ret);
bool vacant_check_right(Matrix54i puzzle, class area_check_return &ret);
bool vacant_check_left(Matrix54i puzzle, class area_check_return &ret);
bool vacant_check_up(Matrix54i puzzle, class area_check_return &ret);
bool vacant_check_down(Matrix54i puzzle, class area_check_return &ret);
bool range_and_vacantcheck_right(Matrix54i puzzle, class area_check_return ret);
bool range_and_vacantcheck_left(Matrix54i puzzle, class area_check_return ret);
bool range_and_vacantcheck_up(Matrix54i puzzle, class area_check_return ret);
bool range_and_vacantcheck_down(Matrix54i puzzle, class area_check_return ret);
Matrix54i move_1x1_to_right(Matrix54i &puzzle, class area_check_return &ret);
Matrix54i move_1x1_to_left(Matrix54i &puzzle, class area_check_return &ret);
Matrix54i move_1x1_to_up(Matrix54i &puzzle, class area_check_return &ret);
Matrix54i move_1x1_to_down(Matrix54i &puzzle, class area_check_return &ret);
Matrix54i move_2x1_to_left(Matrix54i &puzzle, class area_check_return &ret, class area_check_return &ret2);
Matrix54i move_2x1_to_right(Matrix54i &puzzle, class area_check_return &ret, class area_check_return &ret2);
Matrix54i move_2x1_to_up(Matrix54i &puzzle, class area_check_return &ret, class area_check_return &ret2);
Matrix54i move_2x1_to_down(Matrix54i &puzzle, class area_check_return &ret, class area_check_return &ret2);

Matrix54i move_2x2_right(Matrix54i &puzzle, class area_check_return &ret,
                                class area_check_return &ret2, class area_check_return &ret3,
                                class area_check_return &ret4);
Matrix54i move_2x2_left(Matrix54i &puzzle, class area_check_return &ret,
                                class area_check_return &ret2, class area_check_return &ret3,
                                class area_check_return &ret4);
Matrix54i move_2x2_up(Matrix54i &puzzle, class area_check_return &ret,
                                class area_check_return &ret2, class area_check_return &ret3,
                                class area_check_return &ret4);

Matrix54i move_2x2_down(Matrix54i &puzzle, class area_check_return &ret,
                                class area_check_return &ret2, class area_check_return &ret3,
                                class area_check_return &ret4);

Matrix54i num_simple(Matrix54i puzzle, int i);

Matrix54i board_simple(Matrix54i &puzzle);
bool check_rightside(Matrix54i puzzle, int checkval);
bool check_leftside(Matrix54i puzzle, int checkval);
bool check_upside(Matrix54i puzzle, int checkval);
bool check_downside(Matrix54i puzzle, int checkval);
std::vector<int> right_movable_list(Matrix54i puzzle);
std::vector<int> left_movable_list(Matrix54i puzzle);
std::vector<int> up_movable_list(Matrix54i puzzle);
std::vector<int> down_movable_list(Matrix54i puzzle);
Matrix54i movepuzzle_right(Matrix54i &puzzle,int val);
Matrix54i movepuzzle_left(Matrix54i &puzzle,int val);
Matrix54i movepuzzle_up(Matrix54i &puzzle,int val);
Matrix54i movepuzzle_down(Matrix54i &puzzle,int val);
std::vector<Matrix54i> move_right(Matrix54i &puzzle);
std::vector<Matrix54i> move_left(Matrix54i &puzzle);
std::vector<Matrix54i> move_up(Matrix54i &puzzle);
std::vector<Matrix54i> move_down(Matrix54i &puzzle);
std::vector<Matrix54i> moved_board_list(Matrix54i &puzzle);
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


bool exist(std::string hash_puzzle, std::vector<std::string>  puzzle_state);
std::vector<Matrix54i> route(std::unordered_map<Matrix54i, Matrix54i , KeyHasher, KeyEqual> &edges, Matrix54i moved_puzzle);
void queue_state_append(Matrix54i before_moving, std::vector<Matrix54i> movable, std::vector<std::string> &puzzle_state,
                       std::unordered_map<Matrix54i, Matrix54i , KeyHasher, KeyEqual> &edges, std::queue<Matrix54i> &puzzle_list, std::vector<std::vector<Matrix54i>> &c_route);
std::vector<std::vector<Matrix54i>> breadth_first_search(Matrix54i &puzzle);
int shortest(std::vector<std::vector<Matrix54i>> &c_route);

#endif