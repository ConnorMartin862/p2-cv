#include <cassert>
#include <vector>
#include "processing.hpp"

using namespace std;

// v DO NOT CHANGE v ------------------------------------------------
// The implementation of rotate_left is provided for you.
// REQUIRES: img points to a valid Image
// MODIFIES: *img
// EFFECTS:  The image is rotated 90 degrees to the left (counterclockwise).
void rotate_left(Image* img) {

  // for convenience
  int width = Image_width(img);
  int height = Image_height(img);

  // auxiliary image to temporarily store rotated image
  Image aux;
  Image_init(&aux, height, width); // width and height switched

  // iterate through pixels and place each where it goes in temp
  for (int r = 0; r < height; ++r) {
    for (int c = 0; c < width; ++c) {
      Image_set_pixel(&aux, width - 1 - c, r, Image_get_pixel(img, r, c));
    }
  }

  // Copy data back into original
  *img = aux;
}
// ^ DO NOT CHANGE ^ ------------------------------------------------

// v DO NOT CHANGE v ------------------------------------------------
// The implementation of rotate_right is provided for you.
// REQUIRES: img points to a valid Image.
// MODIFIES: *img
// EFFECTS:  The image is rotated 90 degrees to the right (clockwise).
void rotate_right(Image* img){

  // for convenience
  int width = Image_width(img);
  int height = Image_height(img);

  // auxiliary image to temporarily store rotated image
  Image aux;
  Image_init(&aux, height, width); // width and height switched

  // iterate through pixels and place each where it goes in temp
  for (int r = 0; r < height; ++r) {
    for (int c = 0; c < width; ++c) {
      Image_set_pixel(&aux, c, height - 1 - r, Image_get_pixel(img, r, c));
    }
  }

  // Copy data back into original
  *img = aux;
}
// ^ DO NOT CHANGE ^ ------------------------------------------------


// v DO NOT CHANGE v ------------------------------------------------
// The implementation of diff2 is provided for you.
static int squared_difference(Pixel p1, Pixel p2) {
  int dr = p2.r - p1.r;
  int dg = p2.g - p1.g;
  int db = p2.b - p1.b;
  // Divide by 100 is to avoid possible overflows
  // later on in the algorithm.
  return (dr*dr + dg*dg + db*db) / 100;
}
// ^ DO NOT CHANGE ^ ------------------------------------------------


// ------------------------------------------------------------------
// You may change code below this line!



// REQUIRES: img points to a valid Image.
//           energy points to a Matrix.
// MODIFIES: *energy
// EFFECTS:  energy serves as an "output parameter".
//           The Matrix pointed to by energy is initialized to be the same
//           size as the given Image, and then the energy matrix for that
//           image is computed and written into it.
//           See the project spec for details on computing the energy matrix.
void compute_energy_matrix(const Image* img, Matrix* energy) {
  Matrix_init(energy, Image_width(img), Image_height(img));
  Pixel north;
  Pixel south;
  Pixel west;
  Pixel east;
  int width = Matrix_width(energy);
  int height = Matrix_height(energy);
  int sum;
  int max = 0;
  for (int i = 0; i < height; i++){
    for (int j = 0 ; j < width; j++){
      if (i!=0 || j !=0 || i != height-1 || j != width-1){
        north = Image_get_pixel(img, i-height, j);
        south = Image_get_pixel(img, i+height, j);
        west = Image_get_pixel(img, i, j-width);
        east = Image_get_pixel(img, i, j+width);
        sum = squared_difference(north, south) + squared_difference(west, east);
        energy->data[i*height + width] = sum;
      }
    }
  }
  for (int k = 0; k < height*width; k++){
    if (max < energy->data[k]){
      max = energy->data[k];
    }
  }
  Matrix_fill_border(energy, max); 
  // TODO Replace with your implementation!
   // TODO delete me, this is here to make it compile
}


// REQUIRES: energy points to a valid Matrix.
//           cost points to a Matrix.
//           energy and cost aren't pointing to the same Matrix
// MODIFIES: *cost
// EFFECTS:  cost serves as an "output parameter".
//           The Matrix pointed to by cost is initialized to be the same
//           size as the given energy Matrix, and then the cost matrix is
//           computed and written into it.
//           See the project spec for details on computing the cost matrix.
void compute_vertical_cost_matrix(const Matrix* energy, Matrix *cost) {
  assert(energy != cost);
  int width = Matrix_width(energy);
  int height = Matrix_height(energy);
  Matrix_init(cost, width, height);
  int e;
  int min = 0;
  for (int i = 0; i < width; i++){
    cost->data[i] = energy->data[i];
  for (int j = 1; j < height; j++){
    for (int k = 0; k < width; k++){
      e = *Matrix_at(energy, j, k);
      if (k-1 < 0){
        min = Matrix_min_value_in_row(energy, j, k, k+1);
      }
      else if (k+1 >= width){
        min = Matrix_min_value_in_row(energy, j, k-1, k);
      }
      else {
        min = Matrix_min_value_in_row(energy, j, k-1, k+1);
      }
      cost->data[(height*j)+k] = e+min;
    }
  }
  } // TODO Replace with your implementation!
}


