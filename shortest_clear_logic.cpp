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

size_t be_hash_to_simpleboard(const Matrix54i &puzzle)
{
    return to_hash(board_simple(puzzle));
}

std::vector<Node> bfs(const Matrix54i &puzzle)
{
    std::unordered_map<size_t, Node> node_hash_map; // in to the node unorderdmap
    std::unordered_set<size_t> board_hash_value;    // have boards hash value
    std::queue<Matrix54i> puzzle_list;              // puzzle_list
    std::vector<Node> clear_boards;                 // clear boards
    std::vector<std::vector<Node>> clear_routes;    // clear_route

    puzzle_list.push(puzzle); // puzzle list in first node

    size_t hash = be_hash_to_simpleboard(puzzle);
    Node first_node{puzzle, 0, std::vector<Node>{}};                         // to be hash value for puzzle
    node_hash_map[hash] = first_node; // input node map puzzle
    board_hash_value.insert(hash);                                         // input board_hash_value puzzle

    int cost = 0;

    while (!puzzle_list.empty())
    {
        cost++;
        const Matrix54i now_puzzle = puzzle_list.front();
        puzzle_list.pop();

        Node now_node = node_hash_map.at(be_hash_to_simpleboard(now_puzzle));

        for (const Matrix54i &state : moved_board_list(now_puzzle))
        {
            size_t hash_value = be_hash_to_simpleboard(state);
            if (board_hash_value.find(hash_value) != board_hash_value.end())
            {
                continue;
            }
                Node new_node;
                new_node.side_node.push_back(now_node);
                new_node.cost = cost;
                new_node.puzzle = state;
                node_hash_map[hash_value] = new_node; // input new_node HashNodeMap

                board_hash_value.insert(hash_value); // input hashvalue
                puzzle_list.push(state);

                if (clear(state))
                {
                    clear_boards.push_back(new_node);
                }

        }
    }

    for (Node &clear_node : clear_boards)
    {
        std::vector<Node> route;
        while (clear_node.cost > 0)
        {
            route.push_back(clear_node);
            clear_node = clear_node.side_node[0];
        }
        clear_routes.push_back(route);
    }

    std::vector<Node> s = find_shortest_route(clear_routes);
    std::cout << "総手数は" << board_hash_value.size() << "手です" << std::endl;
    std::cout << "クリアルートは" << s.size() << "手です" << std::endl;

    return s;
}


std::vector<Node> find_shortest_route(const std::vector<std::vector<Node>> &clear_route)
{
    std::vector<Node> shortest_vec;
    bool first = true;
    for (std::vector<Node> vec : clear_route)
    {
        if (first)
        {
            first = false;
            shortest_vec = vec;
            continue;
        }

        if (shortest_vec.size() > vec.size())
        {
            shortest_vec = vec;
            continue;
        }
    }
    return shortest_vec;
}