#ifndef NIFTI_H
#define NIFTI_H


#include <fstream>
#include <string>

#include "nifti1.h"
#include "nifti2.h"


class Nifti {
public:

  Nifti(const std::string fileName);

  nifti_1_header& getHeader() {
    return header1;
  }

  short dimx() const {
    if (type == 1)
      return header1.dim[0];
    else
      return header2.dim[0];
  }
  short dimy() const {
    if (type == 1)
      return header1.dim[1];
    else
      return header2.dim[1];
  }
  short dimz() const {
    if (type == 1)
      return header1.dim[2];
    else
      return header2.dim[2];
  }
  short dimt() const {
    if (type == 1)
      return header1.dim[3];
    else
      return header2.dim[3];
  }

  void readFile(std::string fileName);


private:

  void readHeaderType1(std::ifstream& ifs, bool swap);
  void readHeaderType2(std::ifstream& ifs, bool swap);
  void readData(std::ifstream& ifs);
  void checkDataType(std::ifstream& ifs);

  nifti_1_header header1;
  nifti_2_header header2;
  int type;
  bool dataLoaded;
  bool swap;
  std::string fileName;

};


// cast functions for binary data reading

int cast_to_int(char* buffer4, bool swap) {
  int a;
  if (swap) {
    a = (int) (buffer4[0] << 24 | buffer4[1] << 16 | buffer4[2] << 8 | buffer4[3]);
  } else {
    a = (int) (buffer4[3] << 24 | buffer4[2] << 16 | buffer4[1] << 8 | buffer4[0]);
  }
  return a;
}

float cast_to_float(char* buffer4, bool swap) {
  return (float) (buffer4[3] << 24 | buffer4[2] << 16 | buffer4[1] << 8 | buffer4[0]);
}

short cast_to_short(char* buffer2, bool swap) {
  short a;
  if (swap) {
    a = (short) (buffer2[0] << 8 | buffer2[1]);
  } else {
    a =  (short) (buffer2[1] << 8 | buffer2[0]);
  }
  return a;
}





#endif
