#include <iostream>
#include <cstdio>
#include <cstring>
#include <Eigen/Dense>
#include <vector>
#include "method.h"


//test OK
void swap(Eigen::MatrixXi &puzzle,int y1,int x1,int y2,int x2){
    int stock = puzzle(y1,x1);
    puzzle(y1,x1) = puzzle(y2,x2);
    puzzle(y2,x2) = stock;
}

Eigen::MatrixXi init_puzzle(){
    Eigen::MatrixXi puzzle = Eigen::MatrixXi::Zero(5,4);
    puzzle(0,0) = 1;
    puzzle(1,0) = 1;
    puzzle(0,3) = 2;
    puzzle(1,3) = 2;
    puzzle(2,0) = 3;
    puzzle(3,0) = 3;
    puzzle(2,3) = 4;
    puzzle(3,3) = 4;
    puzzle(2,1) = 5;
    puzzle(2,2) = 5;
    puzzle(3,1) = 6;
    puzzle(3,2) = 7;
    puzzle(4,0) = 8;
    puzzle(4,3) = 9;
    puzzle(4,1) = 10;
    puzzle(4,2) = 10;

    return puzzle;
}

void area_check_return::Func(int yv, int xv, int v){
    y = yv;
    x = xv;
    val = v;
}

//TestOK
//Matrixの中にあるTargetValueの座標を返す
std::vector<area_check_return> area_check(Eigen::MatrixXi puzzle, int targetValue) {
    //return用の変数を宣言
    area_check_return ret;

    //return用のlistを宣言
    std::vector<area_check_return> ret_list;

    //Matrixの行数を取得
    int rows = puzzle.rows();
    //Matrixの列数を取得
    int cols = puzzle.cols();

    //Matrixの中身を走査
    for (int i = 0; i < rows; i++){
        for (int c = 0; c < cols; c++){
            //TargetValueとMatrixの中身が一致した場合
            if (puzzle(i,c) == targetValue){
                //return用の変数に座標を格納
                ret.y = i;
                ret.x = c;
                ret.val = puzzle(i,c);
                ret_list.push_back(ret);
            }
        }
    }
    //return
    return ret_list;

}

//testOK
//配列の外側に出ていかないかを確認する
bool inrange_check_right(class area_check_return ret){
    if (ret.x > -1 && ret.x < 3){
        return true;
    }else{
        return false;
    }
}

bool inrange_check_left(class area_check_return ret){
    if (ret.x > 0 && ret.x < 4){
        return true;
    }else{
        return false;
    }
}

bool inrange_check_up(class area_check_return ret){
    if (ret.y < 5 &&ret.y > 0){
        return true;
    }else{
        return false;
    }
}

bool inrange_check_down(class area_check_return ret){
    if(ret.y > -1 && ret.y < 4){
        return true;
    }else{
        return false;
    }
}


//testOK
bool vacant_check_right(Eigen::MatrixXi puzzle, class area_check_return ret){
    int x = ret.x;
    x = x+1;
    if(x > -1 && x < 4){
        if (puzzle(ret.y, x) == 10){
            return true;
        }else{
            return false;
        }
    }else{
        return false;
    }
}

bool vacant_check_left(Eigen::MatrixXi puzzle, class area_check_return ret){
    int x = ret.x;
    x = x-1;
    if (x > -1 && x < 4){
        if (puzzle(ret.y, x) == 10){
            return true;
        }else{
            return false;
        }
    }else{
        return false;
    }
}

bool vacant_check_up(Eigen::MatrixXi puzzle, class area_check_return ret){
    int y = ret.y;
    y = y-1;
    if (ret.y < 5 &&ret.y > -1){

        if (puzzle(y, ret.x) == 10){
            return true;
        }else{
            return false;
        }
    }else{
        return false;
    }
}

bool vacant_check_down(Eigen::MatrixXi puzzle, class area_check_return ret){
    int y = ret.y;
    y = y +1;
    if(ret.y > -1 && ret.y < 5){

        if (puzzle(y, ret.x) == 10){
            return true;
        }else{
            return false;
        }
    }else{
        return false;
    }
}


bool range_and_vacantcheck_right(Eigen::MatrixXi puzzle, class area_check_return ret){
    if (inrange_check_right(ret) && vacant_check_right(puzzle,ret)){
        return true;
    }else{
        return false;
    }
}

bool range_and_vacantcheck_left(Eigen::MatrixXi puzzle, class area_check_return ret){
 if (inrange_check_left(ret) && vacant_check_left(puzzle,ret)){
        return true;
    }else{
        return false;
    }
}

