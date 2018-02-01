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
  ~Nifti() {delete dataVolume;}

  nifti_2_header& getHeader() {
    return header;
  }

  Volume* getDataPointer() { return dataVolume; }

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

  void readHeaderType1(std::ifstream& ifs);
  void readHeaderType2(std::ifstream& ifs);
  void readData(std::ifstream& ifs);
  void checkDataType(std::ifstream& ifs);

  double scale(double in) {
    if (header.scl_slope != 0) {
      in *= header.scl_slope;
    }
    in += header.scl_inter;
    return in;
  }

  nifti_2_header header;
  int type; // nifti1 or 2. the header struct used internally is the same
  bool swap;
  std::string fileName;
  Volume* dataVolume; // pointer to actual data container class

  bool header_read;

};


// cast functions for binary data reading

int cast_to_int(char* buffer4, bool swap);

float cast_to_float(char* buffer4, bool swap);

double cast_to_double(char* buffer8, bool swap);

int16_t cast_to_short(char* buffer2, bool swap);


#endif
