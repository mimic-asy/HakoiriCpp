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

//mada

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

