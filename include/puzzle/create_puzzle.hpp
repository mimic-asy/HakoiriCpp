#ifndef HAKOIRICPP_METHOD_H
#define HAKOIRICPP_METHOD_H

#include <Eigen/Dense>
#include <vector>
#include <queue>
#include <unordered_map>
#include <Functional>
#include <fstream>

using Matrix54i = Eigen::Matrix<int, 5, 4>;

class Location {
public:
    int val;
    int y;
    int x;

    void Func(int yv, int xv, int v);

};