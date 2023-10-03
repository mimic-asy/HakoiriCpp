#include <iostream>
#include <cstdio>
#include <cstring>
#include <Eigen/Dense>
#include <vector>
#include <queue>
#include <unordered_map>

#include "method.h"


//test OK
void swap(Matrix54i &puzzle,int y1,int x1,int y2,int x2){
    int stock = puzzle(y1,x1);
    puzzle(y1,x1) = puzzle(y2,x2);
    puzzle(y2,x2) = stock;
}

Matrix54i init_puzzle(){
    Matrix54i puzzle = Matrix54i::Zero(5,4);
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
std::vector<area_check_return> area_check(Matrix54i puzzle, int targetValue) {
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
            if (puzzle(i, c) == targetValue){
                // 新しい area_check_return オブジェクトを生成し、座標を格納して ret_list に追加
                area_check_return ret;
                ret.y = i;
                ret.x = c;
                ret.val = targetValue;
                ret_list.push_back(ret);
            }
        }
    }
    //return
    return ret_list;
}


//testOK
//配列の外側に出ていかないかを確認する
bool inrange_check_right(class area_check_return &ret) {
    return ret.x >= 0 && ret.x <= 2;
}

bool inrange_check_left(class area_check_return &ret){
    if (ret.x > 0 && ret.x < 4){
        return true;
    }else{
        return false;
    }
}

bool inrange_check_up(class area_check_return &ret){
    if (ret.y < 5 &&ret.y > 0){
        return true;
    }else{
        return false;
    }
}

bool inrange_check_down(class area_check_return &ret){
    if(ret.y > -1 && ret.y < 4){
        return true;
    }else{
        return false;
    }
}


