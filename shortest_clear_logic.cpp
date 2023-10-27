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

void dikstrqueue(const int i,
                 const Matrix54i & now_puzzle,
                 const std::vector<Matrix54i> & movable,
                 std::unordered_map<std::string, std::string, KeyHasher_std, KeyEqual_std> &puzzle_index,
                 std::unordered_map<Matrix54i, node, KeyHasher, KeyEqual> &edges,
                 std::vector<std::vector<node>> &clear_route,
                 std::queue<Matrix54i> &puzzle_list)
{


    for (const Matrix54i &state : movable)
    {
        
        node now = edges.at(now_puzzle);
        std::string hash_puzzle = to_hashable(state);

        assert((edges.find(state) != edges.end()) == isvalue_already(puzzle_index, hash_puzzle));
        if (!isvalue_already(puzzle_index, hash_puzzle))
        {
            node new_node;
            new_node.puzzle = state;
            new_node.cost = i;
            new_node.side_node.push_back(now);
            now.side_node.push_back(new_node);
            edges[state] = new_node;
            puzzle_index[hash_puzzle] = hash_puzzle;
            puzzle_list.push(state);


            if (clear(state))
            {
                std::vector<node> route;

                while (new_node.cost == 0)
                {
                    route.push_back(new_node);
                    new_node = dikstr(new_node);
                }
                clear_route.push_back(route);
            }
        }
        else
        {
            node already = edges.at(state);
            already.side_node.push_back(now);
            if(find_side(now,already)){
                now.side_node.push_back(already);
            }

        }
    }
}

bool find_side(node already, node now)
{
    for (node side : already.side_node)
    {
        if (side.puzzle == now.puzzle)
        {
            return false;
        }
    }
    return true;
}

std::vector<std::vector<node>> breadth_first_search_dikstr(const Matrix54i &puzzle)
{
    std::unordered_map<Matrix54i, node, KeyHasher, KeyEqual> edges;
    std::unordered_map<std::string, std::string, KeyHasher_std, KeyEqual_std> puzzle_index;
    std::queue<Matrix54i> puzzle_list;

    std::vector<std::vector<node>> clear_route;
    puzzle_list.push(puzzle);
    node first_node;
    first_node.puzzle = puzzle;
    first_node.cost = 0;
    edges[puzzle] = first_node;

    Matrix54i copy_puzzle = puzzle;
    std::string str = to_hashable(puzzle);
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
    //最も小さいノードを定義
    node min_node;
    //今のパズルをプリント
    std::cout << now_node.puzzle << std::endl;

    for (node n : now_node.side_node)
    {

        int min = -1;
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
    std::cout << min_node.cost << std::endl;
    std::cout << min_node.puzzle << std::endl;

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