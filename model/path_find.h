#ifndef PATH_FIND_H_
#define PATH_FIND_H_

#include <iomanip>
#include <iostream>
#include <queue>
#include <random>
#include <vector>

namespace s21 {
class PathFind {
 public:
  struct Point {
    int x_ = 0;
    int y_ = 0;
    Point() = default;
    Point(int x, int y) : x_(x), y_(y){};
  };
  Point start;
  Point end;
  PathFind() = default;
  PathFind(std::vector<std::vector<int>>& rightWalls_,
           std::vector<std::vector<int>>& bottomWalls_){};

  ~PathFind(){};

  std::vector<Point> findPath(const std::vector<std::vector<int>>& rightWalls_,
                              const std::vector<std::vector<int>>& bottomWalls_,
                              const Point start, const Point end);

  const std::vector<s21::PathFind::Point>& getPath() { return path_; }

 private:
  Point start_;
  Point end_;
  std::vector<PathFind::Point> path_;
  std::vector<std::vector<int>> rightWalls_;
  std::vector<std::vector<int>> bottomWalls_;
};

}  // namespace s21
#endif  // PATH_FIND_H_