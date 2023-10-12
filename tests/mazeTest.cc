#include <gtest/gtest.h>

#include "../model/maze.cc"
#include "../model/path_find.cc"
#include "../model/save_lab.cc"

void expectVectorsEqual(const std::vector<s21::PathFind::Point>& expected,
                        const std::vector<s21::PathFind::Point>& actual) {
  ASSERT_EQ(expected.size(), actual.size());
  for (size_t i = 0; i < expected.size(); ++i) {
    EXPECT_EQ(expected[i].x_, actual[i].x_);
    EXPECT_EQ(expected[i].y_, actual[i].y_);
  }
}

TEST(Generation, Test_2) {
  s21::Maze maze(20, 20);
  maze.generateMaze();
  EXPECT_EQ(maze.getRightWalls().size(), 20);
  EXPECT_EQ(maze.getBottomWalls().size(), 20);
}
TEST(Path, Test_3) {
  int rows = 4;
  int cols = 4;
  std::vector<std::vector<int>> RightWalls(rows, std::vector<int>(cols, 0));
  std::vector<std::vector<int>> BottomWalls(rows, std::vector<int>(cols, 0));
  std::vector<s21::PathFind::Point>();
  RightWalls[0][3] = 1;
  RightWalls[1][0] = 1;
  RightWalls[1][2] = 1;
  RightWalls[1][3] = 1;
  RightWalls[2][1] = 1;
  RightWalls[2][3] = 1;
  RightWalls[3][3] = 1;

  BottomWalls[0][0] = 1;
  BottomWalls[0][2] = 1;
  BottomWalls[1][2] = 1;
  BottomWalls[2][0] = 1;
  BottomWalls[2][1] = 1;
  BottomWalls[2][3] = 1;
  BottomWalls[3][0] = 1;
  BottomWalls[3][1] = 1;
  BottomWalls[3][2] = 1;
  BottomWalls[3][3] = 1;
  s21::PathFind m;
  s21::PathFind::Point st;
  st.x_ = 0;
  st.y_ = 0;
  s21::PathFind::Point en;
  en.x_ = 3;
  en.y_ = 3;
  std::vector<s21::PathFind::Point> path;
  path = m.findPath(RightWalls, BottomWalls, st, en);
  std::vector<s21::PathFind::Point> expected = {
      {0, 0}, {0, 1}, {0, 2}, {0, 3}, {1, 3}, {2, 3}, {2, 2}, {3, 2}, {3, 3}};
  expectVectorsEqual(path, expected);  //
}

TEST(MazeSaverTest, GetSizeXTest) {
  std::vector<std::vector<int>> matrixRight = {{1, 0, 1}, {0, 1, 0}, {1, 1, 1}};
  std::vector<std::vector<int>> matrixBottom = {
      {0, 1, 0}, {1, 0, 1}, {0, 0, 1}};
  s21::Maze_Saver mazeSaver(3, 3, matrixRight, matrixBottom, "");

  EXPECT_EQ(mazeSaver.get_size_x(), 3);
}

TEST(MazeSaverTest, GetSizeYTest) {
  std::vector<std::vector<int>> matrixRight = {{1, 0, 1}, {0, 1, 0}, {1, 1, 1}};
  std::vector<std::vector<int>> matrixBottom = {
      {0, 1, 0}, {1, 0, 1}, {0, 0, 1}};
  s21::Maze_Saver mazeSaver(3, 3, matrixRight, matrixBottom, "");

  EXPECT_EQ(mazeSaver.get_size_y(), 3);
}

TEST(MazeSaverTest, CreateStringFromVectorRigthTest) {
  std::vector<std::vector<int>> matrixRight = {{1, 0, 1}, {0, 1, 0}, {1, 1, 1}};
  std::vector<std::vector<int>> matrixBottom = {
      {0, 1, 0}, {1, 0, 1}, {0, 0, 1}};
  s21::Maze_Saver mazeSaver(3, 3, matrixRight, matrixBottom, "");

  std::string result = mazeSaver.CreateStringFromVectorRigth(1);
  EXPECT_EQ(result, " 0 1 0");
}

