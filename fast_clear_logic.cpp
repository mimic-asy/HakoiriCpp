#include <iostream>
#include <cstdio>
#include <cstring>
#include <Eigen/Dense>
#include <chrono>
#include <map>
#include "puzzle/puzzle_logic.hpp"
#include "puzzle/graph_logic.hpp"


void fastqueue(Matrix54i now_puzzle,
               std::vector<Matrix54i> movable,
               std::unordered_map<std::string, std::string, KeyHasher_std, KeyEqual_std> &puzzle_index,
               std::unordered_map<Matrix54i, std::vector<Matrix54i>, KeyHasher, KeyEqual> &edges,
               std::queue<Matrix54i> &puzzle_list,
               std::vector<std::vector<Matrix54i>> &c_route)
{
    std::vector<Matrix54i> equal_stock;
    if (now_puzzle != init_puzzle())
    {
        equal_stock = edges[now_puzzle];
    }
    else
    {
        equal_stock.push_back(now_puzzle);
    }

    for (Matrix54i &state : movable)
    {
        Matrix54i state_copy = state;

        Matrix54i simple_puzzle = board_simple(state_copy);

        std::string hash_puzzle = to_hashable(simple_puzzle);
        if (!isvalue_already(puzzle_index, hash_puzzle))
        {
            equal_stock.push_back(state);
            edges[state] = equal_stock;
            puzzle_index[hash_puzzle] = hash_puzzle;
            puzzle_list.push(state);
            if (clear(state))
            {
                std::vector<Matrix54i> add_c_route = fastclearroute(edges, state);
                c_route.push_back(add_c_route);
            }
        }
    }
}

std::vector<std::vector<Matrix54i>> breadth_first_search_fast(Matrix54i &puzzle)
{
    std::vector<std::vector<Matrix54i>> c_route;
    std::unordered_map<Matrix54i, std::vector<Matrix54i>, KeyHasher, KeyEqual> edges;
    std::unordered_map<std::string, std::string, KeyHasher_std, KeyEqual_std> puzzle_index;
    std::queue<Matrix54i> puzzle_list;
    Matrix54i copy_puzzle = puzzle;
    puzzle_list.push(puzzle);

    Matrix54i simple_puzzle = board_simple(copy_puzzle);
    std::string str = to_hashable(simple_puzzle);
    puzzle_index[str] = str;

    while (!puzzle_list.empty())
    {
        Matrix54i now_puzzle = puzzle_list.front();
        puzzle_list.pop();
        std::vector<Matrix54i> movable = moved_board_list(now_puzzle);
        fastqueue(now_puzzle, movable,
                  puzzle_index, edges, puzzle_list, c_route);
    }
    std::cout << "総手数は" << puzzle_index.size() << "手です" << std::endl;
    return c_route;
}

std::vector<Matrix54i> fastclearroute(std::unordered_map<Matrix54i, std::vector<Matrix54i>, KeyHasher, KeyEqual> &edges,
                                      const Matrix54i moved_puzzle)
{
    std::vector<Matrix54i> c_route = edges[moved_puzzle];
    return c_route;
}