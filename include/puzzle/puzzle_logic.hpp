#ifndef HAKOIRICPP_PUZZLE_LOGIC_HPP
#define HAKOIRICPP_PUZZLE_LOGIC_HPP

#include <Eigen/Dense>
#include <vector>
#include <queue>
#include <unordered_map>
#include <functional>
#include <fstream>

using Matrix54i = Eigen::Matrix<int, 5, 4>;
Matrix54i init_puzzle();

class find_location_return
{
public:
    int val;
    int y;
    int x;

    void set_value(int yv, int xv, int v);
};


void swap(Matrix54i &puzzle, int y1, int x1, int y2, int x2);
std::vector<find_location_return> find_location(const Matrix54i &puzzle, int targetValue);
  bool inrange_check_right(const class find_location_return &ret);
  bool inrange_check_left(const class find_location_return &ret);
  bool inrange_check_up(const class find_location_return &ret);
  bool inrange_check_down(const class find_location_return &ret);
  bool empty_check_right(const Matrix54i puzzle, const class find_location_return &ret);
  bool empty_check_left(const Matrix54i puzzle, const class find_location_return &ret);
  bool empty_check_up(const Matrix54i puzzle, const class find_location_return &ret);
  bool empty_check_down(const Matrix54i puzzle, const class find_location_return &ret);
  void move_1x1_to_right(Matrix54i &puzzle, class find_location_return &ret);
  void move_1x1_to_left(Matrix54i &puzzle, class find_location_return &ret);
  void move_1x1_to_up(Matrix54i &puzzle, class find_location_return &ret);
  void move_1x1_to_down(Matrix54i &puzzle, class find_location_return &ret);
  void move_2x1_to_left(Matrix54i &puzzle, class find_location_return &ret,
                      class find_location_return &ret2);
  void move_2x1_to_right(Matrix54i &puzzle, class find_location_return &ret,
                       class find_location_return &ret2);
  void move_2x1_to_up(Matrix54i &puzzle, class find_location_return &ret,
                    class find_location_return &ret2);
  void move_2x1_to_down(Matrix54i &puzzle,
                      class find_location_return &ret, class find_location_return &ret2);
  void move_2x2_right(Matrix54i &puzzle, class find_location_return &ret,
                    class find_location_return &ret2,
                    class find_location_return &ret3,
                    class find_location_return &ret4);
  void move_2x2_left(Matrix54i &puzzle, class find_location_return &ret,
                   class find_location_return &ret2,
                   class find_location_return &ret3,
                   class find_location_return &ret4);
  void move_2x2_up(Matrix54i &puzzle, class find_location_return &ret,
                 class find_location_return &ret2,
                 class find_location_return &ret3,
                 class find_location_return &ret4);
  void move_2x2_down(Matrix54i &puzzle, class find_location_return &ret,
                   class find_location_return &ret2,
                   class find_location_return &ret3,
                   class find_location_return &ret4);

#endif

