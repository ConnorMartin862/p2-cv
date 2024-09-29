#include <iostream>
#include <fstream>
#include "Matrix.hpp"
#include "Image.hpp"
#include "processing.hpp"
using namespace std;

int main(int argc, char *argv[]) {
  if (argc != 4 && argc != 5) {
    cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
     << "WIDTH and HEIGHT must be less than or equal to original" << endl;
     return 1;
  }

  string fileone = argv[1];
  string filetwo = argv[2];
  int w = atoi(argv[3]);

  ifstream fin(fileone);
    if (!(fin.is_open())) {
        cout << "Error opening file: " << fileone << endl;
        return 1;
    }

    Image *a = new Image;
    Image_init(a, fin);

    fin.close();

    int h;

    if (argc!= 5) {
        h = Image_height(a);
    }
    else {
        h = atoi(argv[4]);
    }

    if (w > Image_width(a) || w <= 0 || h > Image_height(a) || h <= 0) {
        cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
        << "WIDTH and HEIGHT must be less than or equal to original" << endl;
        return 1;
    }

    seam_carve(a, w, h);
    ofstream out;
    out.open(filetwo);
    Image_print(a, out);
    out.close();

    delete a;

    return 0;
}