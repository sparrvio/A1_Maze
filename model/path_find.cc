#include "path_find.h"

/// @brief Метод поиска пути в лабиринте по алгоритму волнового поиска. Пока мы
/// не найдем искомую точку, заполняем матрицу с посещенными точками, а так же
/// "волну" значений, каждый раз прибаляя по еденице для следующего значенияы
/// волны. Послле того, как искомая точка найдена, восстанавливаем путь, каждый
/// раз уменьшая значение волны на единицу.
/// @return искомый путь
std::vector<s21::PathFind::Point> s21::PathFind::findPath(
    const std::vector<std::vector<int>>& rightWalls,
    const std::vector<std::vector<int>>& downWalls, const Point start,
    const Point end) {
  std::queue<Point> q;
  q.push(start);

  std::vector<std::vector<bool>> visited(
      rightWalls.size(), std::vector<bool>(rightWalls[0].size(), false));
  std::vector<std::vector<int>> wave(rightWalls.size(),
                                     std::vector<int>(rightWalls[0].size(), 0));

  while (!q.empty()) {
    Point current = q.front();
    q.pop();

    int x = current.x_;
    int y = current.y_;

    if (x == end.x_ && y == end.y_) {
      path_.push_back(end);
      while (!(x == start.x_ && y == start.y_)) {
        int dx = 0;
        int dy = 0;
        if (x > 0 && wave[x - 1][y] == wave[x][y] - 1 &&
            downWalls[x - 1][y] == 0) {
          dx = -1;
        } else if (x < rightWalls.size() - 1 &&
                   wave[x + 1][y] == wave[x][y] - 1 && downWalls[x][y] == 0) {
          dx = 1;
        } else if (y > 0 && wave[x][y - 1] == wave[x][y] - 1 &&
                   rightWalls[x][y - 1] == 0) {
          dy = -1;
        } else if (y < rightWalls[0].size() - 1 &&
                   wave[x][y + 1] == wave[x][y] - 1 && rightWalls[x][y] == 0) {
          dy = 1;
        }
        x += dx;
        y += dy;

        path_.insert(path_.begin(), Point(x, y));
      }
      return path_;
    }

    if (visited[x][y]) {
      continue;
    }

    visited[x][y] = true;

    std::vector<std::pair<int, int>> directions = {
        {1, 0}, {0, 1}, {-1, 0}, {0, -1}};

    for (const auto& dir : directions) {
      int dx = dir.first;
      int dy = dir.second;
      int nx = x + dx;
      int ny = y + dy;
      if (nx < 0 || nx >= rightWalls.size() || ny < 0 ||
          ny >= rightWalls[0].size()) {
        continue;
      }
      if (dy == 1 && rightWalls[x][y] == 1) {
        continue;
      }
      if (dx == 1 && downWalls[x][y] == 1) {
        continue;
      }

      if (dy == -1 && rightWalls[x][y - 1] == 1) {
        continue;
      }

      if (dx == -1 && downWalls[x - 1][y] == 1) {
        continue;
      }

      if (!visited[nx][ny]) {
        wave[nx][ny] = wave[x][y] + 1;
        q.push(Point(nx, ny));
      }
    }
  }
  return std::vector<s21::PathFind::Point>();
}