//testOK
bool vacant_check_right(Matrix54i puzzle, class area_check_return &ret){
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

bool vacant_check_left(Matrix54i puzzle, class area_check_return &ret){
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

bool vacant_check_up(Matrix54i puzzle, class area_check_return &ret){
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

bool vacant_check_down(Matrix54i puzzle, class area_check_return &ret){
    int y = ret.y;
    y = y+1;
    if (ret.y < 4 &&ret.y > -1){

        if (puzzle(y, ret.x) == 10){
            return true;
        }else{
            return false;
        }
    }else{
        return false;
    }
}


bool range_and_vacantcheck_right(Matrix54i puzzle, class area_check_return ret){
    if (inrange_check_right(ret) && vacant_check_right(puzzle,ret)){
        return true;
    }else{
        return false;
    }
}

bool range_and_vacantcheck_left(Matrix54i puzzle, class area_check_return ret){
 if (inrange_check_left(ret) && vacant_check_left(puzzle,ret)){
        return true;
    }else{
        return false;
    }
}

bool range_and_vacantcheck_up(Matrix54i puzzle, class area_check_return ret){
 if (inrange_check_up(ret) && vacant_check_up(puzzle,ret)){
        return true;
    }else{
        return false;
    }
}


bool range_and_vacantcheck_down(Matrix54i puzzle, class area_check_return ret){
 if (inrange_check_down(ret) && vacant_check_down(puzzle,ret)){
        return true;
    }else{
        return false;
    }
}


Matrix54i move_1x1_to_right(Matrix54i &puzzle, class area_check_return &ret){
    int xt = ret.x +1;
    swap(puzzle, ret.y, ret.x, ret.y, xt);
    return puzzle;
}

Matrix54i move_1x1_to_left(Matrix54i &puzzle, class area_check_return &ret){
    int xt = ret.x -1;
    swap(puzzle, ret.y, ret.x, ret.y, xt);
    return puzzle;
}

Matrix54i move_1x1_to_up(Matrix54i &puzzle, class area_check_return &ret){
    int yt = ret.y -1;
    swap(puzzle, ret.y, ret.x, yt, ret.x);
    return puzzle;
}

Matrix54i move_1x1_to_down(Matrix54i &puzzle, class area_check_return &ret){
    int yt = ret.y +1;
    swap(puzzle, ret.y, ret.x, yt, ret.x);
    return puzzle;
}

Matrix54i move_2x1_to_left(Matrix54i &puzzle, class area_check_return &ret, class area_check_return &ret2){
    int xt = ret.x -1;
    int xtt = ret2.x -1;
    swap(puzzle, ret.y, ret.x, ret.y, xt);
    swap(puzzle, ret2.y, ret2.x, ret2.y,xtt);
    return puzzle;
}

Matrix54i move_2x1_to_right(Matrix54i &puzzle, class area_check_return &ret, class area_check_return &ret2){
    int xt = ret.x +1;
    int xtt = ret2.x +1;
    swap(puzzle, ret2.y, ret2.x, ret2.y,xtt);
    swap(puzzle, ret.y, ret.x, ret.y, xt);
    return puzzle;
}

Matrix54i move_2x1_to_up(Matrix54i &puzzle, class area_check_return &ret, class area_check_return &ret2){
    int yt = ret.y -1;
    int ytt = ret2.y -1;
    swap(puzzle, ret.y, ret.x, yt, ret.x);
    swap(puzzle, ret2.y, ret2.x, ytt, ret2.x);
    return puzzle;
}

Matrix54i move_2x1_to_down(Matrix54i &puzzle, class area_check_return &ret, class area_check_return &ret2){
    int yt = ret.y +1;
    int ytt = ret2.y +1;
    swap(puzzle, ret2.y, ret2.x, ytt, ret2.x);
    swap(puzzle, ret.y, ret.x, yt, ret.x);
    return puzzle;
}

Matrix54i move_2x2_right(Matrix54i &puzzle, class area_check_return &ret,
                                class area_check_return &ret2, class area_check_return &ret3,
                                class area_check_return &ret4){
    swap(puzzle, ret4.y, ret4.x, ret4.y, ret4.x+1);
    swap(puzzle, ret2.y, ret2.x, ret2.y, ret2.x+1);
    swap(puzzle, ret.y, ret.x, ret.y, ret.x+1);
    swap(puzzle, ret3.y, ret3.x, ret3.y, ret3.x+1);

    return puzzle;

}

Matrix54i move_2x2_left(Matrix54i &puzzle, class area_check_return &ret,
                                class area_check_return &ret2, class area_check_return &ret3,
                                class area_check_return &ret4){

    swap(puzzle, ret.y, ret.x, ret.y, ret.x-1);
    swap(puzzle, ret3.y, ret3.x, ret3.y, ret3.x-1);
    swap(puzzle, ret4.y, ret4.x, ret4.y, ret4.x-1);
    swap(puzzle, ret2.y, ret2.x, ret2.y, ret2.x-1);


    return puzzle;

}


Matrix54i move_2x2_up(Matrix54i &puzzle, class area_check_return &ret,
                                class area_check_return &ret2, class area_check_return &ret3,
                                class area_check_return &ret4){

    swap(puzzle, ret.y, ret.x, ret.y-1, ret.x);
    swap(puzzle, ret2.y, ret2.x, ret2.y-1, ret2.x);
    swap(puzzle, ret3.y, ret3.x, ret3.y-1, ret3.x);
    swap(puzzle, ret4.y, ret4.x, ret4.y-1, ret4.x);



    return puzzle;

}

Matrix54i move_2x2_down(Matrix54i &puzzle, class area_check_return &ret,
                                class area_check_return &ret2, class area_check_return &ret3,
                                class area_check_return &ret4){

    swap(puzzle, ret3.y, ret3.x, ret3.y+1, ret3.x);
    swap(puzzle, ret4.y, ret4.x, ret4.y+1, ret4.x);
    swap(puzzle, ret.y, ret.x, ret.y+1, ret.x);
    swap(puzzle, ret2.y, ret2.x, ret2.y+1, ret2.x);


    return puzzle;

}



bool clear(Matrix54i puzzle){
    if(puzzle(4,1) == 0 && puzzle(4,2) == 0){
        return true;
    }else{
        return false;
    }
}



Matrix54i num_simple(Matrix54i puzzle, int i){
    Matrix54i copy_puzzle = puzzle;
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


Matrix54i board_simple(Matrix54i &puzzle){
    for (int i = 1; i < 10; i++ ){
        puzzle = num_simple(puzzle,i);
    }
    return puzzle;
}


bool check_rightside(Matrix54i puzzle, int checkval){
    std::vector<area_check_return> num = area_check(puzzle,checkval);

    if (checkval > 0 && checkval < 5 ){
        for (const auto& item : num){
            if(range_and_vacantcheck_right(puzzle,item) == false){
                return false;
            }
        }
    return true;

    }else if(checkval > 5 && checkval < 10 ){
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

bool check_leftside(Matrix54i puzzle, int checkval){
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

bool check_upside(Matrix54i puzzle, int checkval){
    std::vector<area_check_return> num = area_check(puzzle,checkval);

    if(checkval == 5){
        for (const auto& item : num){
            if(range_and_vacantcheck_up(puzzle,item) == false){
                return false;
            }
        }
    return true;

    }else if(checkval > 0  && checkval < 5){

        return range_and_vacantcheck_up(puzzle,num[0]);

    }else if(checkval > 5 && checkval <10){

        return range_and_vacantcheck_up(puzzle,num[0]);

    }else if(checkval == 0){

        if(range_and_vacantcheck_up(puzzle,num[0]) && range_and_vacantcheck_up(puzzle,num[1])){
            return true;

        }
        return false;

    }
    return false;
}

bool check_downside(Matrix54i puzzle, int checkval){
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

std::vector<int> right_movable_list(Matrix54i puzzle){
    std::vector<int> stack_moveright;
    for(int i = 0; i < 10 ; i++){
        if(check_rightside(puzzle,i)){
            stack_moveright.push_back(i);
        }
    }
    return stack_moveright;
}

std::vector<int> left_movable_list(Matrix54i puzzle){
    std::vector<int> stack_moveleft;
    for(int i = 0; i < 10 ; i++){
        if(check_leftside(puzzle,i)){
            stack_moveleft.push_back(i);
        }
    }
    return stack_moveleft;
}

std::vector<int> up_movable_list(Matrix54i puzzle){
    std::vector<int> stack_moveup;
    for(int i = 0; i < 10 ; i++){
        if(check_upside(puzzle,i)){
            stack_moveup.push_back(i);
        }
    }
    return stack_moveup;
}

std::vector<int> down_movable_list(Matrix54i puzzle){
    std::vector<int> stack_movedown;
    for(int i = 0; i < 10 ; i++){
        if(check_downside(puzzle,i)){
            stack_movedown.push_back(i);
        }
    }
    return stack_movedown;
}

//動かす

Matrix54i movepuzzle_right(Matrix54i &puzzle,int val){

    Matrix54i cop = puzzle;
    if(val == 0){
        std::vector<area_check_return> num = area_check(puzzle,0);
        Matrix54i ret_puzzle = move_2x2_right(cop,num[0],num[1],num[2],num[3]);
        return ret_puzzle;

    }else if(val > 0 && val < 6){
        std::vector<area_check_return> num = area_check(puzzle,val);
        Matrix54i ret_puzzle = move_2x1_to_right(cop,num[0],num[1]);
        return ret_puzzle;

    }else{
        std::vector<area_check_return> num = area_check(puzzle,val);
        Matrix54i ret_puzzle = move_1x1_to_right(cop,num[0]);
        return ret_puzzle;

    }

}

Matrix54i movepuzzle_left(Matrix54i &puzzle,int val){

    Matrix54i cop = puzzle;
    if(val == 0){
        std::vector<area_check_return> num = area_check(puzzle,0);
        Matrix54i ret_puzzle = move_2x2_left(cop,num[0],num[1],num[2],num[3]);
        return ret_puzzle;

    }else if(val > 0 && val < 6){

        std::vector<area_check_return> num = area_check(puzzle,val);

        Matrix54i ret_puzzle = move_2x1_to_left(cop,num[0],num[1]);
        return ret_puzzle;

    }else{
        std::vector<area_check_return> num = area_check(puzzle,val);
        Matrix54i ret_puzzle = move_1x1_to_left(cop,num[0]);
        return ret_puzzle;

    }

}

Matrix54i movepuzzle_up(Matrix54i &puzzle,int val){

    Matrix54i cop = puzzle;
    if(val == 0){
        std::vector<area_check_return> num = area_check(puzzle,0);
        Matrix54i ret_puzzle = move_2x2_up(cop,num[0],num[1],num[2],num[3]);
        return ret_puzzle;

    }else if(val > 0 && val < 6){
        std::vector<area_check_return> num = area_check(puzzle,val);
        Matrix54i ret_puzzle = move_2x1_to_up(cop,num[0],num[1]);
        return ret_puzzle;

    }else{
        std::vector<area_check_return> num = area_check(puzzle,val);

        Matrix54i ret_puzzle = move_1x1_to_up(cop,num[0]);
        return ret_puzzle;

    }

}

Matrix54i movepuzzle_down(Matrix54i &puzzle,int val){

    Matrix54i cop = puzzle;
    if(val == 0){
        std::vector<area_check_return> num = area_check(puzzle,0);
        Matrix54i ret_puzzle = move_2x2_down(cop,num[0],num[1],num[2],num[3]);
        return ret_puzzle;

    }else if(val > 0 && val < 6){
        std::vector<area_check_return> num = area_check(puzzle,val);
        Matrix54i ret_puzzle = move_2x1_to_down(cop,num[0],num[1]);
        return ret_puzzle;

    }else{
        std::vector<area_check_return> num = area_check(puzzle,val);
        Matrix54i ret_puzzle = move_1x1_to_down(cop,num[0]);
        return ret_puzzle;

    }

}

std::vector<Matrix54i> move_right(Matrix54i &puzzle){
    std::vector<Matrix54i> ret_list;
    std::vector<int> right_movenum = right_movable_list(puzzle);
    for(const auto& right_num : right_movenum){
        Matrix54i next_puzzle = movepuzzle_right(puzzle, right_num);
        ret_list.push_back(next_puzzle);
    }
    return ret_list;
}


std::vector<Matrix54i> move_left(Matrix54i &puzzle){
    std::vector<Matrix54i> ret_list;
    std::vector<int> left_movenum = left_movable_list(puzzle);
    for(const auto& left_num : left_movenum){
        Matrix54i next_puzzle = movepuzzle_left(puzzle, left_num);
        ret_list.push_back(next_puzzle);
    }
    return ret_list;
}

std::vector<Matrix54i> move_up(Matrix54i &puzzle){
    std::vector<Matrix54i> ret_list;
    std::vector<int> up_movenum = up_movable_list(puzzle);
    for(const auto& up_num : up_movenum){
        Matrix54i next_puzzle = movepuzzle_up(puzzle, up_num);
        ret_list.push_back(next_puzzle);
    }
    return ret_list;
}

std::vector<Matrix54i> move_down(Matrix54i &puzzle){
    std::vector<Matrix54i> ret_list;
    std::vector<int> down_movenum = down_movable_list(puzzle);
    for(const auto& down_num : down_movenum){
        Matrix54i next_puzzle = movepuzzle_down(puzzle, down_num);
        ret_list.push_back(next_puzzle);
    }
    return ret_list;
}

//現在の盤面から動くことが可能な盤面を見つけ出す
std::vector<Matrix54i> moved_board_list(Matrix54i &puzzle){

    std::vector<Matrix54i> movable;
    std::vector<Matrix54i> right = move_right(puzzle);
    std::vector<Matrix54i> left = move_left(puzzle);
    std::vector<Matrix54i> up = move_up(puzzle);
    std::vector<Matrix54i> down = move_down(puzzle);

    if(right.size() == 1){
        movable.push_back(right[0]);
    }else if(right.size() == 2){
        movable.push_back(right[0]);
        movable.push_back(right[1]);
    }

    if(left.size() == 1){
        movable.push_back(left[0]);
    }else if(left.size() == 2){
        movable.push_back(left[0]);
        movable.push_back(left[1]);
    }

    if(up.size() == 1){
        movable.push_back(up[0]);
    }else if(up.size() == 2){
        movable.push_back(up[0]);
        movable.push_back(up[1]);
    }

    if(down.size() == 1){
        movable.push_back(down[0]);
    }else if(down.size() == 2){
        movable.push_back(down[0]);
        movable.push_back(down[1]);

    }
    return movable;
}

std::string to_hashable(const Matrix54i& simple_puzzle) {
    std::string hash;
    for(int y = 0; y < 5; y ++){
        for(int x = 0; x < 4 ; x++){
            int num = simple_puzzle(y,x);
            std::string str = std::to_string(num);
            hash += str;
        }
    }
    return hash;
}


bool exist( std::string hash_puzzle, std::vector<std::string>  puzzle_state){
    if(std::find(puzzle_state.begin(), puzzle_state.end(), hash_puzzle) == puzzle_state.end()){
        return true;
    }else{
        return false;
    }
}

//クリアしたルートを導き出す
std::vector<Matrix54i> route(std::unordered_map<Matrix54i, Matrix54i, KeyHasher, KeyEqual>& edges, Matrix54i moved_puzzle) {
    Matrix54i root = init_puzzle();
    std::vector<Matrix54i> c_route;
    Matrix54i val = moved_puzzle; // 最初のvalをmoved_puzzleから初期化

    while (val != root) {
        c_route.push_back(val);
        val = edges[val]; // 次の値を取得
    }

    c_route.push_back(root); // rootを追加

    return c_route;
}



void queue_state_append(Matrix54i before_moving, std::vector<Matrix54i> movable, std::vector<std::string> &puzzle_state,
                        std::unordered_map<Matrix54i, Matrix54i , KeyHasher, KeyEqual> &edges, std::queue<Matrix54i> &puzzle_list, std::vector<std::vector<Matrix54i>> &c_route){

    for(Matrix54i& state : movable){
        Matrix54i state_copy = state;
        Matrix54i simple_puzzle = board_simple(state_copy);
        std::string hash_puzzle = to_hashable(simple_puzzle);

       if (exist(hash_puzzle, puzzle_state)) {
    // ここで hash_puzzle は文字列のまま使用します
            edges[state] = before_moving; //現在のMatrixから一つ前のMatrixにアクセスできるようにする

            puzzle_state.push_back(hash_puzzle);
            puzzle_list.push(state);
            std::cout<< "new token = \n" << state << std::endl;

            if (clear(state)) {
                std::vector<Matrix54i> add_c_route = route(edges,state);
                c_route.push_back(add_c_route);
            }
        }
    }
}


std::vector<std::vector<Matrix54i>> breadth_first_search(Matrix54i &puzzle){
  std::vector<std::vector<Matrix54i>> c_route;      //クリアする道順を入れるベクター
  std::unordered_map<Matrix54i, Matrix54i , KeyHasher, KeyEqual> edges;   //unordered_map
  std::vector<std::string> puzzle_state;            //状態を入れていくベクター
  std::queue<Matrix54i> puzzle_list;                //動かす盤面を入れていくベクター

  Matrix54i copy_puzzle = puzzle;
  puzzle_list.push(puzzle);
  Matrix54i simple_puzzle = board_simple(copy_puzzle);
  std::string str = to_hashable(simple_puzzle);
  puzzle_state.push_back(str);

while(!puzzle_list.empty()){
        Matrix54i now_puzzle = puzzle_list.front();
        puzzle_list.pop();
        std::vector<Matrix54i> movable = moved_board_list(now_puzzle);
        queue_state_append(now_puzzle ,movable, puzzle_state, edges, puzzle_list, c_route);
}
    std::cout << "総手数は" << puzzle_state.size() << "手です" << std::endl;

    return c_route;

}



int shortest(std::vector<std::vector<Matrix54i>> &c_route){
    std::vector<Matrix54i> shortest_vec;
    bool isFirst = true;
    for(std::vector<Matrix54i> v: c_route){
        if(isFirst || v.size() < shortest_vec.size()){
            shortest_vec = v;
            isFirst = false;
        }
    }
    for(Matrix54i a : shortest_vec){
        std::cout << a << std::endl;
    }
    return shortest_vec.size();
}