bool range_and_vacantcheck_up(Eigen::MatrixXi puzzle, class area_check_return ret){
 if (inrange_check_up(ret) && vacant_check_up(puzzle,ret)){
        return true;
    }else{
        return false;
    }
}


bool range_and_vacantcheck_down(Eigen::MatrixXi puzzle, class area_check_return ret){
 if (inrange_check_down(ret) && vacant_check_down(puzzle,ret)){
        return true;
    }else{
        return false;
    }
}


Eigen::MatrixXi move_1x1_to_right(Eigen::MatrixXi &puzzle, class area_check_return &ret){
    int xt = ret.x +1;
    swap(puzzle, ret.y, ret.x, ret.y, xt);
    return puzzle;
}

Eigen::MatrixXi move_1x1_to_left(Eigen::MatrixXi &puzzle, class area_check_return &ret){
    int xt = ret.x -1;
    swap(puzzle, ret.y, ret.x, ret.y, xt);
    return puzzle;
}

Eigen::MatrixXi move_1x1_to_up(Eigen::MatrixXi &puzzle, class area_check_return &ret){
    int yt = ret.y -1;
    swap(puzzle, ret.y, ret.x, yt, ret.x);
    return puzzle;
}

Eigen::MatrixXi move_1x1_to_down(Eigen::MatrixXi &puzzle, class area_check_return &ret){
    int yt = ret.y +1;
    swap(puzzle, ret.y, ret.x, yt, ret.x);
    return puzzle;
}

Eigen::MatrixXi move_2x1_to_left(Eigen::MatrixXi &puzzle, class area_check_return &ret, class area_check_return &ret2){
    int xt = ret.x -1;
    int xtt = ret2.x -1;
    swap(puzzle, ret.y, ret.x, ret.y, xt);
    swap(puzzle, ret2.y, ret2.x, ret2.y,xtt);
    return puzzle;
}

Eigen::MatrixXi move_2x1_to_right(Eigen::MatrixXi &puzzle, class area_check_return &ret, class area_check_return &ret2){
    int xt = ret.x +1;
    int xtt = ret2.x +1;
    swap(puzzle, ret2.y, ret2.x, ret2.y,xtt);
    swap(puzzle, ret.y, ret.x, ret.y, xt);
    return puzzle;
}

Eigen::MatrixXi move_2x1_to_up(Eigen::MatrixXi &puzzle, class area_check_return &ret, class area_check_return &ret2){
    int yt = ret.y -1;
    int ytt = ret2.y -1;
    swap(puzzle, ret.y, ret.x, yt, ret.x);
    swap(puzzle, ret2.y, ret2.x, ytt, ret2.x);
    return puzzle;
}

Eigen::MatrixXi move_2x1_to_down(Eigen::MatrixXi &puzzle, class area_check_return &ret, class area_check_return &ret2){
    int yt = ret.y +1;
    int ytt = ret2.y +1;
    swap(puzzle, ret2.y, ret2.x, ytt, ret2.x);
    swap(puzzle, ret.y, ret.x, yt, ret.x);
    return puzzle;
}

Eigen::MatrixXi move_2x2_right(Eigen::MatrixXi &puzzle, class area_check_return &ret,
                                class area_check_return &ret2, class area_check_return &ret3,
                                class area_check_return &ret4){
    swap(puzzle, ret4.y, ret4.x, ret4.y, ret4.x+1);
    swap(puzzle, ret2.y, ret2.x, ret2.y, ret2.x+1);
    swap(puzzle, ret.y, ret.x, ret.y, ret.x+1);
    swap(puzzle, ret3.y, ret3.x, ret3.y, ret3.x+1);

    return puzzle;

}

Eigen::MatrixXi move_2x2_left(Eigen::MatrixXi &puzzle, class area_check_return &ret,
                                class area_check_return &ret2, class area_check_return &ret3,
                                class area_check_return &ret4){

    swap(puzzle, ret.y, ret.x, ret.y, ret.x-1);
    swap(puzzle, ret3.y, ret3.x, ret3.y, ret3.x-1);
    swap(puzzle, ret4.y, ret4.x, ret4.y, ret4.x-1);
    swap(puzzle, ret2.y, ret2.x, ret2.y, ret2.x-1);


    return puzzle;

}


Eigen::MatrixXi move_2x2_up(Eigen::MatrixXi &puzzle, class area_check_return &ret,
                                class area_check_return &ret2, class area_check_return &ret3,
                                class area_check_return &ret4){

    swap(puzzle, ret.y, ret.x, ret.y-1, ret.x);
    swap(puzzle, ret2.y, ret2.x, ret2.y-1, ret2.x);
    swap(puzzle, ret3.y, ret3.x, ret3.y-1, ret3.x);
    swap(puzzle, ret4.y, ret4.x, ret4.y-1, ret4.x);



    return puzzle;

}

