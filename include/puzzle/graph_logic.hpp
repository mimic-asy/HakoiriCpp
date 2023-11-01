#ifndef HAKOIRICPP_GRAPH_LOGIC_HPP
#define HAKOIRICPP_GRAPH_LOGIC_HPP

#include <Eigen/Dense>
#include <vector>
#include <queue>
#include <unordered_map>
#include <functional>
#include <fstream>
#include "puzzle/puzzle_logic.hpp"

std::string to_hashable(const Matrix54i &simple_puzzle);

struct node
{
    int puzzle;
    int cost;
    std::vector<node> side_node;
};

struct KeyHasher
{ // インスタンスを取得する->operator
    int operator()(const Matrix54i &a) const
    {
        std::string a_str = to_hashable(const_cast<Matrix54i &>(a));
        std::hash<std::string> hash_fn;
        size_t hash_value = hash_fn(a_str);
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
struct KeyHasher_std
{
    int operator()(const std::string &key) const
    {
        std::hash<std::string> hash_fn;
        size_t hash_value = hash_fn(key);
        return hash_value;
    }
};

// カスタムキー比較関数の構造体 (KeyEqual)
struct KeyEqual_std
{
    bool operator()(const std::string &lhs, const std::string &rhs) const
    {

        return lhs == rhs;
    }
};
using comparative_index = std::unordered_map<std::string, std::string, KeyHasher_std, KeyEqual_std>;
using node_index = std::unordered_map<Matrix54i, node, KeyHasher, KeyEqual>;
bool isvalue_already(const comparative_index &puzzle_index, const std::string &hash_puzzle);
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
std::string to_hashable_pluscomma(const Matrix54i &simple_puzzle);
bool exist(const std::string &hash_puzzle,
           std::vector<std::string> &puzzle_state);
std::vector<Matrix54i> clearroute(std::unordered_map<Matrix54i, Matrix54i,
                                                     KeyHasher, KeyEqual> &edges,
                                  const Matrix54i &moved_puzzle);
void queue_state_append(const Matrix54i &before_moving, std::vector<Matrix54i> &movable,
                        std::vector<std::string> &puzzle_state,
                        std::unordered_map<Matrix54i, Matrix54i, KeyHasher, KeyEqual> &edges,
                        std::queue<Matrix54i> &puzzle_list,
                        std::vector<std::vector<Matrix54i>> &c_route);
std::vector<std::vector<Matrix54i>> breadth_first_search(const Matrix54i &puzzle);
std::vector<Matrix54i> shortestroute_find(const std::vector<std::vector<Matrix54i>> &c_route);
bool keyexists(const std::unordered_map<Matrix54i, Matrix54i, KeyHasher, KeyEqual> &puzzle_index, const std::string &key);

void fastqueue(Matrix54i now_puzzle,
               std::vector<Matrix54i> movable,
               std::vector<std::string> &puzzle_state,
               std::unordered_map<Matrix54i, std::vector<Matrix54i>, KeyHasher, KeyEqual> &edges,
               std::queue<Matrix54i> &puzzle_list,
               std::vector<std::vector<Matrix54i>> &c_route);
std::vector<std::vector<Matrix54i>> breadth_first_search_fast(Matrix54i &puzzle);
std::vector<Matrix54i> fastclearroute(std::unordered_map<Matrix54i, std::vector<Matrix54i>, KeyHasher, KeyEqual> &edges,
                                      const Matrix54i moved_puzzle);

node dikstr(node &now_node);
std::vector<std::vector<node>> breadth_first_search_dikstr(const Matrix54i &puzzle, std::vector<Matrix54i> &matrix_index);
void dikstrqueue(
    int &count_matrix,
    const int i,
    const Matrix54i &now_puzzle,
    const std::vector<Matrix54i> &movable,
    comparative_index &puzzle_index,
    node_index &edges,
    std::vector<node> &clear_nodes,
    std::queue<Matrix54i> &puzzle_list,
    std::vector<Matrix54i> &matrix_index);
std::vector<node> shortestroute_find_dikstr(const std::vector<std::vector<node>> &c_route);
void make_newnode(const int &count_matrix, const int i, node &new_node, const node &now);

#endif