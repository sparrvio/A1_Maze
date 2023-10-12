#include "mainwindow.h"

#include "./ui_mainwindow.h"

namespace s21 {

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  drawingWidget = new DrawingWidget(this);
}

MainWindow::~MainWindow() { delete ui; }

GetDataForLabyrinth getter;
int flag = 0;

void MainWindow::mousePressEvent(QMouseEvent *event) {
  int x = 0, res_x = 0, y = 0, res_y = 0;

  float cellSizeBottom = 500.0 / getter.get_width();
  float cellSizeRight = 500.0 / getter.get_length();
  if (event->button() == Qt::LeftButton) {
    x = event->position().x();
    y = event->position().y();

    res_x = x / cellSizeBottom + 1;
    res_y = y / cellSizeRight + 1;

    if (x < 501 && y < 501) {
      if (countClickMouse_ == 0 || countClickMouse_ == 2) {
        ui->start_x_point->setValue(res_x);
        ui->start_y_point->setValue(res_y);
        getter.set_start_point(ui->start_x_point->value(),
                               ui->start_y_point->value());
        countClickMouse_++;

        if (countClickMouse_ == 3) {
          ui->finish_x_point->clear();
          ui->finish_y_point->clear();
          getter.CleanPath();
          QWidget::update();
          countClickMouse_ = 1;
        }
      } else {
        ui->finish_x_point->setValue(res_x);
        ui->finish_y_point->setValue(res_y);
        getter.set_finish_point(ui->finish_x_point->value(),
                                ui->finish_y_point->value());
        countClickMouse_++;
      }
    }
    if (countClickMouse_ == 2) {
      find_path();
    }
  } else {
    event->ignore();
    ui->start_x_point->clear();
    ui->start_y_point->clear();
    ui->finish_x_point->clear();
    ui->finish_y_point->clear();
    getter.CleanPath();
    countClickMouse_ = 0;
  }
}

void MainWindow::find_path() {
  GetDataForLabyrinth::Point point = getter.get_start_point();
  s21::PathFind::Point start;
  start.x_ = point.x - 1;
  start.y_ = point.y - 1;
  point = getter.get_finish_point();
  s21::PathFind::Point end;
  end.x_ = point.x - 1;
  end.y_ = point.y - 1;

  s21::PathFind pathFind(getter.matrixRight, getter.matrixBottom);
  std::vector<s21::PathFind::Point> path =
      pathFind.findPath(getter.matrixRight, getter.matrixBottom, start, end);
  getter.set_path(path);
  QWidget::update();
}

void GetDataForLabyrinth::set_path(
    std::vector<s21::PathFind::Point> current_path) {
  getter.path_ = current_path;
}

void DrawingWidget::paintEvent(QPaintEvent *event) {
  QPainter painter(this);

  if (getter.path_to_file_ != "\0" || flag == 1) {
    painter.fillRect(rect(), Qt::gray);
    painter.setPen(QPen(Qt::black, 2));

    float cellSizeVertic = 500.0 / getter.get_length();
    float cellSizeHorizont = 500.0 / getter.get_width();

    painter.drawRect(0, 0, 500, 500);
    for (int i = 0; i < getter.matrixRight[0].size(); i++) {
      for (int j = 0; j < getter.matrixRight.size(); j++) {
        int x = j * cellSizeHorizont;
        int y = i * cellSizeVertic;

        if (getter.matrixRight[j][i]) {
          painter.drawLine(x, y + cellSizeVertic, x + cellSizeHorizont,
                           y + cellSizeVertic);
        }

        if (getter.matrixBottom[j][i]) {
          painter.drawLine(x + cellSizeHorizont, y, x + cellSizeHorizont,
                           y + cellSizeVertic);
        }
      }
    }
    painter.setPen(QPen(Qt::green, 2));

    if (getter.get_path_size() > 1) {
      std::vector<s21::PathFind::Point> current_path = getter.get_path();

      for (unsigned int i = 0; i < current_path.size() - 1; ++i) {
        int startX =
            current_path[i].x_ * cellSizeHorizont + cellSizeHorizont / 2;
        int startY = current_path[i].y_ * cellSizeVertic + cellSizeVertic / 2;
        int endX =
            current_path[i + 1].x_ * cellSizeHorizont + cellSizeHorizont / 2;
        int endY = current_path[i + 1].y_ * cellSizeVertic + cellSizeVertic / 2;
        painter.drawLine(startX, startY, endX, endY);
      }
    }
  }
}

void MainWindow::on_Open_file_clicked() {
  getter.CleanPath();
  QString desktopPath =
      QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
  getter.path_to_file_ = QFileDialog::getOpenFileName(nullptr, "Open file",
                                                      desktopPath, "(*.txt)");
  QFile file(getter.path_to_file_);
  if (file.exists()) {
    getter.GetValues();
    ui->Size_x->setValue(getter.get_length());
    ui->Size_y->setValue(getter.get_width());
    ui->start_x_point->setValue(0);
    ui->start_y_point->setValue(0);
    ui->finish_x_point->setValue(0);
    ui->finish_y_point->setValue(0);
    getter.set_start_point(0, 0);
    getter.set_finish_point(0, 0);
    QWidget::update();
  }
}

void GetDataForLabyrinth::set_width(int value) { this->width_ = value; }

int GetDataForLabyrinth::get_path_size() { return path_.size(); }

void GetDataForLabyrinth::set_length(int value) { this->length_ = value; }

size_t GetDataForLabyrinth::get_width() { return this->width_; }

size_t GetDataForLabyrinth::get_length() { return this->length_; }

