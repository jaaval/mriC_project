
#include "nifti.h"
#include <iostream>


Nifti::Nifti(std::string fileName) {
  header1 = nifti_1_header();
  header2 = nifti_2_header();
  this->fileName = fileName;
  std::ifstream ifs (fileName, std::ifstream::binary);
  if (ifs) {
    checkDataType(ifs);
    readHeaderType1(ifs, swap);
    ifs.close();
  } else {
    std::cout << "shit 3" << std::endl;
  }
}


void Nifti::checkDataType(std::ifstream& ifs) {
  char* buffer4 = new char[4];
  ifs.get(buffer4, 5);
  int a = cast_to_int(buffer4, false);
  if (a == 348) {
    type = 1;
    swap = false;
  } else if (a == 540) {
    type = 2;
    swap = false;
  } else {
    a = cast_to_int(buffer4, true);
    if (a == 348) {
      type = 1;
      swap = true;
    } else if (a == 540) {
      type = 2;
      swap = true;
    } else {
      std::cout << "fuck this" << std::endl;
      // ERROR!
    }
  }

  delete[] buffer4;
  ifs.seekg(0, ifs.beg);
}


void Nifti::readFile(std::string fileName) {

}


void Nifti::readData(std::ifstream& ifs) {

}


void Nifti::readHeaderType1(std::ifstream& ifs, bool swap) {
  char* buffer4 = new char[4];
  char* buffer2 = new char[2];

  ifs.get(buffer4, 5);
  header1.sizeof_hdr = cast_to_int(buffer4, swap);
  if (header1.sizeof_hdr != 348) {
    // The end of the world!
    std::cout << "shit" << std::endl;
  }

  ifs.get(header1.data_type, 11);

  ifs.get(header1.db_name, 19);

  ifs.get(buffer4, 5);
  header1.extents = cast_to_int(buffer4, swap);

  ifs.get(buffer2, 3);
  header1.session_error = cast_to_short(buffer2, swap);

  ifs.get(header1.regular);

  ifs.get(header1.dim_info);

  for (int i = 0; i < 8; i++) {
      ifs.get(buffer2, 3);
      header1.dim[i] = cast_to_short(buffer2, swap);
  }

  ifs.get(buffer4, 5);
  header1.intent_p1 = cast_to_float(buffer4, swap);
  ifs.get(buffer4, 5);
  header1.intent_p2 = cast_to_float(buffer4, swap);
  ifs.get(buffer4, 5);
  header1.intent_p3 = cast_to_float(buffer4, swap);

  ifs.get(buffer2, 3);
  header1.intent_code = cast_to_short(buffer2, swap);

  ifs.get(buffer2, 3);
  header1.datatype = cast_to_short(buffer2, swap);

  ifs.get(buffer2, 3);
  header1.bitpix = cast_to_short(buffer2, swap);

  ifs.get(buffer2, 3);
  header1.slice_start = cast_to_short(buffer2, swap);

  for (int i = 0; i < 8; i++) {
    ifs.get(buffer4, 5);
    header1.pixdim[i] = cast_to_float(buffer4, swap);
  }

  ifs.get(buffer4, 5);
  header1.vox_offset = cast_to_float(buffer4, swap);

  ifs.get(buffer4, 5);
  header1.scl_slope = cast_to_float(buffer4, swap);

  ifs.get(buffer4, 5);
  header1.scl_inter = cast_to_float(buffer4, swap);

  ifs.get(buffer2, 3);
  header1.slice_end = cast_to_short(buffer2, swap);

  ifs.get(header1.slice_code);

  ifs.get(header1.xyzt_units);

  ifs.get(buffer4, 5);
  header1.cal_max = cast_to_float(buffer4, swap);

  ifs.get(buffer4, 5);
  header1.cal_min = cast_to_float(buffer4, swap);

  ifs.get(buffer4, 5);
  header1.slice_duration = cast_to_float(buffer4, swap);

  ifs.get(buffer4, 5);
  header1.toffset = cast_to_float(buffer4, swap);

  ifs.get(buffer4, 5);
  header1.glmax = cast_to_int(buffer4, swap);

  ifs.get(buffer4, 5);
  header1.glmin = cast_to_int(buffer4, swap);

  ifs.get(header1.descrip, 81);

  ifs.get(header1.aux_file, 25);

  ifs.get(buffer2, 3);
  header1.qform_code = cast_to_short(buffer2, swap);

  ifs.get(buffer2, 3);
  header1.sform_code = cast_to_short(buffer2, swap);


  ifs.get(buffer4, 5);
  header1.quatern_b = cast_to_float(buffer4, swap);
  ifs.get(buffer4, 5);
  header1.quatern_c = cast_to_float(buffer4, swap);
  ifs.get(buffer4, 5);
  header1.quatern_d = cast_to_float(buffer4, swap);

  ifs.get(buffer4, 5);
  header1.qoffset_x = cast_to_float(buffer4, swap);
  ifs.get(buffer4, 5);
  header1.qoffset_y = cast_to_float(buffer4, swap);
  ifs.get(buffer4, 5);
  header1.qoffset_z = cast_to_float(buffer4, swap);


  for (int i = 0; i < 4; i++) {
    ifs.get(buffer4, 5);
    header1.srow_x[i] = cast_to_float(buffer4, swap);
  }

  for (int i = 0; i < 4; i++) {
    ifs.get(buffer4, 5);
    header1.srow_y[i] = cast_to_float(buffer4, swap);
  }

  for (int i = 0; i < 4; i++) {
    ifs.get(buffer4, 5);
    header1.srow_z[i] = cast_to_float(buffer4, swap);
  }

  ifs.get(header1.intent_name, 17);

  ifs.get(header1.magic, 5);

  if (ifs.tellg() != 348) {
    //well shit
    std::cout << "shit 2 " << ifs.tellg() << std::endl;

  }

  delete[] buffer2;
  delete[] buffer4;
}


int main() {
  std::string filename = "fPhantom-0005-00001-000001-01.nii";
  Nifti ni = Nifti(filename);
  std::cout << ni.getHeader().sizeof_hdr << std::endl;

  for (int i = 0; i < 8; i++) {
    std::cout << ni.getHeader().dim[i] << std::endl;
  }
  std::cout << ni.getHeader().descrip << std::endl;


}
