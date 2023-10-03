
#include <iostream>
#include <cstdio>
#include <cstring>
#include <Eigen/Dense>
#include <vector>
#include"method.h"


int main() {
    Matrix54i puzzle = init_puzzle();
std::vector<std::vector<Matrix54i>>  route = breadth_first_search(puzzle);
int min = shortest(route);
std::cout << "最短経路は" << min << "手です" << std::endl;
    return 0;
}