std::vector<s21::PathFind::Point> GetDataForLabyrinth::get_path() {
  return path_;
}

void GetDataForLabyrinth::CheckingDataBeforeFill() {
  if (get_length() != 0) {
    set_length(0);
  }
  if (get_width() != 0) {
    set_width(0);
  }
  if (!matrixRight.empty()) {
    matrixRight.clear();
  }
  if (!matrixBottom.empty()) {
    matrixBottom.clear();
  }
}

void GetDataForLabyrinth::GetMatrixParametrs(std::string parametrs_string) {
  std::string number_one = "\0";
  std::string number_two = "\0";
  size_t i = 0;
  for (size_t it = 0; it < parametrs_string.length(); ++it) {
    if (std::isdigit(parametrs_string[it]) || parametrs_string[it] == ' ') {
      while (std::isdigit(parametrs_string[it]) &&
             parametrs_string[it] != ' ') {
        number_one[i] = parametrs_string[it];
        it++;
        i++;
      }
      i = 0;
      if (parametrs_string[it] == ' ') {
        it++;
      }
      while (std::isdigit(parametrs_string[it])) {
        number_two[i] = parametrs_string[it];
        it++;
        i++;
      }
    }
  }
  set_length(std::stod(number_one));
  set_width(std::stod(number_two));
}

void PrintMatrix(const std::vector<std::vector<int>> &matrix) {
  for (const auto &rows : matrix) {
    for (const auto &element : rows) {
      std::cout << (element ? '1' : '0') << ' ';
    }
    std::cout << std::endl;
  }
}

void GetDataForLabyrinth::FillMatrixRight(std::string data_string) {
  std::vector<int> current_vector;
  for (size_t it = 0; it < data_string.length(); ++it) {
    if (data_string[it] == '1') {
      current_vector.push_back(true);
    } else if (data_string[it] == '0') {
      current_vector.push_back(false);
    } else {
      continue;
    }
  }
  current_vector.shrink_to_fit();
  matrixRight.push_back(current_vector);
  current_vector.clear();
}

void GetDataForLabyrinth::FillMatrixBottom(std::string data_string) {
  std::vector<int> current_vector;
  for (size_t it = 0; it < data_string.length(); ++it) {
    if (data_string[it] == '1') {
      current_vector.push_back(true);
    } else if (data_string[it] == '0') {
      current_vector.push_back(false);
    } else {
      continue;
    }
  }
  current_vector.shrink_to_fit();
  matrixBottom.push_back(current_vector);
  current_vector.clear();
}

void GetDataForLabyrinth::GetValues() {
  QFile file(path_to_file_);

  CheckingDataBeforeFill();

  if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    QTextStream in(&file);
    std::string checking_line;
    checking_line = in.readLine().toStdString();
    GetMatrixParametrs(checking_line);

    for (size_t it = 0; it < get_length(); ++it) {
      checking_line = in.readLine().toStdString();
      FillMatrixRight(checking_line);
    }

    checking_line = in.readLine().toStdString();

    for (size_t it = 0; it < get_length(); ++it) {
      checking_line = in.readLine().toStdString();
      FillMatrixBottom(checking_line);
    }
    file.close();
  }
}

void GetDataForLabyrinth::set_start_point(int x, int y) {
  if (x > 0) {
    start_.x = x;
  }
  if (y > 0) {
    start_.y = y;
  }
}

void GetDataForLabyrinth::set_finish_point(int x, int y) {
  if (x > 0) {
    finish_.x = x;
  }
  if (y > 0) {
    finish_.y = y;
  }
}

GetDataForLabyrinth::Point GetDataForLabyrinth::get_start_point() {
  return start_;
}

GetDataForLabyrinth::Point GetDataForLabyrinth::get_finish_point() {
  return finish_;
}
void GetDataForLabyrinth::CleanPath() { this->path_.clear(); }

void MainWindow::on_Off_clicked() { QApplication::quit(); }

void MainWindow::on_Save_labirint_clicked() {
  if (getter.matrixBottom.size() != 0 && getter.matrixRight.size() != 0) {
    QString saveFilePath = QFileDialog::getSaveFileName(
        nullptr, "Save as", "", "Text file (*.txt);;All file (*.*)");
    if (!saveFilePath.isEmpty()) {
      Maze_Saver current_maze(getter.get_length(), getter.get_width(),
                              getter.matrixRight, getter.matrixBottom,
                              saveFilePath.toStdString());
      current_maze.SaveCurrentMaze();
    }
  }
}

void MainWindow::on_Generate_clicked() {
  getter.CleanPath();
  getter.set_length(ui->Size_x->value());
  getter.set_width(ui->Size_y->value());
  s21::Maze maze(getter.get_length(), getter.get_width());
  maze.generateMaze();

  getter.matrixRight = maze.getRightWalls();
  getter.matrixBottom = maze.getBottomWalls();

  getter.set_length(getter.matrixRight[0].size());
  getter.set_width(getter.matrixRight.size());
  ui->start_x_point->setValue(0);
  ui->start_y_point->setValue(0);
  ui->finish_x_point->setValue(0);
  ui->finish_y_point->setValue(0);
  getter.set_start_point(0, 0);
  getter.set_finish_point(0, 0);
  flag = 1;
  if (getter.get_length() > 0 && getter.get_width() > 0) {
    QWidget::update();
  }
}

void MainWindow::on_Size_x_valueChanged(int arg1) { getter.set_width(arg1); }

void MainWindow::on_Size_y_valueChanged(int arg1) { getter.set_length(arg1); }

};  // namespace s21
