
#include <iostream>
#include <cstdio>
#include <cstring>
#include <Eigen/Dense>
#include <vector>
#include <chrono>

#include "puzzle/puzzle_method.hpp"

/*
int main() {
Matrix54i puzzle = init_puzzle();
std::vector<std::vector<Matrix54i>>  route = breadth_first_search(puzzle);
std::vector<Matrix54i> min = shortestroute_find(route);
std::cout << "最短経路は" << min.size() << "手です" << std::endl;
std::ofstream myfile;
myfile.open ("example.csv");
for(Matrix54i& node: min){
    std::string one_colmn =  to_hashable_pluscomma(node);
    std::cout << one_colmn << "\n"<< std::endl;
    one_colmn.pop_back();
    one_colmn += "\n";
    myfile << one_colmn;
}
myfile.close();

    return 0;
}
*/

// 速度計測用
int main()
{

    Matrix54i puzzle = init_puzzle();
    std::vector<std::vector<Matrix54i>> route = breadth_first_search_usetime(puzzle);

    return 0;
}