#include "method.h"
#include "gtest/gtest.h"
#include <iostream>
#include <Eigen/Dense>
#include <vector>



namespace {



//swap tests
TEST(swap, puzzle0){
Matrix54i puzzle0 = init_puzzle();
Matrix54i puzzle1 = init_puzzle();


swap(puzzle0, 0, 0, 1, 1);
puzzle1(0,0) = 0;
puzzle1(1,1) = 1;
EXPECT_EQ(puzzle0,puzzle1);
}

TEST(swap, puzzle1){
Matrix54i puzzle2 = init_puzzle();
Matrix54i puzzle3 = init_puzzle();

swap(puzzle2, 4, 3, 0, 3);
swap(puzzle2, 4, 0, 0, 3);

puzzle3(4,3) = 2;
puzzle3(0,3) = 8;
puzzle3(4,0) = 9;
EXPECT_EQ(puzzle2, puzzle3);
}


//area_check tests
TEST(area_check, Value){
Matrix54i puzzle = init_puzzle();
std::vector<area_check_return> test1;
test1 = area_check(puzzle,1);
EXPECT_EQ(test1[0].val,1);
EXPECT_EQ(test1[0].y,0);
EXPECT_EQ(test1[0].x,0);
EXPECT_EQ(test1[1].val,1);
EXPECT_EQ(test1[1].y,1);
EXPECT_EQ(test1[1].x,0);
}

TEST(area_check, Value0){
Matrix54i puzzle = init_puzzle();
std::vector<area_check_return> test0;
test0 = area_check(puzzle,0);
EXPECT_EQ(test0[0].val,0);
EXPECT_EQ(test0[0].y,0);
EXPECT_EQ(test0[0].x,1);
EXPECT_EQ(test0[1].val,0);
EXPECT_EQ(test0[1].y,0);
EXPECT_EQ(test0[1].x,2);
EXPECT_EQ(test0[2].val,0);
EXPECT_EQ(test0[2].y,1);
EXPECT_EQ(test0[2].x,1);
EXPECT_EQ(test0[3].val,0);
EXPECT_EQ(test0[3].y,1);
EXPECT_EQ(test0[3].x,2);
}


TEST(area_check, Value5){
Matrix54i puzzle = init_puzzle();
std::vector<area_check_return> test2;
test2 = area_check(puzzle,5);
EXPECT_EQ(test2[0].val,5);
EXPECT_EQ(test2[0].y,2);
EXPECT_EQ(test2[0].x,1);
EXPECT_EQ(test2[1].val,5);
EXPECT_EQ(test2[1].y,2);
EXPECT_EQ(test2[1].x,2);
}

TEST(inrange_check_right, boolean){

area_check_return ret;
ret.Func(0,3,1);
EXPECT_FALSE(inrange_check_right(ret));
}

TEST (inrange_check_right, boolean1){
area_check_return ret2;
ret2.Func(0,2,1);

EXPECT_TRUE(inrange_check_right(ret2));
}

TEST(inrange_check_right, boolean2){
area_check_return ret3;
ret3.Func(0,-1,1);

EXPECT_FALSE(inrange_check_right(ret3));
}

TEST(inrange_check_right, boolean3){
area_check_return ret4;
ret4.Func(0,0,1);
EXPECT_TRUE(inrange_check_right(ret4));
}


TEST(inrange_check_left, boolean4){
area_check_return ret5;
ret5.Func(0,0,1);
EXPECT_FALSE(inrange_check_left(ret5));
}

TEST(inrange_check_left, boolean5){
area_check_return ret6;
ret6.Func(0,3,1);
EXPECT_TRUE(inrange_check_left(ret6));
}

TEST(inrange_check_left, boolean6){
area_check_return ret5;
ret5.Func(0,-1,1);
EXPECT_FALSE(inrange_check_left(ret5));
}

TEST(inrange_check_left, boolean7){
area_check_return ret5;
ret5.Func(0,5,1);
EXPECT_FALSE(inrange_check_left(ret5));
}

TEST(inrange_check_down, boolean8){
area_check_return ret5;
ret5.Func(5,0,1);
EXPECT_FALSE(inrange_check_down(ret5));
}

TEST(inrange_check_down, boolean9){
area_check_return ret5;
ret5.Func(0,0,1);
EXPECT_TRUE(inrange_check_down(ret5));
}

TEST(inrange_check_up, boolean10){
area_check_return ret5;
ret5.Func(4,0,1);
EXPECT_TRUE(inrange_check_up(ret5));
}


TEST(inrange_check_up, boolean11){
area_check_return ret5;
ret5.Func(0,0,1);
EXPECT_FALSE(inrange_check_up(ret5));
}


TEST(inrange_check_up, boolean12){
area_check_return ret5;
ret5.Func(-1,0,1);
EXPECT_FALSE(inrange_check_up(ret5));
}


TEST(inrange_check_up, boolean13){
area_check_return ret5;
ret5.Func(1,0,1);
EXPECT_TRUE(inrange_check_up(ret5));
}


TEST(inrange_check_up, boolean14){
area_check_return ret5;
ret5.Func(5,0,1);
EXPECT_FALSE(inrange_check_up(ret5));
}

TEST(vacant_check_right,bool0){
Matrix54i puzzle = init_puzzle();
area_check_return ret;
ret.Func(0,3,2);
EXPECT_FALSE(vacant_check_right(puzzle,ret));
}

TEST(vacant_check_right,bool1){
Matrix54i puzzle = init_puzzle();
area_check_return ret;
ret.Func(0,-1,2);
EXPECT_FALSE(vacant_check_right(puzzle,ret));
}

TEST(vacant_check_right,bool2){
Matrix54i puzzle = init_puzzle();
area_check_return ret;
ret.Func(0,5,2);
EXPECT_FALSE(vacant_check_right(puzzle,ret));
}

TEST(vacant_check_right,bool3){
Matrix54i puzzle = init_puzzle();
area_check_return ret;
ret.Func(4,0,8);
EXPECT_TRUE(vacant_check_right(puzzle,ret));
}

TEST(vacant_check_right,bool4){
Matrix54i puzzle = init_puzzle();
puzzle(0,3) = 10;
area_check_return ret;
ret.Func(0,2,0);
EXPECT_TRUE(vacant_check_right(puzzle,ret));
}

TEST(vacant_check_left,bool5){
Matrix54i puzzle = init_puzzle();
area_check_return ret;
ret.Func(4,3,9);
EXPECT_TRUE(vacant_check_left(puzzle,ret));
}

TEST(vacant_check_left,bool6){
Matrix54i puzzle = init_puzzle();
area_check_return ret;
puzzle(0,0) = 10;
ret.Func(0,1,0);
EXPECT_TRUE(vacant_check_left(puzzle,ret));
}

TEST(vacant_check_left,bool7){
Matrix54i puzzle = init_puzzle();
area_check_return ret;
ret.Func(0,0,0);
EXPECT_FALSE(vacant_check_left(puzzle,ret));
}

TEST(vacant_check_left,bool8){
Matrix54i puzzle = init_puzzle();
area_check_return ret;
ret.Func(0,-1,0);
EXPECT_FALSE(vacant_check_left(puzzle,ret));
}

TEST(vacant_check_left,bool9){
Matrix54i puzzle = init_puzzle();
area_check_return ret;
ret.Func(0,15,0);
EXPECT_FALSE(vacant_check_left(puzzle,ret));
}

TEST(vacant_check_up,bool10){
Matrix54i puzzle = init_puzzle();
area_check_return ret;
ret.Func(15,0,0);
EXPECT_FALSE(vacant_check_up(puzzle,ret));
}

TEST(vacant_check_up,bool11){
Matrix54i puzzle = init_puzzle();
area_check_return ret;
ret.Func(-1,0,0);
EXPECT_FALSE(vacant_check_up(puzzle,ret));
}

TEST(vacant_check_up,bool12){
Matrix54i puzzle = init_puzzle();
area_check_return ret;
puzzle(0,0) = 10;
ret.Func(1,0,0);
EXPECT_TRUE(vacant_check_up(puzzle,ret));
}

TEST(vacant_check_up,bool13){
Matrix54i puzzle = init_puzzle();
area_check_return ret;
puzzle(3,0) = 10;
ret.Func(4,0,0);
EXPECT_TRUE(vacant_check_up(puzzle,ret));
}

TEST(vacant_check_down,bool14){
Matrix54i puzzle = init_puzzle();
area_check_return ret;
ret.Func(15,0,0);
EXPECT_FALSE(vacant_check_down(puzzle,ret));
}

TEST(vacant_check_down,bool15){
Matrix54i puzzle = init_puzzle();
area_check_return ret;
ret.Func(-1,0,0);
EXPECT_FALSE(vacant_check_down(puzzle,ret));
}

TEST(vacant_check_down,bool16){
Matrix54i puzzle = init_puzzle();
area_check_return ret;
ret.Func(3,1,0);
EXPECT_TRUE(vacant_check_down(puzzle,ret));
}

TEST(vacant_check_down,bool17){
Matrix54i puzzle = init_puzzle();
area_check_return ret;
puzzle(2,0) = 10;
ret.Func(1,0,0);
EXPECT_TRUE(vacant_check_down(puzzle,ret));
}

TEST(move_1x1_to_left,comparison_puzzle0){
Matrix54i puzzle = init_puzzle();
area_check_return ret;
ret.Func(0,1,0);
puzzle = move_1x1_to_left(puzzle, ret);

EXPECT_EQ(puzzle(0,0), 0);
}

TEST(move_1x1_to_left,comparison_puzzle1){
Matrix54i puzzle = init_puzzle();
area_check_return ret;
ret.Func(0,3,0);
puzzle = move_1x1_to_left(puzzle, ret);

EXPECT_EQ(puzzle(0,3), 0);
}

TEST(move_1x1_to_right,comparison_puzzle2){
Matrix54i puzzle = init_puzzle();
area_check_return ret;
ret.Func(0,0,0);
puzzle = move_1x1_to_right(puzzle, ret);

EXPECT_EQ(puzzle(0,0), 0);
}


TEST(move_1x1_to_right,comparison_puzzle3){
Matrix54i puzzle = init_puzzle();
area_check_return ret;
ret.Func(0,2,0);
puzzle = move_1x1_to_right(puzzle, ret);

EXPECT_EQ(puzzle(0,2), 2);
}

TEST(move_1x1_to_up,comparison_puzzle3){
Matrix54i puzzle = init_puzzle();
area_check_return ret;
ret.Func(0,0,0);
puzzle = move_1x1_to_right(puzzle, ret);
ret.Func(1,0,0);
puzzle = move_1x1_to_up(puzzle, ret);

EXPECT_EQ(puzzle(1,0), 0);
}

TEST(move_1x1_to_up,comparison_puzzle4){
Matrix54i puzzle = init_puzzle();
area_check_return ret;
ret.Func(4,0,0);
puzzle = move_1x1_to_up(puzzle, ret);

EXPECT_EQ(puzzle(3,0),8);
EXPECT_EQ(puzzle(4,0),3);
}

TEST(move_1x1_to_down,comparison_puzzle5){
Matrix54i puzzle = init_puzzle();
area_check_return ret;
ret.Func(0,0,0);
puzzle = move_1x1_to_right(puzzle, ret);
ret.Func(0,0,0);
puzzle = move_1x1_to_down(puzzle, ret);

EXPECT_EQ(puzzle(0,0), 1);
EXPECT_EQ(puzzle(1,0), 0);
}

TEST(move_1x1_to_down,comparison_puzzle6){
Matrix54i puzzle = init_puzzle();
area_check_return ret;
ret.Func(3,0,0);
puzzle = move_1x1_to_down(puzzle, ret);

EXPECT_EQ(puzzle(3,0), 8);
EXPECT_EQ(puzzle(4,0), 3);
}

TEST(move_2x1_to_left,comparison_puz0){
Matrix54i puzzle = init_puzzle();
area_check_return ret,ret2;
ret.Func(0,1,0);
ret2.Func(1,1,0);
puzzle = move_2x1_to_left(puzzle,ret,ret2);

EXPECT_EQ(puzzle(0,0),0);
EXPECT_EQ(puzzle(1,0),0);
}

TEST(move_2x1_to_left,comparison_puz1){
Matrix54i puzzle = init_puzzle();
area_check_return ret,ret2;
ret.Func(0,3,0);
ret2.Func(1,3,0);
puzzle = move_2x1_to_left(puzzle,ret,ret2);

EXPECT_EQ(puzzle(0,3),0);
EXPECT_EQ(puzzle(1,3),0);
}


TEST(move_2x1_to_right,comparison_puz0){
Matrix54i puzzle = init_puzzle();
area_check_return ret,ret2;
ret.Func(0,0,0);
ret2.Func(1,0,0);
puzzle = move_2x1_to_right(puzzle,ret,ret2);

EXPECT_EQ(puzzle(0,0),0);
EXPECT_EQ(puzzle(1,0),0);
}


TEST(move_2x1_to_right,comparison_puz1){
Matrix54i puzzle = init_puzzle();
area_check_return ret,ret2;
ret.Func(0,2,0);
ret2.Func(1,2,0);
puzzle = move_2x1_to_right(puzzle,ret,ret2);

EXPECT_EQ(puzzle(0,2),2);
EXPECT_EQ(puzzle(1,2),2);
}


TEST(move_2x1_to_up,comparison_puz0){
Matrix54i puzzle = init_puzzle();
area_check_return ret,ret2;
ret.Func(1,0,0);
ret2.Func(2,0,0);
puzzle = move_2x1_to_up(puzzle,ret,ret2);

EXPECT_EQ(puzzle(0,0),1);
EXPECT_EQ(puzzle(1,0),3);
EXPECT_EQ(puzzle(2,0),1);
}

TEST(move_2x1_to_up,comparison_puz1){
Matrix54i puzzle = init_puzzle();
area_check_return ret,ret2;
ret.Func(3,0,0);
ret2.Func(4,0,0);
puzzle = move_2x1_to_up(puzzle,ret,ret2);

EXPECT_EQ(puzzle(2,0),3);
EXPECT_EQ(puzzle(3,0),8);
EXPECT_EQ(puzzle(4,0),3);
}

TEST(move_2x1_to_down,comparison_puz0){
Matrix54i puzzle = init_puzzle();
area_check_return ret,ret2;
ret.Func(0,0,0);
ret2.Func(1,0,0);
puzzle = move_2x1_to_down(puzzle,ret,ret2);

EXPECT_EQ(puzzle(0,0),3);
EXPECT_EQ(puzzle(1,0),1);
EXPECT_EQ(puzzle(2,0),1);
}

TEST(move_2x1_to_down,comparison_puz1){
Matrix54i puzzle = init_puzzle();
area_check_return ret,ret2;
ret.Func(2,0,0);
ret2.Func(3,0,0);
puzzle = move_2x1_to_down(puzzle,ret,ret2);

EXPECT_EQ(puzzle(2,0),8);
EXPECT_EQ(puzzle(3,0),3);
EXPECT_EQ(puzzle(4,0),3);
}


TEST(move_2x2_right,comp_puzzle0){
Matrix54i puzzle = init_puzzle();
area_check_return ret,ret2,ret3,ret4;
ret.Func(0,1,0);
ret2.Func(0,2,0);
ret3.Func(1,1,0);
ret4.Func(1,2,0);
puzzle = move_2x2_right(puzzle,ret,ret2,ret3,ret4);

EXPECT_EQ(puzzle(0,2),0);
EXPECT_EQ(puzzle(0,3),0);
EXPECT_EQ(puzzle(1,2),0);
EXPECT_EQ(puzzle(1,3),0);
}

TEST(move_2x2_right,comp_puzzle1){
Matrix54i puzzle = init_puzzle();
area_check_return ret,ret2,ret3,ret4;
ret.Func(3,1,0);
ret2.Func(3,2,0);
ret3.Func(4,1,0);
ret4.Func(4,2,0);
puzzle = move_2x2_right(puzzle,ret,ret2,ret3,ret4);

EXPECT_EQ(puzzle(3,2),6);
EXPECT_EQ(puzzle(3,3),7);
EXPECT_EQ(puzzle(4,2),10);
EXPECT_EQ(puzzle(4,3),10);
}

TEST(move_2x2_left,comp_puzzle2){
Matrix54i puzzle = init_puzzle();
area_check_return ret,ret2,ret3,ret4;
ret.Func(0,1,0);
ret2.Func(0,2,0);
ret3.Func(1,1,0);
ret4.Func(1,2,0);
puzzle = move_2x2_left(puzzle,ret,ret2,ret3,ret4);

EXPECT_EQ(puzzle(0,0),0);
EXPECT_EQ(puzzle(0,1),0);
EXPECT_EQ(puzzle(1,0),0);
EXPECT_EQ(puzzle(1,1),0);
}

TEST(move_2x2_left,comp_puzzle3){
Matrix54i puzzle = init_puzzle();
area_check_return ret,ret2,ret3,ret4;
ret.Func(3,2,7);
ret2.Func(3,3,4);
ret3.Func(4,2,10);
ret4.Func(4,3,9);
puzzle = move_2x2_left(puzzle,ret,ret2,ret3,ret4);

EXPECT_EQ(puzzle(3,1),7);
EXPECT_EQ(puzzle(3,2),4);
EXPECT_EQ(puzzle(4,1),10);
EXPECT_EQ(puzzle(4,2),9);
}

TEST(move_2x2_up,comp_puzzle4){
Matrix54i puzzle = init_puzzle();
area_check_return ret,ret2,ret3,ret4;
ret.Func(1,0,1);
ret2.Func(1,1,0);
ret3.Func(2,0,3);
ret4.Func(2,1,5);
puzzle = move_2x2_up(puzzle,ret,ret2,ret3,ret4);

EXPECT_EQ(puzzle(0,0),1);
EXPECT_EQ(puzzle(0,1),0);
EXPECT_EQ(puzzle(1,0),3);
EXPECT_EQ(puzzle(1,1),5);
}

TEST(move_2x2_up,comp_puzzle5){
Matrix54i puzzle = init_puzzle();
area_check_return ret,ret2,ret3,ret4;
ret.Func(3,0,3);
ret2.Func(3,1,6);
ret3.Func(4,0,8);
ret4.Func(4,1,10);
puzzle = move_2x2_up(puzzle,ret,ret2,ret3,ret4);

EXPECT_EQ(puzzle(2,0),3);
EXPECT_EQ(puzzle(2,1),6);
EXPECT_EQ(puzzle(3,0),8);
EXPECT_EQ(puzzle(3,1),10);
}

TEST(move_2x2_down,comp_puzzle6){
Matrix54i puzzle = init_puzzle();
area_check_return ret,ret2,ret3,ret4;
ret.Func(0,1,0);
ret2.Func(0,2,0);
ret3.Func(1,1,0);
ret4.Func(1,2,0);

puzzle = move_2x2_down(puzzle,ret,ret2,ret3,ret4);

EXPECT_EQ(puzzle(1,1),0);
EXPECT_EQ(puzzle(1,2),0);
EXPECT_EQ(puzzle(2,1),0);
EXPECT_EQ(puzzle(2,2),0);
}

TEST(move_2x2_down,comp_puzzle7){
Matrix54i puzzle = init_puzzle();
area_check_return ret,ret2,ret3,ret4;
ret.Func(2,0,3);
ret2.Func(2,1,5);
ret3.Func(3,0,3);
ret4.Func(3,1,6);
puzzle = move_2x2_down(puzzle,ret,ret2,ret3,ret4);

EXPECT_EQ(puzzle(3,0),3);
EXPECT_EQ(puzzle(3,1),5);
EXPECT_EQ(puzzle(4,0),3);
EXPECT_EQ(puzzle(4,1),6);
}

TEST(num_simple, comp_pz0){
Matrix54i puzzle = init_puzzle();
Matrix54i copy_puzzle = num_simple(puzzle,1);


EXPECT_EQ(copy_puzzle(0,0), 2);
EXPECT_EQ(copy_puzzle(1,0), 2);
EXPECT_EQ(puzzle(0,0),1);
EXPECT_EQ(puzzle(1,0),1);

}

TEST(num_simple, comp_pz1){
Matrix54i puzzle = init_puzzle();
Matrix54i copy_puzzle = num_simple(puzzle,5);


EXPECT_EQ(copy_puzzle(2,1), 5);
EXPECT_EQ(copy_puzzle(2,2), 5);
EXPECT_EQ(puzzle(2,1),5);
EXPECT_EQ(puzzle(2,2),5);

}

TEST(num_simple, comp_pz2){
Matrix54i puzzle = init_puzzle();
Matrix54i copy_puzzle = num_simple(puzzle,10);


EXPECT_EQ(copy_puzzle(4,1), 10);
EXPECT_EQ(copy_puzzle(4,2), 10);
EXPECT_EQ(puzzle(4,1),10);
EXPECT_EQ(puzzle(4,2),10);

}

TEST(num_simple, comp_pz3){
Matrix54i puzzle = init_puzzle();
Matrix54i copy_puzzle = num_simple(puzzle,6);


EXPECT_EQ(copy_puzzle(3,1), 3);
EXPECT_EQ(puzzle(3,1),6);

}

TEST(board_simple,comp_board0){
Matrix54i puzzle = init_puzzle();
Matrix54i copy_puzzle = board_simple(puzzle);

EXPECT_EQ(copy_puzzle(0,0),2);
EXPECT_EQ(copy_puzzle(1,0),2);
EXPECT_EQ(copy_puzzle(0,3),2);
EXPECT_EQ(copy_puzzle(1,3),2);
EXPECT_EQ(copy_puzzle(2,0),2);
EXPECT_EQ(copy_puzzle(2,3),2);
EXPECT_EQ(copy_puzzle(3,3),2);
EXPECT_EQ(copy_puzzle(2,1),5);
EXPECT_EQ(copy_puzzle(2,2),5);
EXPECT_EQ(copy_puzzle(3,1),3);
EXPECT_EQ(copy_puzzle(3,2),3);
EXPECT_EQ(copy_puzzle(4,0),3);
EXPECT_EQ(copy_puzzle(4,3),3);
EXPECT_EQ(copy_puzzle(4,1),10);
EXPECT_EQ(copy_puzzle(4,2),10);

}

TEST(check_rightside,bool0){
Matrix54i puzzle = init_puzzle();

EXPECT_TRUE(check_rightside(puzzle,8));
}

TEST(check_rightside,bool1){
Matrix54i puzzle = init_puzzle();
puzzle(0,3) = 10;
puzzle(1,3) = 10;
EXPECT_TRUE(check_rightside(puzzle,0));
}

TEST(check_rightside,bool2){
Matrix54i puzzle = init_puzzle();
puzzle(0,1) = 10;
puzzle(1,1) = 10;
EXPECT_TRUE(check_rightside(puzzle,1));
}

TEST(check_rightside,bool3){
Matrix54i puzzle = init_puzzle();
puzzle(2,3) = 10;
EXPECT_TRUE(check_rightside(puzzle,5));
}

TEST(check_leftside,bool4){
Matrix54i puzzle = init_puzzle();

EXPECT_TRUE(check_leftside(puzzle,9));
}

TEST(check_leftside,bool5){
Matrix54i puzzle = init_puzzle();
puzzle(0,2) = 10;
puzzle(1,2) = 10;

EXPECT_TRUE(check_leftside(puzzle,2));
}

TEST(check_leftside,bool6){
Matrix54i puzzle = init_puzzle();
puzzle(2,0) = 10;

EXPECT_TRUE(check_leftside(puzzle,5));
}

TEST(check_leftside,bool7){
Matrix54i puzzle = init_puzzle();
puzzle(0,0) = 10;
puzzle(1,0) = 10;

EXPECT_TRUE(check_leftside(puzzle,0));
}

TEST(check_upside,bool8){
Matrix54i puzzle = init_puzzle();

puzzle(3,3) = 10;

EXPECT_TRUE(check_upside(puzzle,9));
}

TEST(check_upside,bool9){
Matrix54i puzzle = init_puzzle();
puzzle(1,0) = 10;


EXPECT_TRUE(check_upside(puzzle,3));
}

TEST(check_upside,bool10){
Matrix54i puzzle = init_puzzle();
puzzle(0,1) = 10;
puzzle(0,2) = 10;
puzzle(2,1) = 0;
puzzle(2,2) = 0;

EXPECT_TRUE(check_upside(puzzle,0));
}

TEST(check_upside,bool11){
Matrix54i puzzle = init_puzzle();
puzzle(1,1) = 10;
puzzle(1,2) = 10;

EXPECT_TRUE(check_upside(puzzle,5));
}


TEST(check_downside,bool12){
Matrix54i puzzle = init_puzzle();

EXPECT_TRUE(check_downside(puzzle,6));
}


TEST(check_downside,bool13){
Matrix54i puzzle = init_puzzle();
puzzle(2,0) = 10;

EXPECT_TRUE(check_downside(puzzle,1));
}

TEST(check_downside,bool14){
Matrix54i puzzle = init_puzzle();
puzzle(3,2) = 10;
puzzle(3,1) = 10;

EXPECT_TRUE(check_downside(puzzle,5));
}

TEST(check_downside,bool15){
Matrix54i puzzle = init_puzzle();
puzzle(2,2) = 10;
puzzle(2,1) = 10;

EXPECT_TRUE(check_downside(puzzle,0));
}

TEST(right_movable_list,listval){
Matrix54i puzzle = init_puzzle();
std::vector<int> list = right_movable_list(puzzle);
EXPECT_EQ(list[0],8);
}

TEST(right_movable_list,listval1){
Matrix54i puzzle = init_puzzle();

puzzle(0,1) = 10;
puzzle(1,1) = 10;

std::vector<int> list = right_movable_list(puzzle);

EXPECT_EQ(list[0],1);
EXPECT_EQ(list[1],8);
}

TEST(right_movable_list,listval2){
Matrix54i puzzle = init_puzzle();

puzzle(3,2) = 10;
puzzle(4,2) = 7;


std::vector<int> list = right_movable_list(puzzle);

EXPECT_EQ(list[0],6);

}


TEST(right_movable_list,listval3){
Matrix54i puzzle = init_puzzle();

puzzle(0,3) = 10;
puzzle(1,3) = 10;

std::vector<int> list = right_movable_list(puzzle);

EXPECT_EQ(list[0],0);
}

TEST(left_movable_list,listval4){
Matrix54i puzzle = init_puzzle();

puzzle(0,2) = 10;
puzzle(1,2) = 10;

std::vector<int> list = left_movable_list(puzzle);

EXPECT_EQ(list[0],2);
EXPECT_EQ(list[1],9);
}


TEST(left_movable_list,listva5){
Matrix54i puzzle = init_puzzle();

puzzle(0,0) = 10;
puzzle(1,0) = 10;
puzzle(2,0) = 1;
puzzle(3,1) = 6;
puzzle(4,1) = 3;
puzzle(4,2) = 3;


std::vector<int> list = left_movable_list(puzzle);

EXPECT_EQ(list[0],0);
}


TEST(left_movable_list,listval6){
Matrix54i puzzle = init_puzzle();

puzzle(2,0) = 10;


std::vector<int> list = left_movable_list(puzzle);

EXPECT_EQ(list[0],5);
EXPECT_EQ(list[1],9);
}


TEST(up_movable_list,listval7){
Matrix54i puzzle = init_puzzle();

puzzle(2,1) = 10;

std::vector<int> list = up_movable_list(puzzle);

EXPECT_EQ(list[0],6);

}

TEST(up_movable_list,listval8){
Matrix54i puzzle = init_puzzle();
puzzle(0,1) = 10;
puzzle(0,2) = 10;
puzzle(2,1) = 0;
puzzle(2,2) = 0;


std::vector<int> list = up_movable_list(puzzle);

EXPECT_EQ(list[0],0);

}

TEST(up_movable_list,listval9){
Matrix54i puzzle = init_puzzle();
puzzle(1,0) = 10;

std::vector<int> list = up_movable_list(puzzle);

EXPECT_EQ(list[0],3);

}

TEST(up_movable_list,listval10){
Matrix54i puzzle = init_puzzle();
puzzle(1,1) = 10;
puzzle(1,2) = 10;



std::vector<int> list = up_movable_list(puzzle);

EXPECT_EQ(list[0],5);

}

TEST(down_movable_list,listval11){
Matrix54i puzzle = init_puzzle();

std::vector<int> list = down_movable_list(puzzle);

EXPECT_EQ(list[0],6);
EXPECT_EQ(list[1],7);

}

TEST(down_movable_list,listval12){
Matrix54i puzzle = init_puzzle();
puzzle(2,0) = 10;

std::vector<int> list = down_movable_list(puzzle);
EXPECT_EQ(list[0],1);
EXPECT_EQ(list[1],6);
EXPECT_EQ(list[2],7);

}

TEST(down_movable_list,listval13){
Matrix54i puzzle = init_puzzle();
puzzle(3,1) = 10;
puzzle(3,2) = 10;
puzzle(4,1) = 6;
puzzle(4,2) = 7;
std::vector<int> list = down_movable_list(puzzle);
EXPECT_EQ(list[0],5);
}

TEST(down_movable_list,listval14){
Matrix54i puzzle = init_puzzle();
puzzle(4,1) = 5;
puzzle(4,2) = 5;
puzzle(2,1) = 10;
puzzle(2,2) = 10;


std::vector<int> list = down_movable_list(puzzle);
EXPECT_EQ(list[0],0);

}

TEST(movepuzzle_right,compboard0){
Matrix54i puzzle = init_puzzle();

puzzle = movepuzzle_right(puzzle,0);

EXPECT_EQ(puzzle(0,2),0);
EXPECT_EQ(puzzle(1,2),0);
EXPECT_EQ(puzzle(0,3),0);
EXPECT_EQ(puzzle(1,3),0);
}

TEST(movepuzzle_right,compboard1){
Matrix54i puzzle = init_puzzle();

puzzle = movepuzzle_right(puzzle,1);

EXPECT_EQ(puzzle(0,0),0);
EXPECT_EQ(puzzle(1,0),0);
EXPECT_EQ(puzzle(0,1),1);
EXPECT_EQ(puzzle(1,1),1);
}

TEST(movepuzzle_right,compboard2){
Matrix54i puzzle = init_puzzle();

puzzle = movepuzzle_right(puzzle,5);

EXPECT_EQ(puzzle(2,3),5);
EXPECT_EQ(puzzle(2,2),5);
EXPECT_EQ(puzzle(2,1),4);
}

TEST(movepuzzle_right,compboard3){
Matrix54i puzzle = init_puzzle();

puzzle = movepuzzle_right(puzzle,8);

EXPECT_EQ(puzzle(4,0),10);
EXPECT_EQ(puzzle(4,1),8);

}

TEST(MovePuzzle_Left,CompBoard0){
Matrix54i puzzle = init_puzzle();

puzzle = movepuzzle_left(puzzle,0);

EXPECT_EQ(puzzle(0,0),0);
EXPECT_EQ(puzzle(1,0),0);
EXPECT_EQ(puzzle(1,1),0);
EXPECT_EQ(puzzle(1,1),0);
EXPECT_EQ(puzzle(0,2),1);
EXPECT_EQ(puzzle(1,2),1);
}

TEST(MovePuzzle_Left,CompBoard1){
Matrix54i puzzle = init_puzzle();

puzzle = movepuzzle_left(puzzle,2);

EXPECT_EQ(puzzle(0,3),0);
EXPECT_EQ(puzzle(1,3),0);
EXPECT_EQ(puzzle(0,2),2);
EXPECT_EQ(puzzle(1,2),2);

}


TEST(MovePuzzle_Left,CompBoard2){
Matrix54i puzzle = init_puzzle();

puzzle = movepuzzle_left(puzzle,5);

EXPECT_EQ(puzzle(2,0),5);
EXPECT_EQ(puzzle(2,1),5);
EXPECT_EQ(puzzle(2,2),3);
}

TEST(MovePuzzle_Left,CompBoard3){
Matrix54i puzzle = init_puzzle();

puzzle = movepuzzle_left(puzzle,9);

EXPECT_EQ(puzzle(4,2),9);
EXPECT_EQ(puzzle(4,3),10);
}

TEST(MovePuzzle_up,CompBoard1){
Matrix54i puzzle = init_puzzle();
puzzle(0,1) = 5;
puzzle(0,2) = 5;
puzzle(2,1) = 0;
puzzle(2,2) = 0;

puzzle = movepuzzle_up(puzzle,0);

EXPECT_EQ(puzzle(0,1),0);
EXPECT_EQ(puzzle(0,2),0);
EXPECT_EQ(puzzle(1,1),0);
EXPECT_EQ(puzzle(1,2),0);
}

TEST(MovePuzzle_up,CompBoard2){
Matrix54i puzzle = init_puzzle();

puzzle = movepuzzle_up(puzzle,3);

EXPECT_EQ(puzzle(1,0),3);
EXPECT_EQ(puzzle(2,0),3);
EXPECT_EQ(puzzle(3,0),1);
EXPECT_EQ(puzzle(0,0),1);
}


TEST(MovePuzzle_up,CompBoard3){
Matrix54i puzzle = init_puzzle();

puzzle = movepuzzle_up(puzzle,5);

EXPECT_EQ(puzzle(1,1),5);
EXPECT_EQ(puzzle(1,2),5);
EXPECT_EQ(puzzle(2,1),0);
EXPECT_EQ(puzzle(2,2),0);
}

TEST(MovePuzzle_up,CompBoard4){
Matrix54i puzzle = init_puzzle();

puzzle = movepuzzle_up(puzzle,9);

EXPECT_EQ(puzzle(3,3),9);
EXPECT_EQ(puzzle(4,3),4);
}

TEST(MovePuzzle_down,CompBoard1){
Matrix54i puzzle = init_puzzle();

puzzle = movepuzzle_down(puzzle,0);

EXPECT_EQ(puzzle(2,1),0);
EXPECT_EQ(puzzle(2,2),0);
EXPECT_EQ(puzzle(1,1),0);
EXPECT_EQ(puzzle(1,2),0);
EXPECT_EQ(puzzle(0,1),5);
EXPECT_EQ(puzzle(0,2),5);
}

TEST(MovePuzzle_down,CompBoard2){
Matrix54i puzzle = init_puzzle();

puzzle = movepuzzle_down(puzzle,1);

EXPECT_EQ(puzzle(1,0),1);
EXPECT_EQ(puzzle(2,0),1);
EXPECT_EQ(puzzle(0,0),3);
}

TEST(MovePuzzle_down,CompBoard3){
Matrix54i puzzle = init_puzzle();

puzzle = movepuzzle_down(puzzle,5);

EXPECT_EQ(puzzle(3,1),5);
EXPECT_EQ(puzzle(3,2),5);
EXPECT_EQ(puzzle(2,1),6);
EXPECT_EQ(puzzle(2,2),7);
}

TEST(MovePuzzle_down,CompBoard4){
Matrix54i puzzle = init_puzzle();

puzzle = movepuzzle_down(puzzle,6);

EXPECT_EQ(puzzle(4,1),6);
EXPECT_EQ(puzzle(3,1),10);

}

TEST(to_hashable,string){
Matrix54i puzzle = init_puzzle();
std::string str = "1002100235543674810109";
std::string hash = to_hashable(puzzle);
EXPECT_EQ(hash,str);
}


TEST(to_hashable,string0){
Matrix54i puzzle = init_puzzle();
puzzle = board_simple(puzzle);
std::string str = "2002200225522332310103";
std::string hash = to_hashable(puzzle);
EXPECT_EQ(hash,str);
}

TEST(exist,vectorstring){
std::vector<std::string>  puzzle_state;
puzzle_state.push_back("321");
puzzle_state.push_back("123");
puzzle_state.push_back("213");
puzzle_state.push_back("111");


std::string str = "123";
EXPECT_TRUE(exist(str,puzzle_state));
}

TEST(exist,vectorstring2){
std::vector<std::string>  puzzle_state;
puzzle_state.push_back("321");
puzzle_state.push_back("123");
puzzle_state.push_back("213");
puzzle_state.push_back("111");
std::string str = "355";
EXPECT_FALSE(exist(str,puzzle_state));
}

}