Eigen::MatrixXi move_2x2_down(Eigen::MatrixXi &puzzle, class area_check_return &ret,
                                class area_check_return &ret2, class area_check_return &ret3,
                                class area_check_return &ret4){

    swap(puzzle, ret3.y, ret3.x, ret3.y+1, ret3.x);
    swap(puzzle, ret4.y, ret4.x, ret4.y+1, ret4.x);
    swap(puzzle, ret.y, ret.x, ret.y+1, ret.x);
    swap(puzzle, ret2.y, ret2.x, ret2.y+1, ret2.x);


    return puzzle;

}



bool clear(Eigen::MatrixXi puzzle){
    if(puzzle(4,1) == 0 && puzzle(4,2) == 0){
        return true;
    }else{
        return false;
    }
}



Eigen::MatrixXi num_simple(Eigen::MatrixXi puzzle, int i){
    Eigen::MatrixXi copy_puzzle = puzzle;
    std::vector<area_check_return> num = area_check(puzzle,i);
     for (const auto& item : num) {
        if (item.val > 0 && item.val <5){
            copy_puzzle(item.y, item.x) = 2;
        }else if(item.val > 5 && item.val < 10){
            copy_puzzle(item.y, item.x ) = 3;
        }else{
            continue;
        }
    }
    return copy_puzzle;
}


Eigen::MatrixXi board_simple(Eigen::MatrixXi &puzzle){
    for (int i = 1; i < 10; i++ ){
        puzzle = num_simple(puzzle,i);
    }
    return puzzle;
}


bool check_rightside(Eigen::MatrixXi puzzle, int checkval){
    std::vector<area_check_return> num = area_check(puzzle,checkval);

    if (checkval > 0 && checkval < 5 ){
        for (const auto& item : num){
            if(range_and_vacantcheck_right(puzzle,item) == false){
                return false;
            }
            return true;
        }

    }else if(checkval > 5 && checkval <10 ){
        return range_and_vacantcheck_right(puzzle,num[0]);

    }else if(checkval == 5){
        return range_and_vacantcheck_right(puzzle,num[1]);

    }else if(checkval == 0){
        if(range_and_vacantcheck_right(puzzle,num[1]) && range_and_vacantcheck_right(puzzle,num[3])){
            return true;
        }
        return false;

    }else{
        return false;
    }

    return false;
}

bool check_leftside(Eigen::MatrixXi puzzle, int checkval){
    std::vector<area_check_return> num = area_check(puzzle,checkval);

    if(checkval > 0 && checkval < 5){
        for (const auto& item : num){
            if(range_and_vacantcheck_left(puzzle,item) == false){
                return false;
            }
        }
        return true;

    }else if(checkval > 4 && checkval < 10){
        return range_and_vacantcheck_left(puzzle,num[0]);

    }else if(checkval == 0){
        if(range_and_vacantcheck_left(puzzle,num[0]) && range_and_vacantcheck_left(puzzle,num[2])){
            return true;

        }
        return false;

    }
    return false;
}

bool check_upside(Eigen::MatrixXi puzzle, int checkval){
    std::vector<area_check_return> num = area_check(puzzle,checkval);

    if(checkval == 5){
        for (const auto& item : num){
            if(range_and_vacantcheck_up(puzzle,item) == false){
                return false;
            }
        }
        return true;

    }else if(checkval > 0 && checkval < 10 && checkval != 5){
        return range_and_vacantcheck_up(puzzle,num[0]);

    }else if(checkval == 0){
        if(range_and_vacantcheck_up(puzzle,num[0]) && range_and_vacantcheck_up(puzzle,num[1])){
            return true;

        }
        return false;

    }
    return false;
}

bool check_downside(Eigen::MatrixXi puzzle, int checkval){
    std::vector<area_check_return> num = area_check(puzzle,checkval);

    if(checkval == 5){
        for (const auto& item : num){
            if(range_and_vacantcheck_down(puzzle,item) == false){
                return false;
            }
        }
        return true;

    }else if(checkval > 0 && checkval < 5){
        return range_and_vacantcheck_down(puzzle,num[1]);
    }else if(checkval > 5 && checkval < 10){
        return range_and_vacantcheck_down(puzzle,num[0]);

    }else if(checkval == 0){
        if(range_and_vacantcheck_down(puzzle,num[2]) && range_and_vacantcheck_down(puzzle,num[3])){
            return true;

        }
        return false;

    }
    return false;
}

