#include "Matrix.hpp"
#include "Matrix_test_helpers.hpp"
#include "unit_test_framework.hpp"

using namespace std;

// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Fills a 3x5 Matrix with a value and checks
// that Matrix_at returns that value for each element.
TEST(test_fill_basic) {
  Matrix mat;
  const int width = 3;
  const int height = 5;
  const int value = 42;
  Matrix_init(&mat, 3, 5);
  Matrix_fill(&mat, value);

  for(int r = 0; r < height; ++r){
    for(int c = 0; c < width; ++c){
      ASSERT_EQUAL(*Matrix_at(&mat, r, c), value);
    }
  }
}

// ADD YOUR TESTS HERE
// You are encouraged to use any functions from Matrix_test_helpers.hpp as needed.
TEST(test_fill_border) {
  Matrix mat;
  const int width = 5;
  const int height = 4;
  const int outside_value = 42;
  const int inside_value = 0;

  Matrix_init(&mat, width, height);
  Matrix_fill(&mat, inside_value);
  Matrix_fill_border(&mat, outside_value);

  for(int r = 0; r < height; ++r){
    for(int c = 0; c < width; ++c){
      if (r == 0 || r == height - 1 || c == 0 || c == width - 1) {
        ASSERT_EQUAL(*Matrix_at(&mat, r, c), outside_value);
      }
      else {
        ASSERT_EQUAL(*Matrix_at(&mat, r, c), inside_value);
      }
    }
  }
}

TEST(test_height_and_width) {
  Matrix mat;
  const int width = 7;
  const int height = 6;

  Matrix_init(&mat, width, height);
  ASSERT_EQUAL(Matrix_height(&mat), height);
  ASSERT_EQUAL(Matrix_width(&mat), width);
}

TEST(test_at_basic){
  Matrix mat;
  const int width = 5;
  const int height = 4;
  const int value = 22;

  Matrix_init(&mat, width, height);
  Matrix_fill(&mat, value);
  ASSERT_EQUAL(*Matrix_at(&mat, 3, 2), value);
}

TEST(test_at_complex){
  Matrix mat;
  const int width = 3;
  const int height = 3;
  const int inside_value = 0;
  const int outside_value = 1;

  Matrix_init(&mat, width, height);
  Matrix_fill(&mat, inside_value);
  Matrix_fill_border(&mat, outside_value);
  ASSERT_EQUAL(*Matrix_at(&mat, 1, 1), inside_value);
}

TEST(test_max){
  Matrix mat;
  const int width = 3;
  const int height = 3;
  const int inside_value = 7;
  const int outside_value = 3;

  Matrix_init(&mat, width, height);
  Matrix_fill(&mat, inside_value);
  Matrix_fill_border(&mat, outside_value);
  ASSERT_EQUAL(Matrix_max(&mat), inside_value);
}

TEST(test_min_column){
  Matrix mat;
  const int width = 3;
  const int height = 3;
  const int inside_value = 3;
  const int outside_value = 7;

  Matrix_init(&mat, width, height);
  Matrix_fill(&mat, inside_value);
  Matrix_fill_border(&mat, outside_value);
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(&mat, 1, 0, 2), 1);
}

TEST(test_min_row){
  Matrix mat;
  const int width = 3;
  const int height = 3;
  const int inside_value = 3;
  const int outside_value = 7;

  Matrix_init(&mat, width, height);
  Matrix_fill(&mat, inside_value);
  Matrix_fill_border(&mat, outside_value);
  ASSERT_EQUAL(Matrix_min_value_in_row(&mat, 1, 0, 2), 3);
}

TEST_MAIN() // Do NOT put a semicolon here