// REQUIRES: cost points to a valid Matrix
// EFFECTS:  Returns the vertical seam with the minimal cost according to the given
//           cost matrix, represented as a vector filled with the column numbers for
//           each pixel along the seam, starting with the lowest numbered row (top
//           of image) and progressing to the highest (bottom of image). The length
//           of the returned vector is equal to Matrix_height(cost).
//           While determining the seam, if any pixels tie for lowest cost, the
//           leftmost one (i.e. with the lowest column number) is used.
//           See the project spec for details on computing the minimal seam.
vector<int> find_minimal_vertical_seam(const Matrix* cost) {
  int height = Matrix_height(cost);
  int width = Matrix_width(cost);
  vector<int> min_seam_reverse = {};
  vector<int> min_seam = {};
  int column;
  int min;
  for (int i = height-1; i > -1; i--){
      column = Matrix_column_of_min_value_in_row(cost, i, 0, width-1);
      min = *Matrix_at(cost, i, column);
      min_seam_reverse.push_back(min);
  }
  for (int j = min_seam_reverse.size()-1; j > -1; j--){
    min_seam.push_back(min_seam_reverse[j]);
  }
  return min_seam;
  // TODO Replace with your implementation!
}


// REQUIRES: img points to a valid Image with width >= 2
//           seam.size() == Image_height(img)
//           each element x in seam satisfies 0 <= x < Image_width(img)
// MODIFIES: *img
// EFFECTS:  Removes the given vertical seam from the Image. That is, one
//           pixel will be removed from every row in the image. The pixel
//           removed from row r will be the one with column equal to seam[r].
//           The width of the image will be one less than before.
//           See the project spec for details on removing a vertical seam.
// NOTE:     Declare a new variable to hold the smaller Image, and
//           then do an assignment at the end to copy it back into the
//           original image.
void remove_vertical_seam(Image *img, const vector<int> &seam) {
  assert(img->width >=2);
  int size = seam.size();
  assert(size == Image_height(img));
  Image copy;
  Image_init(&copy, Image_width(img)-1, Image_height(img)-1);
  for (int i = 0; i < Image_width(img); i++){
    if (0 > seam[i] || seam[i] >= Image_width(img)){
      assert(false);
    }
  }
  for (int j = 0; j < Image_height(img); j++){
    for (int k = 0; k < Image_width(img); k++){
      if (seam[j] != k){
        if (seam[j] < k){
          Image_get_pixel(&copy, j, k) = Image_get_pixel(img, j, k);
        }
        else if (seam[j] > k){
          Image_get_pixel(&copy, j, k-1) = Image_get_pixel(img, j, k);
        }
      }
    }
  }
  img = &copy;
  // TODO Replace with your implementation!
}


// REQUIRES: img points to a valid Image
//           0 < newWidth && newWidth <= Image_width(img)
// MODIFIES: *img
// EFFECTS:  Reduces the width of the given Image to be newWidth by using
//           the seam carving algorithm. See the spec for details.
// NOTE:     Use a vector to hold the seam, and make sure that it has
//           the right size. You can use .data() on a vector to get
//           the underlying array.
void seam_carve_width(Image *img, int newWidth) {
  assert(0 < newWidth && newWidth <= Image_width(img));
  Matrix energy;
  Matrix cost;
  compute_energy_matrix(img, &energy);
  compute_vertical_cost_matrix(&energy, &cost);
// TODO Replace with your implementation!
}

// REQUIRES: img points to a valid Image
//           0 < newHeight && newHeight <= Image_height(img)
// MODIFIES: *img
// EFFECTS:  Reduces the height of the given Image to be newHeight.
// NOTE:     This is equivalent to first rotating the Image 90 degrees left,
//           then applying seam_carve_width(img, newHeight), then rotating
//           90 degrees right.
void seam_carve_height(Image *img, int newHeight) {
  assert(0 < newHeight && newHeight <= Image_height(img));
  rotate_left(img);
  seam_carve_width(img, newHeight);
  rotate_right(img);
   // TODO Replace with your implementation!
}

// REQUIRES: img points to a valid Image
//           0 < newWidth && newWidth <= Image_width(img)
//           0 < newHeight && newHeight <= Image_height(img)
// MODIFIES: *img
// EFFECTS:  Reduces the width and height of the given Image to be newWidth
//           and newHeight, respectively.
// NOTE:     This is equivalent to applying seam_carve_width(img, newWidth)
//           and then applying seam_carve_height(img, newHeight).
void seam_carve(Image *img, int newWidth, int newHeight) {
  assert(0 < newWidth && newWidth <= Image_width(img));
  assert(0 < newHeight && newHeight <= Image_height(img));
  seam_carve_width(img, newWidth);
  seam_carve_height(img, newHeight);
  // TODO Replace with your implementation!
}
