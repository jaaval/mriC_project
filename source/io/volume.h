#ifndef VOLUME_H
#define VOLUME_H

#include <vector>
#include <assert.h>

typedef struct VolInfo {
  int a;//placeholder
} VolInfo;

int xyz_to_i(int x, int y, int z, int dims[]) {
  assert(x < dims[0] &&  y < dims[1] && z < dims[2]);
  return x * dims[1] * dims[2] + y * dims[2] + z;
}

std::vector<int> i_to_xyz(int i, int dims[]) {
  assert(i < dims[0] * dims[1] * dims[2]);
  int yz = dims[1] * dims[2];
  int x = i / yz;
  int ix = (i - x * yz);
  int y = ix / dims[2];
  int z = ix % dims[2];
  return std::vector<int> {x,y,z};
}

class Volume {

public:

  Volume();

  double get(int i, int t);
  double get(int x, int y, int z, int t);
  std::vector<double>& get(int x, int y, int z);

  std::vector<int> getNeighborhoodIndices(int i, int r);
  std::vector<int> getNeighborhoodIndices(int x, int y, int z, int r);

private:

  // data x*y*z*t
  std::vector<std::vector<double>> data;
  VolInfo info;

  int dims[4];

};

#endif
