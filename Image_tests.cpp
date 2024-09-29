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
TEST(test_width_height){
  Image a;
  Image b;
  Image_init(&a, 2, 7);
<<<<<<< HEAD
  ASSERT_TRUE(a.width == 2);
  ASSERT_TRUE(a.height == 7);
  Image_init(&b, 1, 16);
  ASSERT_TRUE(b.width == 1);
  ASSERT_TRUE(b.height == 16);
=======
  assert(Image_width(&a) == 2);
  assert(Image_height(&a) == 7);
  Image_init(&b, 1, 16);
  assert(Image_width(&b) == 1);
  assert(Image_height(&b) == 16);
>>>>>>> e7b339c (Project 2 final)
}

TEST(test_get_pixel){
  Image d;
  Image_init(&d, 7, 8);
<<<<<<< HEAD
  Matrix a;
  Matrix_init(&a, 7, 8);
  Matrix_fill(&a, 200);
  Matrix b;
  Matrix_init(&b, 7, 8);
  Matrix_fill(&b, 165);
  Matrix c;
  Matrix_init(&c, 7, 8);
  Matrix_fill(&c, 92);
  d.red_channel = a;
  d.green_channel = b;
  d.blue_channel = c;
  Pixel p1;
  p1.r = 200;
  p1.g = 165;
  p1.b = 92;
  ASSERT_TRUE(Pixel_equal(p1, Image_get_pixel(&d, 4, 3)));
  ASSERT_TRUE(Pixel_equal(p1, Image_get_pixel(&d, 6, 0)));
  ASSERT_TRUE(Pixel_equal(p1, Image_get_pixel(&d, 5, 1)));
=======

  Pixel red = {200, 165, 92};
  Image_fill(&d, red);

  assert(Pixel_equal(red, Image_get_pixel(&d, 4, 3)));
  assert(Pixel_equal(red, Image_get_pixel(&d, 6, 0)));
  assert(Pixel_equal(red, Image_get_pixel(&d, 5, 1)));
>>>>>>> e7b339c (Project 2 final)
}

TEST(test_set_pixel){
  Image d;
  Image_init(&d, 7, 8);

  Pixel p2 {200, 165, 92};
  Image_fill(&d, p2);

  Pixel p1 = {102, 143, 2};

  Image_set_pixel(&d, 3, 4, p1);
  ASSERT_TRUE(Pixel_equal((Image_get_pixel(&d, 3, 4)), p1));
}


TEST(test_get_pixel_two){
  Image d;
  Image_init(&d, 7, 8);

  Pixel p1 = {200, 165, 92};
  Image_fill(&d, p1);

  ASSERT_TRUE(Pixel_equal(p1, Image_get_pixel(&d, 4, 3)));
  ASSERT_TRUE(Pixel_equal(p1, Image_get_pixel(&d, 6, 0)));
  ASSERT_TRUE(Pixel_equal(p1, Image_get_pixel(&d, 5, 1)));
}

TEST(test_set_pixel_two){
  Image d;
  Image_init(&d, 7, 8);

  Pixel p1 = {200, 165, 92};

  Pixel p2 = {102, 143, 2};

  Image_set_pixel(&d, 3, 2, p1);
<<<<<<< HEAD
  Image_set_pixel(&d, 3, 4, p2);
  ASSERT_TRUE(Pixel_equal((Image_get_pixel(&d, 3, 2)), p1));
  ASSERT_TRUE(Pixel_equal((Image_get_pixel(&d, 3, 4)), p2));
}

TEST_MAIN()
=======
  Image_set_pixel(&d, 0, 6, p2);
  Image_set_pixel(&d, 6, 6, p2);
  Pixel_equal((Image_get_pixel(&d, 3, 2)), p1);
  Pixel_equal((Image_get_pixel(&d, 0, 6)), p2);
  Pixel_equal((Image_get_pixel(&d, 6, 6)), p2);
}

TEST(test_image_fill) {
  Image d;
  Image_init(&d, 7, 8);

  Pixel hot_pink = {255, 105, 180};

  Image_fill(&d, hot_pink);

  assert(Pixel_equal(hot_pink, Image_get_pixel(&d, 0, 0)));
  assert(Pixel_equal(hot_pink, Image_get_pixel(&d, 7, 6)));
}

TEST(test_image_init){
  string data = "P3\n"
                "2 2\n"    
                "255\n" 
                "255 0 0  0 255 0\n"  
                "0 0 255  255 255 255\n";  

    istringstream input_stream(data);

    Image img;
    Image_init(&img, input_stream);

    ASSERT_EQUAL(Image_width(&img), 2);
    ASSERT_EQUAL(Image_height(&img), 2);

    Pixel p1 = {255, 0, 0};
    assert(Pixel_equal(p1, Image_get_pixel(&img, 0, 0)));

    Pixel p2 = {0, 255, 0};
    assert(Pixel_equal(p2, Image_get_pixel(&img, 0, 1)));


    Pixel p3 = {0, 0, 255};
    assert(Pixel_equal(p3, Image_get_pixel(&img, 1, 0)));

    Pixel p4 = {255, 255, 255};
    assert(Pixel_equal(p4, Image_get_pixel(&img, 1, 1)));
}

TEST_MAIN() // Do NOT put a semicolon here
>>>>>>> e7b339c (Project 2 final)
