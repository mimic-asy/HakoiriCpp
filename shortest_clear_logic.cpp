#include <iostream>
#include <cstdio>
#include <cstring>
#include <Eigen/Dense>
#include <chrono>
#include <map>
#include "puzzle/puzzle_logic.hpp"
#include "puzzle/graph_logic.hpp"

inline void node::set_node(const Matrix54i puz, const int cos, const node &nd)
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

void make_newnode(const Matrix54i state, const int i, node &new_node, const node &now)
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
            std::cout << new_node.cost << std::endl;
            edges[state_simple] = new_node;
            puzzle_index[hash_puzzle] = hash_puzzle;
            puzzle_list.push(state);

            if (clear(state))
            {
                std::vector<node> route;
                while (new_node.cost > 0)
                {
                    route.push_back(new_node);
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

        const Matrix54i now_puzzle = puzzle_list.front();
        puzzle_list.pop();
        std::vector<Matrix54i> movable = moved_board_list(now_puzzle);
        i++;
        dikstrqueue(i, now_puzzle, movable,
                    puzzle_index, edges, clear_route, puzzle_list);
    }

    std::vector<node> s = shortestroute_find_dikstr(clear_route);
    std::cout << "総手数は" << puzzle_index.size() << "手です" << std::endl;
    std::cout << "クリアルートは" << s.size() << "手です" << std::endl;

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
            min_node = n;
            min = min_node.cost;
        }
        if (min > n.cost)
        {
            min_node = n;
            min = min_node.cost;
        }
    }

    return min_node;
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