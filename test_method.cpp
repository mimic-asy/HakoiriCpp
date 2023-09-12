#include "method.h"
#include "gtest/gtest.h"
#include <iostream>
#include <Eigen/Dense>
#include <vector>



namespace {



//swap
TEST(swap, puzzle){
Eigen::MatrixXi puzzle0 = init_puzzle();
Eigen::MatrixXi puzzle1 = init_puzzle();

swap(puzzle0, 0, 0, 1, 1);
}



//area_check tests
TEST(area_check, Value){
Eigen::MatrixXi puzzle = init_puzzle();
std::vector<area_check_return> test1;
test1 = area_check(puzzle,1);
ASSERT_EQ(test1[0].val,1);
ASSERT_EQ(test1[0].y,0);
ASSERT_EQ(test1[0].x,0);
ASSERT_EQ(test1[1].val,1);
ASSERT_EQ(test1[1].y,1);
ASSERT_EQ(test1[1].x,0);
}

TEST(area_check, Value0){
Eigen::MatrixXi puzzle = init_puzzle();
std::vector<area_check_return> test0;
test0 = area_check(puzzle,0);
ASSERT_EQ(test0[0].val,0);
ASSERT_EQ(test0[0].y,0);
ASSERT_EQ(test0[0].x,1);
ASSERT_EQ(test0[1].val,0);
ASSERT_EQ(test0[1].y,0);
ASSERT_EQ(test0[1].x,2);
ASSERT_EQ(test0[2].val,0);
ASSERT_EQ(test0[2].y,1);
ASSERT_EQ(test0[2].x,1);
ASSERT_EQ(test0[3].val,0);
ASSERT_EQ(test0[3].y,1);
ASSERT_EQ(test0[3].x,2);
}


TEST(area_check, Value5){
Eigen::MatrixXi puzzle = init_puzzle();
std::vector<area_check_return> test2;
test2 = area_check(puzzle,5);
ASSERT_EQ(test2[0].val,5);
ASSERT_EQ(test2[0].y,2);
ASSERT_EQ(test2[0].x,1);
ASSERT_EQ(test2[1].val,5);
ASSERT_EQ(test2[1].y,2);
ASSERT_EQ(test2[1].x,2);
}

}

