#ifndef HAKOIRICPP_METHOD_H
#define HAKOIRICPP_METHOD_H

#include <Eigen/Dense>
#include <vector>

Eigen::MatrixXi init_puzzle();

class area_check_return {
public:
    int val;
    int y;
    int x;
};

Eigen::MatrixXi swap(Eigen::MatrixXi puzzle,int y1,int x1,int y2,int x2);

std::vector<area_check_return> area_check(Eigen::MatrixXi puzzle, int targetValue);
#endif