#include <iostream>
#include <cstdio>
#include <cstring>
#include <Eigen/Dense>
#include <chrono>
#include "puzzle/puzzle_logic.hpp"
#include "puzzle/graph_logic.hpp"

bool clear(const Matrix54i &puzzle)
{
    if (puzzle(4, 1) == 0 && puzzle(4, 2) == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

Matrix54i num_simple(const Matrix54i &puzzle, const int i)
{
    Matrix54i copy_puzzle = puzzle;
    std::vector<find_location_return> num = find_location(puzzle, i);
    for (const auto &item : num)
    {
        if (item.val > 0 && item.val < 5)
        {
            copy_puzzle(item.y, item.x) = 2;
        }
        else if (item.val > 5 && item.val < 10)
        {
            copy_puzzle(item.y, item.x) = 3;
        }
        else
        {
            continue;
        }
    }
    return copy_puzzle;
}

Matrix54i board_simple(const Matrix54i &puzzle)
{
    Matrix54i copy_puzzle = puzzle;
    for (int i = 1; i < 10; i++)
    {
        copy_puzzle = num_simple(copy_puzzle, i);
    }
    return copy_puzzle;
}

bool range_and_emptycheck_right(const Matrix54i &puzzle, const class find_location_return &ret)
{
    if (inrange_check_right(ret) && empty_check_right(puzzle, ret))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool range_and_emptycheck_left(const Matrix54i &puzzle, const class find_location_return &ret)
{
    if (inrange_check_left(ret) && empty_check_left(puzzle, ret))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool range_and_emptycheck_up(const Matrix54i &puzzle, const class find_location_return &ret)
{
    if (inrange_check_up(ret) && empty_check_up(puzzle, ret))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool range_and_emptycheck_down(const Matrix54i &puzzle, const class find_location_return &ret)
{
    if (inrange_check_down(ret) && empty_check_down(puzzle, ret))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool check_rightside(const Matrix54i &puzzle, const int checkval)
{
    std::vector<find_location_return> num = find_location(puzzle, checkval);

    if (checkval > 0 && checkval < 5)
    {
        for (const auto &item : num)
        {
            if (range_and_emptycheck_right(puzzle, item) == false)
            {
                return false;
            }
        }
        return true;
    }
    else if (checkval > 5 && checkval < 10)
    {
        return range_and_emptycheck_right(puzzle, num[0]);
    }
    else if (checkval == 5)
    {
        return range_and_emptycheck_right(puzzle, num[1]);
    }
    else if (checkval == 0)
    {

        if (range_and_emptycheck_right(puzzle, num[1]) && range_and_emptycheck_right(puzzle, num[3]))
        {
            return true;
        }
        return false;
    }
    else
    {
        return false;
    }

    return false;
}

bool check_leftside(const Matrix54i &puzzle, const int checkval)
{
    std::vector<find_location_return> num = find_location(puzzle, checkval);

    if (checkval > 0 && checkval < 5)
    {
        for (const auto &item : num)
        {
            if (range_and_emptycheck_left(puzzle, item) == false)
            {
                return false;
            }
        }
        return true;
    }
    else if (checkval > 4 && checkval < 10)
    {
        return range_and_emptycheck_left(puzzle, num[0]);
    }
    else if (checkval == 0)
    {
        if (range_and_emptycheck_left(puzzle, num[0]) && range_and_emptycheck_left(puzzle, num[2]))
        {
            return true;
        }
        return false;
    }
    return false;
}

bool check_upside(const Matrix54i &puzzle, int checkval)
{
    std::vector<find_location_return> num = find_location(puzzle, checkval);

    if (checkval == 5)
    {
        for (const auto &item : num)
        {
            if (range_and_emptycheck_up(puzzle, item) == false)
            {
                return false;
            }
        }
        return true;
    }
    else if (checkval > 0 && checkval < 5)
    {

        return range_and_emptycheck_up(puzzle, num[0]);
    }
    else if (checkval > 5 && checkval < 10)
    {

        return range_and_emptycheck_up(puzzle, num[0]);
    }
    else if (checkval == 0)
    {

        if (range_and_emptycheck_up(puzzle, num[0]) && range_and_emptycheck_up(puzzle, num[1]))
        {
            return true;
        }
        return false;
    }
    return false;
}

bool check_downside(const Matrix54i &puzzle, int checkval)
{
    std::vector<find_location_return> num = find_location(puzzle, checkval);
    if (checkval == 5)
    {
        for (const auto &item : num)
        {
            if (range_and_emptycheck_down(puzzle, item) == false)
            {
                return false;
            }
        }
        return true;
    }
    else if (checkval > 0 && checkval < 5)
    {
        return range_and_emptycheck_down(puzzle, num[1]);
    }
    else if (checkval > 5 && checkval < 10)
    {
        return range_and_emptycheck_down(puzzle, num[0]);
    }
    else if (checkval == 0)
    {
        if (range_and_emptycheck_down(puzzle, num[2]) && range_and_emptycheck_down(puzzle, num[3]))
        {
            return true;
        }
        return false;
    }
    return false;
}

std::vector<int> numbers_canmove_right(const Matrix54i &puzzle)
{
    std::vector<int> stack_moveright;
    for (int i = 0; i < 10; i++)
    {
        if (check_rightside(puzzle, i))
        {
            stack_moveright.push_back(i);
        }
    }
    return stack_moveright;
}

std::vector<int> numbers_canmove_left(const Matrix54i &puzzle)
{
    std::vector<int> stack_moveleft;
    for (int i = 0; i < 10; i++)
    {
        if (check_leftside(puzzle, i))
        {
            stack_moveleft.push_back(i);
        }
    }
    return stack_moveleft;
}

std::vector<int> numbers_canmove_up(const Matrix54i &puzzle)
{
    std::vector<int> stack_moveup;
    for (int i = 0; i < 10; i++)
    {
        if (check_upside(puzzle, i))
        {
            stack_moveup.push_back(i);
        }
    }
    return stack_moveup;
}

std::vector<int> numbers_canmove_down(const Matrix54i &puzzle)
{
    std::vector<int> stack_movedown;
    for (int i = 0; i < 10; i++)
    {
        if (check_downside(puzzle, i))
        {
            stack_movedown.push_back(i);
        }
    }
    return stack_movedown;
}

Matrix54i movepuzzle_right(const Matrix54i &puzzle, const int val)
{
    Matrix54i copy_puzzle = puzzle;
    if (val == 0)
    {
        std::vector<find_location_return> num = find_location(puzzle, 0);
        move_2x2_right(copy_puzzle, num[0], num[1], num[2], num[3]);
        return copy_puzzle;
    }
    else if (val > 0 && val < 6)
    {
        std::vector<find_location_return> num = find_location(puzzle, val);
        move_2x1_to_right(copy_puzzle, num[0], num[1]);
        return copy_puzzle;
    }
    else
    {
        std::vector<find_location_return> num = find_location(puzzle, val);
        move_1x1_to_right(copy_puzzle, num[0]);
        return copy_puzzle;
    }
}

Matrix54i movepuzzle_left(const Matrix54i &puzzle, const int val)
{
    Matrix54i copy_puzzle = puzzle;
    if (val == 0)
    {
        std::vector<find_location_return> num = find_location(puzzle, 0);
        move_2x2_left(copy_puzzle, num[0], num[1], num[2], num[3]);
        return copy_puzzle;
    }
    else if (val > 0 && val < 6)
    {
        std::vector<find_location_return> num = find_location(puzzle, val);
        move_2x1_to_left(copy_puzzle, num[0], num[1]);
        return copy_puzzle;
    }
    else
    {
        std::vector<find_location_return> num = find_location(puzzle, val);
        move_1x1_to_left(copy_puzzle, num[0]);
        return copy_puzzle;
    }
}

Matrix54i movepuzzle_up(const Matrix54i &puzzle, const int val)
{
    Matrix54i copy_puzzle = puzzle;
    if (val == 0)
    {
        std::vector<find_location_return> num = find_location(puzzle, 0);
        move_2x2_up(copy_puzzle, num[0], num[1], num[2], num[3]);
        return copy_puzzle;
    }
    else if (val > 0 && val < 6)
    {
        std::vector<find_location_return> num = find_location(puzzle, val);
        move_2x1_to_up(copy_puzzle, num[0], num[1]);
        return copy_puzzle;
    }
    else
    {
        std::vector<find_location_return> num = find_location(puzzle, val);
        move_1x1_to_up(copy_puzzle, num[0]);
        return copy_puzzle;
    }
}

Matrix54i movepuzzle_down(const Matrix54i &puzzle, const int val)
{
    Matrix54i copy_puzzle = puzzle;
    if (val == 0)
    {
        std::vector<find_location_return> num = find_location(puzzle, 0);
        move_2x2_down(copy_puzzle, num[0],
                      num[1], num[2], num[3]);
        return copy_puzzle;
    }
    else if (val > 0 && val < 6)
    {
        std::vector<find_location_return> num = find_location(puzzle, val);
        move_2x1_to_down(copy_puzzle, num[0], num[1]);
        return copy_puzzle;
    }
    else
    {
        std::vector<find_location_return> num = find_location(puzzle, val);
        move_1x1_to_down(copy_puzzle, num[0]);
        return copy_puzzle;
    }
}

std::vector<Matrix54i> move_right(const Matrix54i &puzzle)
{
    std::vector<Matrix54i> ret_list;
    std::vector<int> right_movenum = numbers_canmove_right(puzzle);
    for (const auto &right_num : right_movenum)
    {
        Matrix54i next_puzzle = movepuzzle_right(puzzle, right_num);
        ret_list.push_back(next_puzzle);
    }
    return ret_list;
}

std::vector<Matrix54i> move_left(const Matrix54i &puzzle)
{
    std::vector<Matrix54i> ret_list;
    std::vector<int> left_movenum = numbers_canmove_left(puzzle);
    for (const auto &left_num : left_movenum)
    {
        Matrix54i next_puzzle = movepuzzle_left(puzzle, left_num);
        ret_list.push_back(next_puzzle);
    }
    return ret_list;
}

std::vector<Matrix54i> move_up(const Matrix54i &puzzle)
{
    std::vector<Matrix54i> ret_list;
    std::vector<int> up_movenum = numbers_canmove_up(puzzle);
    for (const auto &up_num : up_movenum)
    {
        Matrix54i next_puzzle = movepuzzle_up(puzzle, up_num);
        ret_list.push_back(next_puzzle);
    }
    return ret_list;
}

std::vector<Matrix54i> move_down(const Matrix54i &puzzle)
{
    std::vector<Matrix54i> ret_list;
    std::vector<int> down_movenum = numbers_canmove_down(puzzle);
    for (const auto &down_num : down_movenum)
    {
        Matrix54i next_puzzle = movepuzzle_down(puzzle, down_num);
        ret_list.push_back(next_puzzle);
    }
    return ret_list;
}

std::vector<Matrix54i> moved_board_list(const Matrix54i &input)
{
    Matrix54i puzzle = input;
    std::vector<Matrix54i> movable;
    std::vector<Matrix54i> right = move_right(puzzle);
    std::vector<Matrix54i> left = move_left(puzzle);
    std::vector<Matrix54i> up = move_up(puzzle);
    std::vector<Matrix54i> down = move_down(puzzle);
    if (right.size() == 1)
    {
        movable.push_back(right[0]);
    }
    else if (right.size() == 2)
    {
        movable.push_back(right[0]);
        movable.push_back(right[1]);
    }
    if (left.size() == 1)
    {
        movable.push_back(left[0]);
    }
    else if (left.size() == 2)
    {
        movable.push_back(left[0]);
        movable.push_back(left[1]);
    }
    if (up.size() == 1)
    {
        movable.push_back(up[0]);
    }
    else if (up.size() == 2)
    {
        movable.push_back(up[0]);
        movable.push_back(up[1]);
    }
    if (down.size() == 1)
    {
        movable.push_back(down[0]);
    }
    else if (down.size() == 2)
    {
        movable.push_back(down[0]);
        movable.push_back(down[1]);
    }
    return movable;
}

std::string mat_to_str(const Matrix54i &simple_puzzle)
{
    std::string hash;
    int rows = simple_puzzle.rows();
    int cols = simple_puzzle.cols();

    for (int y = 0; y < rows; y++)
    {
        for (int x = 0; x < cols; x++)
        {
            int num = simple_puzzle(y, x);
            std::string str = std::to_string(num);
            hash += str;
        }
    }
    return hash;
}

std::string mat_to_str_pluscomma(const Matrix54i &simple_puzzle)
{
    std::string hash;
    for (int y = 0; y < 5; y++)
    {
        for (int x = 0; x < 4; x++)
        {
            int num = simple_puzzle(y, x);
            std::string str = std::to_string(num);
            hash += str;
            hash += ",";
        }
    }
    return hash;
}

bool exist(const std::string &hash_puzzle,
           std::vector<std::string> &puzzle_state)
{
    std::chrono::system_clock::time_point start, end; // 計測用関数
    start = std::chrono::system_clock::now();
    // std::reverse(puzzle_state.begin(), puzzle_state.end());
    if (std::find(puzzle_state.begin(), puzzle_state.end(),
                  hash_puzzle) == puzzle_state.end())
    {
        end = std::chrono::system_clock::now();
        double time = static_cast<double>(std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count());
        // printf("%.0lf\n", time);
        return true;
    }
    else
    {
        end = std::chrono::system_clock::now();
        double time = static_cast<double>(std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count());
        // printf("%.0lf\n", time);
        return false;
    }
}

std::vector<Matrix54i> clearroute(std::unordered_map<Matrix54i, Matrix54i,
                                                     KeyHasher, KeyEqual> &edges,
                                  const Matrix54i &moved_puzzle)
{
    std::chrono::system_clock::time_point start, end; // 計測用関数

    Matrix54i root = init_puzzle();
    std::vector<Matrix54i> c_route;
    Matrix54i val = moved_puzzle;

    start = std::chrono::system_clock::now();
    while (val != root)
    {
        c_route.push_back(val);
        val = edges[val];
    }
    c_route.push_back(root);
    return c_route;
}

void queue_state_append(const Matrix54i &before_moving, std::vector<Matrix54i> &movable,
                        std::vector<std::string> &puzzle_state,
                        std::unordered_map<Matrix54i, Matrix54i, KeyHasher, KeyEqual> &edges,
                        std::queue<Matrix54i> &puzzle_list,
                        std::vector<std::vector<Matrix54i>> &c_route)
{
    for (Matrix54i &state : movable)
    {
        Matrix54i state_copy = state;
        Matrix54i simple_puzzle = board_simple(state_copy);
        std::string hash_puzzle = mat_to_str(simple_puzzle);
        if (exist(hash_puzzle, puzzle_state))
        {
            edges[state] = before_moving;
            puzzle_state.push_back(hash_puzzle);
            puzzle_list.push(state);
            if (clear(state))
            {
                std::vector<Matrix54i> add_c_route = clearroute(edges, state);
            }
        }
    }
}

std::vector<std::vector<Matrix54i>> breadth_first_search(const Matrix54i &puzzle)
{
    std::vector<std::vector<Matrix54i>> c_route;
    std::unordered_map<Matrix54i, Matrix54i, KeyHasher, KeyEqual> edges;
    std::vector<std::string> puzzle_state;
    std::queue<Matrix54i> puzzle_list;
    puzzle_list.push(puzzle);
    Matrix54i simple_puzzle = board_simple(puzzle);
    std::string str = mat_to_str(simple_puzzle);
    puzzle_state.push_back(str);
    while (!puzzle_list.empty())
    {
        Matrix54i now_puzzle = puzzle_list.front();
        puzzle_list.pop();
        std::vector<Matrix54i> movable = moved_board_list(now_puzzle);
        queue_state_append(now_puzzle, movable,
                           puzzle_state, edges, puzzle_list, c_route);
    }
    std::cout << "総手数は" << puzzle_state.size() << "手です" << std::endl;
    return c_route;
}

std::vector<Matrix54i> shortestroute_find(const std::vector<std::vector<Matrix54i>> &c_route)
{
    std::vector<Matrix54i> shortest_vec;
    bool isFirst = true;
    for (std::vector<Matrix54i> v : c_route)
    {
        if (isFirst || v.size() < shortest_vec.size())
        {
            shortest_vec = v;
            isFirst = false;
        }
    }
    return shortest_vec;
}
