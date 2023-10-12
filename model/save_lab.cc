#include "save_lab.h"

/// @brief Метод возвращает ширину лабиринта, если текущее значение x > 1
int s21::Maze_Saver::get_size_x() {
  if (x_size_ < 1) throw std::invalid_argument("Incorrect maze size =(");
  return x_size_;
}
/// @brief Метод возвращает длинну лабиринта, если текущее значение у > 1
int s21::Maze_Saver::get_size_y() {
  if (y_size_ < 1) throw std::invalid_argument("Incorrect maze size =(");
  return y_size_;
}

/// @brief Метод копирует значение строки, для матрицы отвечающей за отрисовку
/// вертикальных стенок, из текстового файла, записывает данные значения в
/// вектор для последующего сохранения
/// @param line_namber - номер текущей строи
/// @return заполненый значениями строки вектор
std::vector<int> s21::Maze_Saver::get_matrixRigth_line(int line_namber) {
  std::vector<int> current;
  for (auto it = 0; it < matrixRight_[line_namber].size(); ++it) {
    current.push_back(matrixRight_[line_namber][it]);
  }
  current.shrink_to_fit();
  return current;
}

/// @brief Метод копирует значение строки, для матрицы отвечающей за отрисовку
/// горизонтальных стенок, из текстового файла, записывает данные значения в
/// вектор для последующего сохранения
/// @param line_namber - номер текущей строи
/// @return заполненый значениями строки вектор
std::vector<int> s21::Maze_Saver::get_matrixBottom_line(int line_namber) {
  std::vector<int> current;
  for (auto it = 0; it < matrixBottom_[line_namber].size(); ++it) {
    current.push_back(matrixBottom_[line_namber][it]);
  }
  current.shrink_to_fit();
  return current;
}
/// @brief Метод сохранения текущего лабиринта. Получение из первой строки
/// размеров лабиринта, получение в цикле матрицы отвечающей за отрисовку
/// вертикальных стенок и в последующем цикле получение значений для матрицы
/// отвечающей за отрисовку горизонтальных стенок.
void s21::Maze_Saver::SaveCurrentMaze() {
  std::ofstream file;
  file.open(maze_path_);
  if (file.is_open()) {
    int iterator = 0;
    file << get_size_y() << " " << get_size_x() << std::endl;
    while (iterator < y_size_) {
      std::string current_string = "\0";
      current_string = CreateStringFromVectorRigth(iterator);
      file << current_string << std::endl;
      ++iterator;
    }
    file << std::endl;
    iterator = 0;
    while (iterator < y_size_) {
      std::string current_string = "\0";
      current_string = CreateStringFromVectorBottom(iterator);
      file << current_string << std::endl;
      ++iterator;
    }
    file.close();
  }
}

/// @brief В методе создаеться строка из линии текстового файла, для
/// последующего парсинга и преобразования в вектор, для записи в матрицу
/// отвечающую за отрисовку вертикальных стенок.
std::string s21::Maze_Saver::CreateStringFromVectorRigth(int iterator) {
  std::string resultString = " ";
  std::vector<int> current_line = get_matrixRigth_line(iterator);
  for (int it = 0; it < current_line.size(); ++it) {
    if (current_line[it] == 1) {
      resultString += "1";
    } else {
      resultString += "0";
    }
    resultString += " ";
  }
  if (resultString.back() == ' ') {
    resultString.pop_back();
  }

  return resultString;
}
/// @brief В методе создаеться строка из линии текстового файла, для
/// последующего парсинга и преобразования в вектор, для записи в матрицу
/// отвечающую за отрисовку горизонтальных стенок.
std::string s21::Maze_Saver::CreateStringFromVectorBottom(int iterator) {
  std::string resultString = " ";
  std::vector<int> current_line = get_matrixBottom_line(iterator);
  for (int it = 0; it < current_line.size(); ++it) {
    if (current_line[it] == 1) {
      resultString += "1";
    } else {
      resultString += "0";
    }
    resultString += " ";
  }
  if (resultString.back() == ' ') {
    resultString.pop_back();
  }

  return resultString;
}
