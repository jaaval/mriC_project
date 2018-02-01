
#include "volume.h"
#include <iostream>


double* Volume::get(int i, int t) {
  return data[i][t];
}

double* Volume::get(int x, int y, int z, int t) {
  int index = xyz_to_i(x,y,z, dims);
  return data[index][t];
}

std::vector<double*>& Volume::get(int x, int y, int z) {
  int index = xyz_to_i(x,y,z, dims);
  return data[index];
}

std::vector<int> Volume::getNeighborhoodIndices(int x, int y, int z, int r) {
  int n = (2*r+1)*(2*r+1) - (2*(r-1)+1)*(2*(r-1)+1);
  std::vector<int> indices(n);
  int counter = 0;
  for (int a = x - r; a < x + r+1; a++) {
    for (int b = y - r; b < y + r+1; b++) {
      for (int c = z - r; c < z + r+1; c++) {
        if (a == x+r || a == x-r || b == y+r || b == y-r || c == z+r || c == z-r) {
          if (a >= 0 && b >= 0 && c >= 0 && a < dims[0] && b < dims[1] && c < dims[2]) {
            indices[counter++] = xyz_to_i(a, b, c, dims);
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


void Volume::createContainer() {
  int n = dims[0] * dims[1] * dims[2];
  int t = dims[3];
  std::vector<std::vector<double*>> temp1(n, std::vector<double*>(t, NULL));
  data = temp1;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < t; j++) {
      double* temp3 = new double[datadim];
      data[i][j] = temp3;
    }
  }
}


void Volume::printData() {
  for (auto iter1 = data.begin(); iter1 < data.end(); iter1++) {
    for (auto iter2 = iter1->begin(); iter2 < iter1->end(); iter2++) {
      if (*iter2 && *iter2 != NULL) {
        for (int i = 0; i < datadim; i++) {
          std::cout << *iter2[i] << " ";
        }
        std::cout << " - ";
      }
    }
    std::cout << std::endl;
  }
}

Volume::Volume(int64_t dims_[]) {
  // set info on container dimensions
  for (int i = 1; i < 5; i++) {
    dims[i-1] = dims_[i];
  }
  if (dims_[0] < 5) {
    datadim = 1;
  } else {
    datadim = dims_[5];
  }
  // allocate the container
  createContainer();
}

Volume::Volume() {//test constructor
  dims[0] = 64;
  dims[1] = 64;
  dims[2] = 48;
  dims[3] = 5;
  datadim = 1;
  for (int i = 0; i < 64*64*48; i++) {
    std::vector<double*> temp;
    for (int j = 0; j < 5; j++) {
      double* datatesti = new double[datadim];
      datatesti[0] = i;
      temp.push_back(datatesti);
    }
    data.push_back(temp);
  }
}

Volume::~Volume() {
  for (auto iter1 = data.begin(); iter1 < data.end(); iter1++) {
    for (auto iter2 = iter1->begin(); iter2 < iter1->end(); iter2++) {
      if (*iter2 && *iter2 != NULL) {
        delete[] *iter2;
      }
    }
  }
}



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




int testmain() {
  int num = 25*25*25;
  Volume asdf;
  double* test11 = asdf.get(num,2);
  double test1 = test11[0];
  int ds[] = {64,64,48, 5};
  std::vector<int> bla = i_to_xyz(num, ds);
  double* test22 = asdf.get(bla[0], bla[1], bla[2], 2);
  double test2 = test22[0];
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
