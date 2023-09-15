
#include <iostream>
#include <cstdio>
#include <cstring>
#include <Eigen/Dense>
#include <vector>
#include"method.h"


int main() {
    Eigen::MatrixXi puzzle = init_puzzle();
    area_check_return ret;
    ret.Func(0,1,0);
    puzzle = move_1x1_to_left(puzzle,ret);
    std::cout << puzzle << std::endl;

    /**

    std::vector<area_check_return> result = area_check(puzzle, 0);

    // ループを使用して結果を出力
    for (const auto& item : result) {
        std::cout << "Value: " << item.val << ", Y: " << item.y << ", X: " << item.x << std::endl;
    }
    */


    return 0;
}