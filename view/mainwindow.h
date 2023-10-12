#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QFile>
#include <QFileDialog>
#include <QMainWindow>
#include <QMessageBox>
#include <QMouseEvent>
#include <QPainter>
#include <QPen>
#include <QStandardPaths>
#include <QTextStream>
#include <iostream>
#include <queue>
#include <vector>

#include "../model/maze.h"
#include "../model/save_lab.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

namespace s21 {
class DrawingWidget;

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void on_Generate_clicked();

 private slots:
  void on_Open_file_clicked();
  void on_Off_clicked();
  void on_Save_labirint_clicked();
  void find_path();

  void on_Size_x_valueChanged(int arg1);
  void on_Size_y_valueChanged(int arg1);

 private:
  void mousePressEvent(QMouseEvent *event);
  int countClickMouse_ = 0;
  Ui::MainWindow *ui;
  DrawingWidget *drawingWidget;
};

class DrawingWidget : public QWidget {
 public:
  DrawingWidget(QWidget *parent = nullptr) : QWidget(parent) {
    setFixedSize(500, 500);
  }

 protected:
  void paintEvent(QPaintEvent *event) override;
  QSize sizeHint() const override { return QSize(500, 500); }
};

class GetDataForLabyrinth {
 public:
  struct Point {
    int x = 0;
    int y = 0;
    Point() = default;
    Point(int _x, int _y) : x(_x), y(_y) {}
  };
  void set_width(int value);
  void set_length(int value);
  void set_path(std::vector<s21::PathFind::Point> current_path);
  void set_start_point(int x, int y);
  void set_finish_point(int x, int y);

  size_t get_width();
  size_t get_length();
  GetDataForLabyrinth::Point get_start_point();
  GetDataForLabyrinth::Point get_finish_point();
  int get_path_size();
  std::vector<s21::PathFind::Point> get_path();

  void GetValues();
  void CheckingDataBeforeFill();
  void GetMatrixParametrs(std::string parametrs_string);
  void FillMatrixRight(std::string data_string);
  void FillMatrixBottom(std::string data_string);
  void CleanPath();

  std::vector<std::vector<int>> matrixRight;
  std::vector<std::vector<int>> matrixBottom;

  QString path_to_file_ = "\0";

 private:
  size_t width_ = 20;
  size_t length_ = 20;
  Point start_;
  Point finish_;
  std::vector<s21::PathFind::Point> path_;
};
};      // namespace s21
#endif  // MAINWINDOW_H
