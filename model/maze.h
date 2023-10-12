#ifndef MAZE_H_
#define MAZE_H_

#include "path_find.h"

namespace s21 {
class Maze {
  int rows_ = 0;
  int cols_ = 0;
  int counter_ = 0;
  std::vector<int> currentLine_;
  std::vector<std::vector<int>> rightWalls_;
  std::vector<std::vector<int>> bottomWalls_;
  bool randomBool();
  void mergeSet(int, int);
  void createUniqueSet();
  bool searchIndeticalSet(int);
  int searchElemWithoutBottmWals(int, int);
  void createRightWals(int);
  void createBottomWals(int);
  void copyCurrentLine(int);
  void endLineCheck();

 public:
  Maze() = default;
  Maze(int rows, int cols)
      : rows_(rows),
        cols_(cols),
        currentLine_(cols_, 0),
        rightWalls_(rows, std::vector<int>(cols, 0)),
        bottomWalls_(rows, std::vector<int>(cols, 0)) {}
  ~Maze() {}

  void generateMaze();
  std::vector<std::vector<int>> getRightWalls();
  std::vector<std::vector<int>> getBottomWalls();
};
}  // namespace s21

#endif  // MAZE_H_