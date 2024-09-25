#include "Matrix.hpp"
#include "Image_test_helpers.hpp"
#include "unit_test_framework.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <cassert>

using namespace std;

// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Sets various pixels in a 2x2 Image and checks
// that Image_print produces the correct output.
TEST(test_print_basic) {
  Image img;
  const Pixel red = {255, 0, 0};
  const Pixel green = {0, 255, 0};
  const Pixel blue = {0, 0, 255};
  const Pixel white = {255, 255, 255};

  Image_init(&img, 2, 2);
  Image_set_pixel(&img, 0, 0, red);
  Image_set_pixel(&img, 0, 1, green);
  Image_set_pixel(&img, 1, 0, blue);
  Image_set_pixel(&img, 1, 1, white);

  // Capture our output
  ostringstream s;
  Image_print(&img, s);

  // Correct output
  ostringstream correct;
  correct << "P3\n2 2\n255\n";
  correct << "255 0 0 0 255 0 \n";
  correct << "0 0 255 255 255 255 \n";
  ASSERT_EQUAL(s.str(), correct.str());
}

// IMPLEMENT YOUR TEST FUNCTIONS HERE
// You are encouraged to use any functions from Image_test_helpers.hpp as needed.
TEST(width_height){
  Image a;
  Image b;
  Image_init(&a, 2, 7);
  assert(a.width == 2);
  assert(a.height == 7);
  Image_init(&b, 1, 16);
  assert(b.width == 1);
  assert(b.height == 16);
}

TEST(get_pixel){
  Image d;
  Image_init(&d, 7, 8);
  Matrix a;
  Matrix_init(&a, 7, 8);
  Matrix_fill(&a, 200);
  Matrix b;
  Matrix_init(&a, 7, 8);
  Matrix_fill(&b, 165);
  Matrix c;
  Matrix_init(&a, 7, 8);
  Matrix_fill(&c, 92);
  d.red_channel = a;
  d.green_channel = b;
  d.blue_channel = c;
  Pixel p1;
  p1.r = 200;
  p1.g = 165;
  p1.b = 92;
  assert(Pixel_equal(p1, Image_get_pixel(&d, 4, 3)));
  assert(Pixel_equal(p1, Image_get_pixel(&d, 6, 0)));
  assert(Pixel_equal(p1, Image_get_pixel(&d, 5, 1)));
}

TEST(set_pixel){
  Image d;
  Image_init(&d, 7, 8);
  Matrix a;
  Matrix_init(&a, 7, 8);
  Matrix_fill(&a, 200);
  Matrix b;
  Matrix_init(&a, 7, 8);
  Matrix_fill(&b, 165);
  Matrix c;
  Matrix_init(&a, 7, 8);
  Matrix_fill(&c, 92);
  d.red_channel = a;
  d.green_channel = b;
  d.blue_channel = c;
}


TEST_MAIN() // Do NOT put a semicolon here
