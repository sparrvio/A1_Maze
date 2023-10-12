#ifndef A1_MAZE_MODEL_SAVE_LAB_H_
#define A1_MAZE_MODEL_SAVE_LAB_H_

#include <fstream>
#include <iostream>
#include <limits>
#include <string>
#include <vector>
namespace s21 {
class Maze_Saver {
 public:
  Maze_Saver(int width, int length, std::vector<std::vector<int>> matrixRight,
             std::vector<std::vector<int>> matrixBottom, std::string path) {
    this->x_size_ = width;
    this->y_size_ = length;
    this->matrixRight_ = matrixRight;
    this->matrixBottom_ = matrixBottom;
    this->maze_path_ = path;
  }

  int get_size_x();
  int get_size_y();
  std::vector<int> get_matrixRigth_line(int line_namber);
  std::vector<int> get_matrixBottom_line(int line_namber);
  void SaveCurrentMaze();
  std::string CreateStringFromVectorRigth(int iterator);
  std::string CreateStringFromVectorBottom(int iterator);

 private:
  int x_size_;
  int y_size_;
  std::vector<std::vector<int>> matrixRight_;
  std::vector<std::vector<int>> matrixBottom_;
  std::string maze_path_;
};
};      // namespace s21
#endif  // A1_MAZE_MODEL_SAVE_LAB_H_