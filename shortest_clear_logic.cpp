#include <iostream>
#include <cstdio>
#include <cstring>
#include <Eigen/Dense>
#include <chrono>
#include <map>
#include "puzzle/puzzle_logic.hpp"
#include "puzzle/graph_logic.hpp"

inline void node::set_node(Matrix54i puz, int cos, node nd)
{
    puzzle = puz;
    cost = cos;
    side_node.push_back(nd);
}

bool isvalue_already(const std::unordered_map<std::string, std::string, KeyHasher_std, KeyEqual_std> &puzzle_index, const std::string hash_puzzle)
{
    auto it = puzzle_index.find(hash_puzzle);
    return it != puzzle_index.end();
}

void make_newnode(const Matrix54i state, int i, node new_node, node now)
{
    new_node.puzzle = state;
    new_node.cost = i;
    new_node.side_node.push_back(now);
}

void dikstrqueue(const int i,
                 const Matrix54i &now_puzzle,
                 const std::vector<Matrix54i> &movable,
                 std::unordered_map<std::string, std::string, KeyHasher_std, KeyEqual_std> &puzzle_index,
                 std::unordered_map<Matrix54i, node, KeyHasher, KeyEqual> &edges,
                 std::vector<std::vector<node>> &clear_route,
                 std::queue<Matrix54i> &puzzle_list)
{
    Matrix54i copy_now_puzzle = now_puzzle;
    Matrix54i now_simple = board_simple(copy_now_puzzle);
    node now = edges.at(now_simple);

    for (const Matrix54i &state : movable)
    {
        Matrix54i state_copy = state;
        Matrix54i state_simple = board_simple(state_copy);
        std::string hash_puzzle = to_hashable(state_simple);

        if (!isvalue_already(puzzle_index, hash_puzzle))
        {
            node new_node;
            make_newnode(state, i, new_node, now);
            edges[state_simple] = new_node;
            puzzle_index[hash_puzzle] = hash_puzzle;
            puzzle_list.push(state);

            if (clear(state))
            {
                std::vector<node> route;
                while (new_node.cost>0)
                {
                    route.push_back(new_node);
                    std::cout << new_node.cost << std::endl;
                    new_node = dikstr(new_node);
                }
                clear_route.push_back(route);
            }
        }
        else
        {
            node already = edges.at(state_simple);
            already.side_node.push_back(now);
        }
    }
}

std::vector<std::vector<node>> breadth_first_search_dikstr(const Matrix54i &puzzle)
{
    // sengen
    std::unordered_map<Matrix54i, node, KeyHasher, KeyEqual> edges;
    std::unordered_map<std::string, std::string, KeyHasher_std, KeyEqual_std> puzzle_index;
    std::queue<Matrix54i> puzzle_list;
    std::vector<std::vector<node>> clear_route;
    node first_node;
    // dequeに初期盤面を追加
    puzzle_list.push(puzzle);
    // puzzleを複製
    Matrix54i copy_puzzle = puzzle;
    // puzzleを比較するための形にする
    Matrix54i simple_puzzle = board_simple(copy_puzzle);
    // string型に変換する
    std::string str = to_hashable(simple_puzzle);

    // nodeの設定を行う
    first_node.puzzle = puzzle;
    first_node.cost = 0;
    edges[simple_puzzle] = first_node;
    puzzle_index[str] = str;
    int i = 0;
    while (!puzzle_list.empty())
    {
        i++;
        const Matrix54i now_puzzle = puzzle_list.front();
        puzzle_list.pop();
        std::vector<Matrix54i> movable = moved_board_list(now_puzzle);
        dikstrqueue(i, now_puzzle, movable,
                    puzzle_index, edges, clear_route, puzzle_list);
    }
    std::cout << "総手数は" << puzzle_index.size() << "手です" << std::endl;
    std::cout << "クリアルートは" << clear_route.size() << "手です" << std::endl;

    return clear_route;
}

node dikstr(node now_node)
{
    // 最も小さいノードを定義
    node min_node;
    int min = -1;

    for (node n : now_node.side_node)
    {
        if (min == -1)
        {
            min = n.cost;
            min_node = n;
        }
        if (min > n.cost)
        {
            min = n.cost;
            min_node = n;
        }
        else if (min == n.cost)
        {
            min_node = dikstrloop(min_node, n);
        }
    }

    return min_node;
}

node dikstrloop(node min, node n)
{
    node min_next = dikstr(min);
    node n_next = dikstr(n);
    if (min_next.cost > n_next.cost)
    {
        return n_next;
    }
    else if (min_next.cost == n_next.cost)
    {
        return dikstrloop(min_next, n_next);
    }
    else
    {
        return min_next;
    }
}

std::vector<node> shortestroute_find_dikstr(const std::vector<std::vector<node>> &c_route)
{
    std::vector<node> shortest_vec;
    bool isFirst = true;
    for (std::vector<node> v : c_route)
    {
        if (isFirst || v.size() < shortest_vec.size())
        {
            shortest_vec = v;
            isFirst = false;
        }
    }
    return shortest_vec;
}