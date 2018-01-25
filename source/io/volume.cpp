
#include "volume.h"


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

std::vector<int> Volume::getNeighborhoodIndices(int i, int r) {
  int[] xyz = i_to_xyz(i, dims);
  int size = (2*r+1) * (2*r+1) * (2*r+1);
  int indices[size];
  int counter = 0;
  for (int a = xyz[0] - r; a < xyz[0] + r+1; a++) {
    for (int b = xyz[1] - r; b < xyz[1] + r+1; b++) {
      for (int c = xyz[2] - r; c < xyz[2] + r+1; c++) {
        indices[counter++] = xyz_to_i(a, b, c, dims);
      }
    }
  }
  return std::vector<int> v(indices, size)
}