//動かせる数字をリストにする

std::vector<int> right_movable_list(Eigen::MatrixXi puzzle){
    std::vector<int> stack_moveright;
    for(int i = 0; i < 10 ; i++){
        if(check_rightside(puzzle,i)){
            stack_moveright.push_back(i);
        }
    }
    return stack_moveright;
}

std::vector<int> left_movable_list(Eigen::MatrixXi puzzle){
    std::vector<int> stack_moveleft;
    for(int i = 0; i < 10 ; i++){
        if(check_leftside(puzzle,i)){
            stack_moveleft.push_back(i);
        }
    }
    return stack_moveleft;
}

std::vector<int> up_movable_list(Eigen::MatrixXi puzzle){
    std::vector<int> stack_moveup;
    for(int i = 0; i < 10 ; i++){
        if(check_upside(puzzle,i)){
            stack_moveup.push_back(i);
        }
    }
    return stack_moveup;
}

std::vector<int> down_movable_list(Eigen::MatrixXi puzzle){
    std::vector<int> stack_movedown;
    for(int i = 0; i < 10 ; i++){
        if(check_downside(puzzle,i)){
            stack_movedown.push_back(i);
        }
    }
    return stack_movedown;
}

//動かす

Eigen::MatrixXi movepuzzle_right(Eigen::MatrixXi &puzzle,int val){
    if(val == 0){
        std::vector<area_check_return> num = area_check(puzzle,0);
        Eigen::MatrixXi ret_puzzle = move_2x2_right(puzzle,num[0],num[1],num[2],num[3]);
        return ret_puzzle;

    }else if(val > 0 && val < 6){
        std::vector<area_check_return> num = area_check(puzzle,val);
        Eigen::MatrixXi ret_puzzle = move_2x1_to_right(puzzle,num[0],num[1]);
        return ret_puzzle;

    }else{
        std::vector<area_check_return> num = area_check(puzzle,val);
        Eigen::MatrixXi ret_puzzle = move_1x1_to_right(puzzle,num[0]);
        return ret_puzzle;

    }

}

Eigen::MatrixXi movepuzzle_left(Eigen::MatrixXi &puzzle,int val){
    if(val == 0){
        std::vector<area_check_return> num = area_check(puzzle,0);
        Eigen::MatrixXi ret_puzzle = move_2x2_left(puzzle,num[0],num[1],num[2],num[3]);
        return ret_puzzle;

    }else if(val > 0 && val < 6){
        std::vector<area_check_return> num = area_check(puzzle,val);
        Eigen::MatrixXi ret_puzzle = move_2x1_to_left(puzzle,num[0],num[1]);
        return ret_puzzle;

    }else{
        std::vector<area_check_return> num = area_check(puzzle,val);
        Eigen::MatrixXi ret_puzzle = move_1x1_to_left(puzzle,num[0]);
        return ret_puzzle;

    }

}

Eigen::MatrixXi movepuzzle_up(Eigen::MatrixXi &puzzle,int val){
    if(val == 0){
        std::vector<area_check_return> num = area_check(puzzle,0);
        Eigen::MatrixXi ret_puzzle = move_2x2_up(puzzle,num[0],num[1],num[2],num[3]);
        return ret_puzzle;

    }else if(val > 0 && val < 6){
        std::vector<area_check_return> num = area_check(puzzle,val);
        Eigen::MatrixXi ret_puzzle = move_2x1_to_up(puzzle,num[0],num[1]);
        return ret_puzzle;

    }else{
        std::vector<area_check_return> num = area_check(puzzle,val);

        Eigen::MatrixXi ret_puzzle = move_1x1_to_up(puzzle,num[0]);
        return ret_puzzle;

    }

}

Eigen::MatrixXi movepuzzle_down(Eigen::MatrixXi &puzzle,int val){
    if(val == 0){
        std::vector<area_check_return> num = area_check(puzzle,0);
        Eigen::MatrixXi ret_puzzle = move_2x2_down(puzzle,num[0],num[1],num[2],num[3]);
        return ret_puzzle;

    }else if(val > 0 && val < 6){
        std::vector<area_check_return> num = area_check(puzzle,val);
        Eigen::MatrixXi ret_puzzle = move_2x1_to_down(puzzle,num[0],num[1]);
        return ret_puzzle;

    }else{
        std::vector<area_check_return> num = area_check(puzzle,val);
        Eigen::MatrixXi ret_puzzle = move_1x1_to_down(puzzle,num[0]);
        return ret_puzzle;

    }

}