TEST(MazeSaverTest, CreateStringFromVectorBottomTest) {
  std::vector<std::vector<int>> matrixRight = {{1, 0, 1}, {0, 1, 0}, {1, 1, 1}};
  std::vector<std::vector<int>> matrixBottom = {
      {0, 1, 0}, {1, 0, 1}, {0, 0, 1}};
  s21::Maze_Saver mazeSaver(3, 3, matrixRight, matrixBottom, "");

  std::string result = mazeSaver.CreateStringFromVectorBottom(2);
  EXPECT_EQ(result, " 0 0 1");
}

TEST(MazeSaverTest, SaveCurrentMazeTest) {
  std::vector<std::vector<int>> matrixRight = {{1, 0, 1}, {0, 1, 0}, {1, 1, 1}};
  std::vector<std::vector<int>> matrixBottom = {
      {0, 1, 0}, {1, 0, 1}, {0, 0, 1}};
  s21::Maze_Saver mazeSaver(3, 3, matrixRight, matrixBottom, "saved_maze.txt");

  mazeSaver.SaveCurrentMaze();

  std::ifstream file("saved_maze.txt");
  std::string line;
  std::vector<std::string> lines;
  while (std::getline(file, line)) {
    lines.push_back(line);
  }

  EXPECT_EQ(lines[0], "3 3");
  EXPECT_EQ(lines[1], " 1 0 1");
  EXPECT_EQ(lines[2], " 0 1 0");
  EXPECT_EQ(lines[3], " 1 1 1");
  EXPECT_EQ(lines[4], "");
  EXPECT_EQ(lines[5], " 0 1 0");
  EXPECT_EQ(lines[6], " 1 0 1");
  EXPECT_EQ(lines[7], " 0 0 1");
}
TEST(MazeSaverTest, FileOpenTest) {
  std::vector<std::vector<int>> matrixRight = {{1, 0, 1}, {0, 1, 0}, {1, 1, 1}};
  std::vector<std::vector<int>> matrixBottom = {
      {0, 1, 0}, {1, 0, 1}, {0, 0, 1}};
  s21::Maze_Saver mazeSaver1(3, 3, matrixRight, matrixBottom,
                             "saved_maze1.txt");
  mazeSaver1.SaveCurrentMaze();

  std::ifstream file("saved_maze1.txt");
  EXPECT_TRUE(file.is_open());
  file.close();
}

TEST(MazeSaverTest, FileContentTest) {
  std::vector<std::vector<int>> matrixRight = {{1, 0, 1}, {0, 1, 0}, {1, 1, 1}};
  std::vector<std::vector<int>> matrixBottom = {
      {0, 1, 0}, {1, 0, 1}, {0, 0, 1}};
  s21::Maze_Saver mazeSaver(3, 3, matrixRight, matrixBottom, "saved_maze1.txt");

  mazeSaver.SaveCurrentMaze();

  std::ifstream file("saved_maze1.txt");
  ASSERT_TRUE(file.is_open());

  int sizeY, sizeX;
  file >> sizeY >> sizeX;
  EXPECT_EQ(sizeY, mazeSaver.get_size_y());
  EXPECT_EQ(sizeX, mazeSaver.get_size_x());

  std::string line;
  std::getline(file, line);

  int iterator = 0;
  while (iterator < mazeSaver.get_size_x()) {
    std::string expectedString =
        mazeSaver.CreateStringFromVectorRigth(iterator);
    std::getline(file, line);
    EXPECT_EQ(line, expectedString);
    ++iterator;
  }

  std::getline(file, line);

  iterator = 0;
  while (iterator < mazeSaver.get_size_x()) {
    std::string expectedString =
        mazeSaver.CreateStringFromVectorBottom(iterator);
    std::getline(file, line);
    EXPECT_EQ(line, expectedString);
    ++iterator;
  }
  file.close();
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
