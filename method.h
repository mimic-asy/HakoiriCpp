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

    void Func(int yv, int xv, int v);

};

void swap(Eigen::MatrixXi &puzzle,int y1,int x1,int y2,int x2);
std::vector<area_check_return> area_check(Eigen::MatrixXi puzzle, int targetValue);
bool inrange_check_right(class area_check_return ret);
bool inrange_check_left(class area_check_return ret);
bool inrange_check_up(class area_check_return ret);
bool inrange_check_down(class area_check_return ret);
bool vacant_check_right(Eigen::MatrixXi puzzle, class area_check_return ret);
bool vacant_check_left(Eigen::MatrixXi puzzle, class area_check_return ret);
bool vacant_check_up(Eigen::MatrixXi puzzle, class area_check_return ret);
bool vacant_check_down(Eigen::MatrixXi puzzle, class area_check_return ret);
Eigen::MatrixXi move_1x1_to_right(Eigen::MatrixXi &puzzle, class area_check_return &ret);
Eigen::MatrixXi move_1x1_to_left(Eigen::MatrixXi &puzzle, class area_check_return &ret);
Eigen::MatrixXi move_1x1_to_up(Eigen::MatrixXi &puzzle, class area_check_return &ret);
Eigen::MatrixXi move_1x1_to_down(Eigen::MatrixXi &puzzle, class area_check_return &ret);
Eigen::MatrixXi move_2x1_to_left(Eigen::MatrixXi &puzzle, class area_check_return &ret, class area_check_return &ret2);
Eigen::MatrixXi move_2x1_to_right(Eigen::MatrixXi &puzzle, class area_check_return &ret, class area_check_return &ret2);
Eigen::MatrixXi move_2x1_to_up(Eigen::MatrixXi &puzzle, class area_check_return &ret, class area_check_return &ret2);
Eigen::MatrixXi move_2x1_to_down(Eigen::MatrixXi &puzzle, class area_check_return &ret, class area_check_return &ret2);

Eigen::MatrixXi move_2x2_right(Eigen::MatrixXi &puzzle, class area_check_return &ret,
                                class area_check_return &ret2, class area_check_return &ret3,
                                class area_check_return &ret4);
Eigen::MatrixXi move_2x2_left(Eigen::MatrixXi &puzzle, class area_check_return &ret,
                                class area_check_return &ret2, class area_check_return &ret3,
                                class area_check_return &ret4);
Eigen::MatrixXi move_2x2_up(Eigen::MatrixXi &puzzle, class area_check_return &ret,
                                class area_check_return &ret2, class area_check_return &ret3,
                                class area_check_return &ret4);

Eigen::MatrixXi move_2x2_down(Eigen::MatrixXi &puzzle, class area_check_return &ret,
                                class area_check_return &ret2, class area_check_return &ret3,
                                class area_check_return &ret4);

#endif