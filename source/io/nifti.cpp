
#include "nifti.h"


Nifti::Nifti(std::string fileName) {

}

Nifti::readHeader(ifstream& ifs) {
  char buffer4[4];
  char buffer2[2];

  ifs.get(buffer4, 4);
  this->header.sizeof_hdr = cast_to_int(buffer4);
  if (this->header.sizeof_hdr != 348) {
    // The end of the world!
  }
  ifs.get(this->header.data_type, 10);
  ifs.get(this->header.db_name, 18);

  ifs.get(buffer4, 4);
  this->header.extents = cast_to_int(buffer4);

  ifs.get(buffer2, 2);
  this->header.session_error = cast_to_short(buffer2);

  ifs.get(this->header.regular);

  ifs.get(this->header.dim_info);

  for (int i = 0; i < 8; i++) {
      ifs.get(buffer2, 2);
      this->header.dim[i] = cast_to_short(buffer2);
  }

  for (int i = 0; i < 3; i++) {
    ifs.get(buffer4, 4);
    this->header.intent[i] = cast_to_float(buffer4);
  }

  ifs.get(buffer2, 2);
  this->header.intent_code[i] = cast_to_short(buffer2);

  ifs.get(buffer2, 2);
  this->header.datatype[i] = cast_to_short(buffer2);

  ifs.get(buffer2, 2);
  this->header.bitpix[i] = cast_to_short(buffer2);

  ifs.get(buffer2, 2);
  this->header.slice_start[i] = cast_to_short(buffer2);

  for (int i = 0; i < 8; i++) {
    ifs.get(buffer4, 4);
    this->header.pixdim[i] = cast_to_float(buffer4);
  }

  ifs.get(buffer4, 4);
  this->header.vox_offset = cast_to_float(buffer4);

  ifs.get(buffer4, 4);
  this->header.slc_slope = cast_to_float(buffer4);

  ifs.get(buffer4, 4);
  this->header.slc_inter = cast_to_float(buffer4);

  ifs.get(buffer2, 2);
  this->header.slice_end[i] = cast_to_short(buffer2);

  ifs.get(this->header.slice_code);

  ifs.get(this->header.xyzt_units);

  ifs.get(buffer4, 4);
  this->header.cal_max = cast_to_float(buffer4);

  ifs.get(buffer4, 4);
  this->header.cal_min = cast_to_float(buffer4);

  ifs.get(buffer4, 4);
  this->header.slice_duration = cast_to_float(buffer4);

  ifs.get(buffer4, 4);
  this->header.toffset = cast_to_float(buffer4);

  ifs.get(buffer4, 4);
  this->header.glmax = cast_to_int(buffer4);

  ifs.get(buffer4, 4);
  this->header.glmin = cast_to_int(buffer4);

  ifs.get(this->header.descrip, 80);

  ifs.get(this->header.aux_file, 24);

  ifs.get(buffer2, 2);
  this->header.qform_code[i] = cast_to_short(buffer2);

  ifs.get(buffer2, 2);
  this->header.sform_code[i] = cast_to_short(buffer2);

  for (int i = 0; i < 3; i++) {
    ifs.get(buffer4, 4);
    this->header.quatern[i] = cast_to_float(buffer4);
  }

  for (int i = 0; i < 3; i++) {
    ifs.get(buffer4, 4);
    this->header.qoffset[i] = cast_to_float(buffer4);
  }

  for (int i = 0; i < 4; i++) {
    ifs.get(buffer4, 4);
    this->header.srow_x[i] = cast_to_float(buffer4);
  }

  for (int i = 0; i < 4; i++) {
    ifs.get(buffer4, 4);
    this->header.srow_y[i] = cast_to_float(buffer4);
  }

  for (int i = 0; i < 4; i++) {
    ifs.get(buffer4, 4);
    this->header.srow_z[i] = cast_to_float(buffer4);
  }

  ifs.get(this->header.intent_name, 16);

  ifs.get(this->header.magic, 4);

  if (ifs.tellg != 348) {
    //well shit
  }
}
