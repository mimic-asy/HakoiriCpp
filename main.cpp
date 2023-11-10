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
    const Matrix54i puzzle = init_puzzle();
    std::vector<Node> route = bfs(puzzle);

    std::ofstream myfile;
    myfile.open("example.csv");
    for (Node &nd :route)
    {
        std::string one_colmn = mat_to_str_pluscomma(nd.puzzle);
        one_colmn.pop_back();
        one_colmn += "\n";
        myfile << one_colmn;
    }
    myfile.close();

    return 0;
}