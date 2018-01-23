


#include <fstream>
#include <string>


class Nifti {
public:

  Nifti(const std::string fileName);

  NiftiHeader& getHeader() const {
    return header;
  }

  size_t dimx() const {
    return (size_t) header.dim[0];
  }
  size_t dimy() const {
    return (size_t) header.dim[1];
  }
  size_t dimz() const {
    return (size_t) header.dim[2];
  }
  size_t dimt() const {
    return (size_t) header.dim[3];
  }

  void readFile(std::string fileName);


private:

  void readHeader(ifstream& ifs);
  void readData(ifstream& ifs, size_t bytes); //TODO think how to actually read the data

  NiftiHeader header;
  bool dataLoaded;
  std::string fileName;

};

struct NiftiHeader {
  int sizeof_hdr; // header size == 348
  char data_type[10]; // not used
  char db_name[18]; // not used
  int extents; // not used
  short session_error; // not used
  char regular; // not used
  char dim_info; // encodings for directions
  short dim[8]; // data dimensions
  float intent[3]; // intent parameters p1,p2,p3
  short intent_code; // nifti intent
  short datatype;
  short bitpix; // number of bits / voxel
  short slice_start; // first slice index
  float pixdim[8]; // grid spacings (unit per dimension)
  float vox_offset; // offset ??
  float scl_slope; // data scaling, slope
  float scl_inter; // data scaling, offset  -> slope*x+inter
  short slice_end; // last slice index
  char slice_code; //slice timing order?
  char xyzt_units; // units of pixdim[1:4]
  float cal_max; // max disp intensity
  float cal_min; // min disp intensity
  float slice_duration; // time for one slice (TR?)
  float toffset; // time axis shift
  int glmax; // not used
  int glmin; // not used
  char descrip[80]; // description text
  char aux_file[24]; // aux file name
  short qform_code; // use the quaternion fields
  short sform_code; // use the affine fields
  float quatern[3]; // quaternion bcd parameters
  float qoffset[3]; // quaternion offsets
  float srow_x[4]; // 1st row affine transform
  float srow_y[4]; // 2st row affine transform
  float srow_z[4]; // 3st row affine transform
  char intent_name[16]; // name or meaning of the data
  char magic[4]; //magic string ?
};

class Volume {

public:

private:

};


// cast functions for binary data reading

int cast_to_int(char[4] buffer4) {
  return (int) (buffer4[0] << 24 | buffer4[1] << 16 | buffer4[2] << 8 | buffer4[3]);
}

float cast_to_float(char[4] buffer4) {
  return (float) (buffer4[0] << 24 | buffer4[1] << 16 | buffer4[2] << 8 | buffer4[3]);
}

short cast_to_short(char[2] buffer2) {
  return (short) (buffer2[0] << 8 | buffer2[1]);
}
