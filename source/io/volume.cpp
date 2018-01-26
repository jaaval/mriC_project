
#include "volume.h"
#include <iostream>


double Volume::get(int i, int t) {
  return data[i][t];
}

double Volume::get(int x, int y, int z, int t) {
  int index = xyz_to_i(x,y,z, dims);
  return data[index][t];
}

std::vector<double>& Volume::get(int x, int y, int z) {
  int index = xyz_to_i(x,y,z, dims);
  return data[index];
}

std::vector<int> Volume::getNeighborhoodIndices(int x, int y, int z, int r) {
  std::vector<int> indices;
  for (int a = x - r; a < x + r+1; a++) {
    for (int b = y - r; b < y + r+1; b++) {
      for (int c = z - r; c < z + r+1; c++) {
        if (a == x+r || a == x-r || b == y+r || b == y-r || c == z+r || c == z-r) {
          if (a >= 0 && b >= 0 && c >= 0 && a < dims[0] && b < dims[1] && c < dims[2]) {
            indices.push_back(xyz_to_i(a, b, c, dims));
          }
        }
      }
    }
  }
  return indices;
}

std::vector<int> Volume::getNeighborhoodIndices(int i, int r) {
  std::vector<int> xyz = i_to_xyz(i, dims);
  return getNeighborhoodIndices(xyz[0], xyz[1], xyz[2], r);
}

Volume::Volume() {//test constructor
  dims[0] = 64;
  dims[1] = 64;
  dims[2] = 48;
  dims[3] = 5;
  for (int i = 0; i < 64*64*48; i++) {
    std::vector<double> datatest = {i,i,i,i,i};
    data.push_back(datatest);
  }
}




int main() {
  int num = 25*25*25;
  Volume asdf;
  double test1 = asdf.get(num,2);
  int ds[] = {64,64,48, 5};
  std::vector<int> bla = i_to_xyz(num, ds);
  double test2 = asdf.get(bla[0], bla[1], bla[2], 2);
  std::cout << test1 << std::endl;
  std::cout << test2 << std::endl;
  std::cout << bla[0] << " " << bla[1] << " " << bla[2] << std::endl;
  std::vector<int> bla2 = asdf.getNeighborhoodIndices(num, 2);
  for (auto iter = bla2.begin(); iter < bla2.end(); iter++) {
    std::cout << *iter << std::endl;
  }
  std::cout << "---------------------" << std::endl;
  std::vector<int> bla3 = asdf.getNeighborhoodIndices(num, 1);
  std::vector<int> bla4;
  for (auto iter = bla3.begin(); iter < bla3.end(); iter++) {
    bla4 = i_to_xyz(*iter, ds);
    std::cout << bla4[0] << " " << bla4[1] << " " << bla4[2] << std::endl;
  }
}
