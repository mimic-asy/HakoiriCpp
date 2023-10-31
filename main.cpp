
#include <iostream>
#include <cstdio>
#include <cstring>
#include <Eigen/Dense>
#include <vector>
#include <chrono>

#include "puzzle/graph_logic.hpp"
#include "puzzle/puzzle_logic.hpp"

int main()
{
    Matrix54i puzzle = init_puzzle();
    std::vector<std::vector<node>> route = breadth_first_search_dikstr(puzzle);
    std::vector<node> min = shortestroute_find_dikstr(route);

    std::ofstream myfile;
    myfile.open("example.csv");
    for (node &n : min)
    {
        std::string one_colmn = to_hashable_pluscomma(n.puzzle);
        one_colmn.pop_back();
        one_colmn += "\n";
        myfile << one_colmn;
    }
    myfile.close();

    return 0;
}