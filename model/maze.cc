#include "maze.h"

/// @brief Метод создает уникальное множество элементов в currentLine_, заменяя
/// каждый нулевой элемент на уникальное числовое значение.
void s21::Maze::createUniqueSet() {
  for (auto &elem : currentLine_) {
    if (elem == 0) {
      elem = ++counter_;
    }
  }
}
/// @brief Генерируем строку с рандомными значениями true/false6 которая поможет
/// принимать нам решение, устанавливать стенку в лабиринте или нет.
bool s21::Maze::randomBool() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(0, 1);
  return dis(gen) == 1;
}

/// @brief Метод объединяет два множества элементов путем замены всех элементов,
/// равных currentNext, на current
void s21::Maze::mergeSet(int current, int currentNext) {
  for (int i = 0; i < cols_; i++) {
    if (currentLine_[i] == currentNext) {
      currentLine_[i] = current;
    }
  }
}

/// @brief Метод createRightWals(int row) выполняет следующие действия: Если row
/// равен 0, вызывается функция createUniqueSet(), которая создает уникальное
/// множество элементов. Затем происходит итерация по каждому элементу в
/// диапазоне от 0 до cols_. Генерируется случайное булево значение с помощью
/// функции randomBool(). Если choise равно true или currentLine_[i] равен
/// currentLine_[i + 1], то rightWalls_[row][i] устанавливается равным 1, что
/// означает наличие правой стены. Если choise равно false, вызывается функция
/// mergeSet(currentLine_[i], currentLine_[i + 1]), которая объединяет два
/// множества элементов. Последний элемент rightWalls_[row][cols_ - 1]
/// устанавливается равным 1, чтобы закрыть правую стену в конце строки.
void s21::Maze::createRightWals(int row) {
  if (row == 0) {
    createUniqueSet();
  }
  for (int i = 0; i < cols_; ++i) {
    bool choise = randomBool();
    if (choise == true || (currentLine_[i] == currentLine_[i + 1])) {
      rightWalls_[row][i] = 1;
    } else if (choise == false) {
      mergeSet(currentLine_[i], currentLine_[i + 1]);
    }
  }
  rightWalls_[row][cols_ - 1] = 1;
}

/// @brief Метод createBottomWals(int row) выполняет следующие действия:
/// Происходит итерация по каждому элементу в диапазоне от 0 до cols_.
/// Генерируется случайное булево значение с помощью функции randomBool(). Если
/// choise равно true и функция searchIndeticalSet(currentLine_[i]) возвращает
/// true, то bottomWalls_[row][i] устанавливается равным 1, что означает наличие
/// нижней стены. Если функция searchElemWithoutBottmWals(currentLine_[i], row)
/// возвращает 0, то bottomWalls_[row][i] устанавливается равным 0, что означает
/// отсутствие нижней стены.
void s21::Maze::createBottomWals(int row) {
  for (int i = 0; i < cols_; i++) {
    bool choise = randomBool();
    if (choise == true && searchIndeticalSet(currentLine_[i])) {
      bottomWalls_[row][i] = 1;
    }
    if (searchElemWithoutBottmWals(currentLine_[i], row) == 0) {
      bottomWalls_[row][i] = 0;
    }
  }
}
/// @brief Метод подсчитывает колличество элементов в строке без нижних границ.
int s21::Maze::searchElemWithoutBottmWals(int value, int row) {
  int countElem = 0;
  for (int i = 0; i < cols_; i++) {
    if (currentLine_[i] == value && bottomWalls_[row][i] == 0) countElem++;
  }
  return countElem;
}
/// @brief Метод подсчитывает одинаковые множества и возвращает true если такие
/// найдены и false6 если не найдены.
bool s21::Maze::searchIndeticalSet(int value) {
  int countIndeticalSet = 0;
  for (int i = 0; i < cols_; i++) {
    if (currentLine_[i] == value) {
      countIndeticalSet++;
    }
  }
  return countIndeticalSet > 1 ? true : false;
}
/// @brief Метод копирует элементы из строки numLine массива bottomWalls_ в
/// массив currentLine_, присваивая им уникальные значения counter_.
void s21::Maze::copyCurrentLine(int numLine) {
  for (int i = 0; i < cols_; i++) {
    counter_++;
    if (bottomWalls_[numLine][i] == 1) {
      currentLine_[i] = counter_;
    }
  }
}

/// @brief Метод проверяет и обрабатывает конец строки в лабиринте.
/// Устанавливает соответствующие значения для правых и нижних стен, включая
/// объединение множеств элементов.
void s21::Maze::endLineCheck() {
  for (int i = 0; i < cols_; i++) {
    if (currentLine_[i] != currentLine_[i + 1]) {
      rightWalls_[rows_ - 1][i] = 0;
      mergeSet(currentLine_[i], currentLine_[i + 1]);
    }
    bottomWalls_[rows_ - 1][i] = 1;
  }
  rightWalls_[rows_ - 1][cols_ - 1] = 1;
};
/// @brief Метод генерирует лабиринт, создавая стены и обрабатывая концы строк.
void s21::Maze::generateMaze() {
  for (int i = 0; i < rows_; i++) {
    if (i == rows_ - 1) {
      createRightWals(i);
      endLineCheck();
    } else {
      createRightWals(i);
      createBottomWals(i);
      copyCurrentLine(i);
    }
  }
}
/// @brief Метод возвращает вертикальные стены лабиринта в виде двумерного
/// вектора. Если rightWalls_ пуст, то метод возвращает пустой вектор. В
/// противном случае, метод возвращает rightWalls_, который содержит информацию
/// о наличии или отсутствии вертикальных стен в лабиринте.
std::vector<std::vector<int>> s21::Maze::getRightWalls() {
  if (rightWalls_.size() < 1) return std::vector<std::vector<int>>();
  return rightWalls_;
}

/// @brief Метод возвращает горизонтальные стены лабиринта в виде двумерного
/// вектора. Если bottomWalls_ пуст, то метод возвращает пустой вектор. В
/// противном случае, метод возвращает bottomWalls_, который содержит информацию
/// о наличии или отсутствии горизонтальных стен в лабиринте.
std::vector<std::vector<int>> s21::Maze::getBottomWalls() {
  if (bottomWalls_.size() < 1) return std::vector<std::vector<int>>();
  return bottomWalls_;
}