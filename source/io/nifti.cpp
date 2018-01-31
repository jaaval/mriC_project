
#include "nifti.h"
#include <iostream>
#include <string.h>


Nifti::Nifti(std::string fileName) {
  header = nifti_2_header();
  this->fileName = fileName;
  std::ifstream ifs (fileName, std::ifstream::binary);
  if (ifs) {
    checkDataType(ifs);
    if (type == 1) {
      readHeaderType1(ifs, swap);
    } else if (type == 2) {
      std::cout << "have not implemented nifti2 reading yet" << std::endl;
    }
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
  if (!header_read) {
    std::cout << "here be error" << std::endl;
  }
  int hlen = header.sizeof_hdr;
  ifs.seekg(hlen); // jump at the end of header

}


/*
 * read nifti1 header to nifti2 header template
*/
void Nifti::readHeaderType1(std::ifstream& ifs, bool swap) {
  char* buffer4 = new char[4];
  char* buffer2 = new char[2];

  ifs.get(buffer4, 5);
  header.sizeof_hdr = cast_to_int(buffer4, swap);
  if (header.sizeof_hdr != 348) {
    // The end of the world!
    std::cout << "shit" << std::endl;
  }

  ifs.ignore(10);//data_type

  ifs.ignore(18);//whatever

  ifs.ignore(4);//extents

  ifs.ignore(2);//extents

  ifs.ignore(1);//regular

  ifs.ignore(1);//dim_info

  for (int i = 0; i < 8; i++) {
      ifs.get(buffer2, 3);
      header.dim[i] = cast_to_short(buffer2, swap);
  }

  ifs.get(buffer4, 5);
  header.intent_p1 = cast_to_float(buffer4, swap);
  ifs.get(buffer4, 5);
  header.intent_p2 = cast_to_float(buffer4, swap);
  ifs.get(buffer4, 5);
  header.intent_p3 = cast_to_float(buffer4, swap);

  ifs.get(buffer2, 3);
  header.intent_code = cast_to_short(buffer2, swap);

  ifs.get(buffer2, 3);
  header.datatype = cast_to_short(buffer2, swap);

  ifs.get(buffer2, 3);
  header.bitpix = cast_to_short(buffer2, swap);

  ifs.get(buffer2, 3);
  header.slice_start = cast_to_short(buffer2, swap);

  for (int i = 0; i < 8; i++) {
    ifs.get(buffer4, 5);
    header.pixdim[i] = cast_to_float(buffer4, swap);
  }

  ifs.get(buffer4, 5);
  header.vox_offset = (int64_t)cast_to_float(buffer4, swap); //old was float. now long. figure out

  ifs.get(buffer4, 5);
  header.scl_slope = cast_to_float(buffer4, swap);

  ifs.get(buffer4, 5);
  header.scl_inter = cast_to_float(buffer4, swap);

  ifs.get(buffer2, 3);
  header.slice_end = cast_to_short(buffer2, swap);

  char a;
  ifs.get(a);
  header.slice_code = (int)a; // figure this out

  ifs.get(a);
  header.xyzt_units = (int)a; // figure this out

  ifs.get(buffer4, 5);
  header.cal_max = cast_to_float(buffer4, swap);

  ifs.get(buffer4, 5);
  header.cal_min = cast_to_float(buffer4, swap);

  ifs.get(buffer4, 5);
  header.slice_duration = cast_to_float(buffer4, swap);

  ifs.get(buffer4, 5);
  header.toffset = cast_to_float(buffer4, swap);

  ifs.ignore(4); // glmax

  ifs.ignore(4); // glmin

  ifs.get(header.descrip, 81);

  ifs.get(header.aux_file, 25);

  ifs.get(buffer2, 3);
  header.qform_code = cast_to_short(buffer2, swap);

  ifs.get(buffer2, 3);
  header.sform_code = cast_to_short(buffer2, swap);


  ifs.get(buffer4, 5);
  header.quatern_b = cast_to_float(buffer4, swap);
  ifs.get(buffer4, 5);
  header.quatern_c = cast_to_float(buffer4, swap);
  ifs.get(buffer4, 5);
  header.quatern_d = cast_to_float(buffer4, swap);

  ifs.get(buffer4, 5);
  header.qoffset_x = cast_to_float(buffer4, swap);
  ifs.get(buffer4, 5);
  header.qoffset_y = cast_to_float(buffer4, swap);
  ifs.get(buffer4, 5);
  header.qoffset_z = cast_to_float(buffer4, swap);


  for (int i = 0; i < 4; i++) {
    ifs.get(buffer4, 5);
    header.srow_x[i] = cast_to_float(buffer4, swap);
  }

  for (int i = 0; i < 4; i++) {
    ifs.get(buffer4, 5);
    header.srow_y[i] = cast_to_float(buffer4, swap);
  }

  for (int i = 0; i < 4; i++) {
    ifs.get(buffer4, 5);
    header.srow_z[i] = cast_to_float(buffer4, swap);
  }

  ifs.get(header.intent_name, 17);

  ifs.get(header.magic, 5);
  if (!strcmp(header.magic, "nil\0")) {
    std::cout << "magic not valid nifti1 identifier" << std::endl;
  }

  if (ifs.tellg() != 348) {
    //well shit
    std::cout << "shit 2 " << ifs.tellg() << std::endl;

  }

  header_read = true;
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
