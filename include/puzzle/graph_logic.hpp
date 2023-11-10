#ifndef HAKOIRICPP_GRAPH_LOGIC_HPP
#define HAKOIRICPP_GRAPH_LOGIC_HPP

#include <Eigen/Dense>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <functional>
#include <fstream>
#include "puzzle/puzzle_logic.hpp"

std::string mat_to_str(const Matrix54i &simple_puzzle);
std::size_t to_hash(const Matrix54i &simple_puzzle);

struct Node
{
    Matrix54i puzzle;
    int cost;
    std::vector<Node> side_node;
};

struct KeyHasher
{ // インスタンスを取得する->operator
    int operator()(const Matrix54i &a) const
    {
        size_t hash_value = to_hash(a);
        return hash_value;
    }
};

struct KeyEqual
{
    bool operator()(const Matrix54i &a, const Matrix54i &b) const
    {
        return a == b;
    }
};



bool clear(const Matrix54i &puzzle);
Matrix54i num_simple(const Matrix54i &puzzle, const int i);
Matrix54i board_simple(const Matrix54i &puzzle);
bool range_and_emptycheck_right(const Matrix54i &puzzle, const class find_location_return &ret);
bool range_and_emptycheck_left(const Matrix54i &puzzle, const class find_location_return &ret);
bool range_and_emptycheck_up(const Matrix54i &puzzle, const class find_location_return &ret);
bool range_and_emptycheck_down(const Matrix54i &puzzle, const class find_location_return &ret);
bool check_rightside(const Matrix54i &puzzle, const int checkval);
bool check_leftside(const Matrix54i &puzzle, const int checkval);
bool check_upside(const Matrix54i &puzzle, const int checkval);
bool check_downside(const Matrix54i &puzzle, const int checkval);
std::vector<int> numbers_canmove_right(const Matrix54i &puzzle);
std::vector<int> numbers_canmove_left(const Matrix54i &puzzle);
std::vector<int> numbers_canmove_up(const Matrix54i &puzzle);
std::vector<int> numbers_canmove_down(const Matrix54i &puzzle);
Matrix54i movepuzzle_right(const Matrix54i &puzzle, const int val);
Matrix54i movepuzzle_left(const Matrix54i &puzzle, const int val);
Matrix54i movepuzzle_up(const Matrix54i &puzzle, const int val);
Matrix54i movepuzzle_down(const Matrix54i &puzzle, const int val);
std::vector<Matrix54i> move_right(const Matrix54i &puzzle);
std::vector<Matrix54i> move_left(const Matrix54i &puzzle);
std::vector<Matrix54i> move_up(const Matrix54i &puzzle);
std::vector<Matrix54i> move_down(const Matrix54i &puzzle);
std::vector<Matrix54i> moved_board_list(const Matrix54i &puzzle);
std::string mat_to_str_pluscomma(const Matrix54i &simple_puzzle);
std::vector<Matrix54i> shortestroute_find(const std::vector<std::vector<Matrix54i>> &c_route);
bool keyexists(const std::unordered_map<Matrix54i, Matrix54i, KeyHasher, KeyEqual> &puzzle_index, const std::string &key);
std::vector<Node> find_shortest_route(const std::vector<std::vector<Node>> &clear_route);
std::vector<Node> bfs(const Matrix54i &puzzle);
Node find_min_cost(const Node &node);
size_t be_hash_to_simpleboard(const Matrix54i &puzzle);




#endif