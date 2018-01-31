#ifndef NIFTI_H
#define NIFTI_H


#include <fstream>
#include <string>

#include "nifti1.h" // constants for the header
#include "nifti2.h" // header definition
#include "volume.h"



class Nifti {
public:

  Nifti(const std::string fileName);

  nifti_2_header& getHeader() {
    return header;
  }

  short dimx() const {
    return header.dim[0];
  }
  short dimy() const {
    return header.dim[1];
  }
  short dimz() const {
    return header.dim[2];
  }
  short dimt() const {
    return header.dim[3];
  }

  void readFile(std::string fileName);


private:

  void readHeaderType1(std::ifstream& ifs, bool swap);
  void readHeaderType2(std::ifstream& ifs, bool swap);
  void readData(std::ifstream& ifs);
  void checkDataType(std::ifstream& ifs);

  nifti_2_header header;
  int type; // nifti1 or 2. the header struct used internally is the same
  bool swap;
  std::string fileName;

  bool header_read;

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
  float a;
  if (swap) {
    a = (float) (buffer4[0] << 24 | buffer4[1] << 16 | buffer4[2] << 8 | buffer4[3]);
  } else {
    a = (float) (buffer4[3] << 24 | buffer4[2] << 16 | buffer4[1] << 8 | buffer4[0]);
  }
  return a;
}

int16_t cast_to_short(char* buffer2, bool swap) {
  int16_t a;
  if (swap) {
    a = (int16_t) (buffer2[0] << 8 | buffer2[1]);
  } else {
    a =  (int16_t) (buffer2[1] << 8 | buffer2[0]);
  }
  return a;
}





#endif
