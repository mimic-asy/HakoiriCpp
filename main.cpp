
#include <iostream>
#include <cstdio>
#include <cstring>
#include <Eigen/Dense>
#include <vector>


#include <iostream>
#include <cstdio>
#include <cstring>
#include <Eigen/Dense>
#include <vector>

Eigen::MatrixXi swap(Eigen::MatrixXi &puzzle,int y1,int x1,int y2,int x2){
    int stock = puzzle(y1,x1);
    std::cout << "y1,x1 ="<< puzzle(y1,x1) << std::endl;
    std::cout << "y2,x2 ="<< puzzle(y2,x2) << std::endl;
    std::cout << "stock ="<< stock << std::endl;
    puzzle(y1,x1) = puzzle(y2,x2);
    std::cout <<"y1,x1 ="<< puzzle(y1,x1) << std::endl;
    std::cout << "y2,x2 ="<< puzzle(y2,x2) << std::endl;
    std::cout << "stock ="<< stock << std::endl;
    puzzle(y2,x2) = stock;
    std::cout <<"y1,x1 ="<< puzzle(y1,x1) << std::endl;
    std::cout << "y2,x2 ="<< puzzle(y2,x2) << std::endl;
    std::cout << "stock ="<< stock << std::endl;

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

class area_check_return {
public:
    int val;
    int y;
    int x;
};


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


int main() {
    Eigen::MatrixXi puzzle = init_puzzle();
    swap(puzzle, 1,1,2,1);
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