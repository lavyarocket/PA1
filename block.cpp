#include "block.h"
#include <cmath>
#include <iostream>

int Block::height() const {
  if (width() == 0) {
    return 0;
  }
  return data[0].size();
}

int Block::width() const {
  return data.size();
}

void Block::render(PNG &im, int x) const {
  for (int row = 0; row < width(); row++) 
    for (int col = 0; col < height(); col++) 
      *(im.getPixel(row+x,col)) = data[row][col];
}

void Block::build(PNG &im, int x, int width) {
  for (int row = 0; row < width; row++) {
    vector<HSLAPixel> tmp;
    for (unsigned int col = 0; col < im.height(); col++) 
      tmp.push_back(*(im.getPixel(row+x,col)));
    data.push_back(tmp);
  }
}
