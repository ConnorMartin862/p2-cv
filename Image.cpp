#include <cassert>
#include "Image.hpp"

// REQUIRES: img points to an Image
//           0 < width && 0 < height
// MODIFIES: *img
// EFFECTS:  Initializes the Image with the given width and height, with
//           all pixels initialized to RGB values of 0.
void Image_init(Image* img, int width, int height) {
  assert(width > 0);
  assert(height > 0);

  img->width = width;
  img->height = height;

  Matrix_init(&img->green_channel, width, height);
  Matrix_init(&img->red_channel, width, height);
  Matrix_init(&img->blue_channel, width, height);

  for (int i = 0; i < height; i++){
    for (int j = 0; j < width; j++) {
      *Matrix_at(&img->green_channel, i, j) = 0;
      *Matrix_at(&img->red_channel, i, j) = 0;
      *Matrix_at(&img->blue_channel, i, j) = 0;
    }
  }
}

// REQUIRES: img points to an Image
//           is contains an image in PPM format without comments
//           (any kind of whitespace is ok)
// MODIFIES: *img, is
// EFFECTS:  Initializes the Image by reading in an image in PPM format
//           from the given input stream.
// NOTE:     See the project spec for a discussion of PPM format.
void Image_init(Image* img, std::istream& is) {
  std::string plain;
  is >> plain;
  assert(plain == "P3");

  int width;
  int height;
  int max_value;

  is >> width >> height;
  is >> max_value;

  img->width = width;
  img->height = height;

  img->red_channel = {width, height, std::vector<int>(width * height)};
  img->green_channel = {width, height, std::vector<int>(width * height)};
  img->blue_channel = {width, height, std::vector<int>(width * height)};


  for (int i = 0; i < width * height; i++) {
    int r;
    int g;
    int b;

    is >> r >> g >> b;
    img->red_channel.data[i] = r;
    img->green_channel.data[i] = g;
    img->blue_channel.data[i] = b;
  }

  return;
}

// REQUIRES: img points to a valid Image
// MODIFIES: os
// EFFECTS:  Writes the image to the given output stream in PPM format.
//           You must use the kind of whitespace specified here.
//           First, prints out the header for the image like this:
//             P3 [newline]
//             WIDTH [space] HEIGHT [newline]
//             255 [newline]
//           Next, prints out the rows of the image, each followed by a
//           newline. Each pixel in a row is printed as three ints
//           for its red, green, and blue components, in that order. Each
//           int is followed by a space. This means that there will be an
//           "extra" space at the end of each line. See the project spec
//           for an example.
void Image_print(const Image* img, std::ostream& os) {
  os << "P3" << std::endl;

  os << img->width << " " << img->height << std::endl;
  os << "255" << std::endl;

  for(int i = 0; i < img->height; i++) {
    for (int j = 0; j < img->width; j++) {
      os << img->red_channel.data[(i * img->width) + j] << " " <<
       img->green_channel.data[(i * img->width) + j] << " " << 
       img->blue_channel.data[(i * img->width) + j] << " ";
    }
    os << std::endl;
  }

  return;
}

// REQUIRES: img points to a valid Image
// EFFECTS:  Returns the width of the Image.
int Image_width(const Image* img) {
  return img->width;
}

// REQUIRES: img points to a valid Image
// EFFECTS:  Returns the height of the Image.
int Image_height(const Image* img) {
  return img -> height;
}

// REQUIRES: img points to a valid Image
//           0 <= row && row < Image_height(img)
//           0 <= column && column < Image_width(img)
// EFFECTS:  Returns the pixel in the Image at the given row and column.
Pixel Image_get_pixel(const Image* img, int row, int column) {
  assert(0 <= row && row < Image_height(img));
  assert(0 <= column && column < Image_width(img));
  const Matrix* red = &img->red_channel;
  const Matrix* green = &img->green_channel;
  const Matrix* blue = &img->blue_channel;
  const int* redptr = Matrix_at(red, row, column);
  const int* greenptr = Matrix_at(green, row, column);
  const int* blueptr = Matrix_at(blue, row, column);
  Pixel pix;
  pix.r = *redptr;
  pix.g = *greenptr;
  pix.b = *blueptr;
  return pix;
}

// REQUIRES: img points to a valid Image
//           0 <= row && row < Image_height(img)
//           0 <= column && column < Image_width(img)
// MODIFIES: *img
// EFFECTS:  Sets the pixel in the Image at the given row and column
//           to the given color.
void Image_set_pixel(Image* img, int row, int column, Pixel color) {
  assert(0 <= row && row < Image_height(img));
  assert(0 <= column && column < Image_width(img));
  int pixel_num = (row * img->width) + column;

  img->red_channel.data[pixel_num] = color.r;
  img->blue_channel.data[pixel_num] = color.b;
  img->green_channel.data[pixel_num] = color.g;
}

// REQUIRES: img points to a valid Image
// MODIFIES: *img
// EFFECTS:  Sets each pixel in the image to the given color.
void Image_fill(Image* img, Pixel color) {
for (int i = 0; i < Image_height(img); i++){
    for (int j = 0; j < Image_width(img); j++){
      Image_set_pixel(img, i, j, color);
    }
  }
<<<<<<< HEAD
}
=======
}
>>>>>>> b8d506af067ee688c0a3aec0f2da5f66670def7f
