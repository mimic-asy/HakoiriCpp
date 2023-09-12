#include <iostream>
#include <cstdio>
#include <cstring>
#include <Eigen/Dense>
#include <chrono>

Eigen::MatrixXi baseboard(){
    Eigen::MatrixXi board = Eigen::MatrixXi::Zero(5,4);
    board(0,0) = 1;
    board(1,0) = 1;
    board(0,3) = 2;
    board(1,3) = 2;
    board(2,0) = 3;
    board(3,0) = 3;
    board(2,3) = 4;
    board(3,3) = 4;
    board(2,1) = 5;
    board(2,2) = 5;
    board(3,1) = 6;
    board(3,2) = 7;
    board(4,0) = 8;
    board(4,3) = 9;
    board(4,1) = 10;
    board(4,2) = 10;

    std::cout << board << std::endl;

    return board;
}




inline void swap1block(Eigen::MatrixXi board,int y1,int x1,int y2,int x2){
    int stock = board(y1,x1);
    board(y1,x1) = board(y2,x2);
    board(y2,x2) = stock;
}

inline void swap2block(Eigen::MatrixXi board,int y1,int x1,int y2,int x2,
                       int y3,int x3,int y4,int x4){
    int stock = board(y1,x1);
    board(y1,x1) = board(y3,x3);
    board(y3,x3) = stock;
    stock = board(y2,x2);
    board(y2,x2) = board(y4,x4);
    board(y4,x4) = stock;
}

inline void swap4block(Eigen::MatrixXi board,
                       int y1,int x1,int y2,int x2,
                       int y3,int x3,int y4,int x4,
                       int y5,int x5,int y6,int x6,
                       int y7,int x7,int y8,int x8){
    int stock = board(y1,x1);
    board(y1,x1) = board(y5,x5);
    board(y5,x5) = stock;
    stock = board(y2,x2);
    board(y2,x2) = board(y6,x6);
    board(y6,x6) = stock;
    stock = board(y3,x3);
    board(y3,x3) = board(y7,x7);
    board(y7,x7) = stock;
    stock = board(y4,x4);
    board(y4,x4) = board(y8,x8);
    board(y8,x8) = stock;
}


int main(){

    Eigen::MatrixXi board = baseboard();
    using namespace std;
    chrono::system_clock::time_point start, end;

    int N = 10000000;

    start = chrono::system_clock::now();
    for (int i = 0; i < N; ++i){
        swap1block(board,0,0,0,1);
        swap1block(board,1,0,1,1);
    }
    end = chrono::system_clock::now();
    double time = static_cast<double>(chrono::duration_cast<chrono::nanoseconds>(end - start).count());
    printf("swap1block_time %.0lf[ns]\n", time);

    start = chrono::system_clock::now();
    for (int i = 0; i < N; ++i){
        swap2block(board,0,0,0,1,1,0,1,1);
    }
    end = chrono::system_clock::now();
    double time2 = static_cast<double>(chrono::duration_cast<chrono::nanoseconds>(end - start).count());
    printf("swap2block_time %.0lf[ns]\n", time2);
    return 0;
}

