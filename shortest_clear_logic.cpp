#include <iostream>
#include <cstdio>
#include <cstring>
#include <Eigen/Dense>
#include <chrono>
#include <map>
#include "puzzle/puzzle_logic.hpp"
#include "puzzle/graph_logic.hpp"




std::size_t to_hash(const Matrix54i &simple_puzzle)
{
    std::size_t hash;
    int rows = simple_puzzle.rows();
    int cols = simple_puzzle.cols();

    for (int y = 0; y < rows; y++)
    {
        for (int x = 0; x < cols; x++)
        {
            int num = simple_puzzle(y, x);
            hash ^= num + 0x9e3779b9 + (hash << 6) + (hash >> 2);
        }
    }
    return hash;
}

bool isvalue_already(const comparative_index &puzzle_index, const size_t &hash_puzzle)
{
    auto it = puzzle_index.find(hash_puzzle);
    return it != puzzle_index.end();
}

void make_newnode(const int &count_matrix, const int i, node &new_node, const node &now)
{
    new_node.puzzle = count_matrix;
    new_node.cost = i;
    new_node.side_node.push_back(now);
}

void dikstrqueue(
    int &count_matrix,
    const int i,
    const Matrix54i &now_puzzle,
    const std::vector<Matrix54i> &movable,
    comparative_index &puzzle_index,
    node_index &edges,
    std::vector<node> &clear_nodes,
    std::queue<Matrix54i> &puzzle_list,
    std::vector<Matrix54i> &matrix_index)
{
    Matrix54i copy_now_puzzle = now_puzzle;
    Matrix54i now_simple = board_simple(copy_now_puzzle);
    node now = edges.at(now_simple);

    for (const Matrix54i &state : movable)
    {
        Matrix54i state_copy = state;
        Matrix54i state_simple = board_simple(state_copy);
        std::string hash_puzzle = mat_to_str(state_simple);
        std::hash<std::string> hash_fn;
        size_t hash_value = hash_fn(hash_puzzle);

        if (!isvalue_already(puzzle_index, hash_value))
        {
            node new_node;
            matrix_index.push_back(state);
            count_matrix++;
            make_newnode(count_matrix, i, new_node, now);
            edges[state_simple] = new_node;
            puzzle_index.insert(hash_value);
            puzzle_list.push(state);

            if (clear(state))
            {
                clear_nodes.push_back(new_node);

            }
        }
        else
        {
            node already = edges.at(state_simple);
            already.side_node.push_back(now);
        }
    }
}

std::vector<std::vector<node>> breadth_first_search_dikstr(const Matrix54i &puzzle, std::vector<Matrix54i> &matrix_index)
{
    // sengen
    node_index edges;
    comparative_index puzzle_index;
    std::queue<Matrix54i> puzzle_list;
    std::vector<node> clear_nodes;
    std::vector<std::vector<node>> clear_routes;
    node first_node;
    // dequeに初期盤面を追加
    puzzle_list.push(puzzle);
    // puzzleを複製
    // puzzleを比較するための形にする
    Matrix54i simple_puzzle = board_simple(puzzle);
    // string型に変換する
    std::string str = mat_to_str(simple_puzzle);

    // nodeの設定を行う
    int count_matrix = 0;
    matrix_index.push_back(puzzle);
    first_node.puzzle = count_matrix;
    first_node.cost = 0;
    edges[simple_puzzle] = first_node;
    std::hash<std::string> hash_fn;
    size_t str_val = hash_fn(str);
    puzzle_index.insert(str_val);
    int i = 0;

    while (!puzzle_list.empty())
    {

        const Matrix54i now_puzzle = puzzle_list.front();
        puzzle_list.pop();
        std::vector<Matrix54i> movable = moved_board_list(now_puzzle);
        i++;
        dikstrqueue(count_matrix, i, now_puzzle, movable,
                    puzzle_index, edges, clear_nodes, puzzle_list ,matrix_index);
    }


    for(node &clear_node : clear_nodes){
        std::vector<node> route;
        while (clear_node.cost > 0)
        {
            route.push_back(clear_node);
            clear_node = dikstr(clear_node);
        }
        clear_routes.push_back(route);
    }

    std::vector<node> s = shortestroute_find_dikstr(clear_routes);
    std::cout << "総手数は" << puzzle_index.size() << "手です" << std::endl;
    std::cout << "クリアルートは" << s.size() << "手です" << std::endl;

    return clear_routes;
}

node dikstr(node &now_node)
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