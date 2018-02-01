#ifndef VOLUME_H
#define VOLUME_H

#include <vector>
#include <assert.h>
#include <stdint.h>

typedef struct VolInfo {
  int a;//placeholder
} VolInfo;

int xyz_to_i(int x, int y, int z, int dims[]);

std::vector<int> i_to_xyz(int i, int dims[]);


class Volume {

public:

  Volume();
  Volume( int64_t dims_[]);
  ~Volume();

  double* get(int i, int t);
  double* get(int x, int y, int z, int t);
  std::vector<double*>& get(int i);
  std::vector<double*>& get(int x, int y, int z);

  std::vector<std::vector<double*>>& getDataReference() {return data;}

  // these are for accessing cenrtain parts of the 3d data. return indices of the data.
  std::vector<int> getNeighborhoodIndices(int i, int r);
  std::vector<int> getNeighborhoodIndices(int x, int y, int z, int r);
  std::vector<int> getSliceIndices(int i, int direction);

  void printData();

private:

  void createContainer();

  // data (x*y*z) * t * (datadim)
  std::vector<std::vector<double*>> data;
  VolInfo info;

  int dims[4];
  int datadim;
  // TODO aux params

};

#endif
