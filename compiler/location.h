/*
$Author = Sargis Ananyan;
$Corp = RedM Inc;
$Web = https://redm.pro/;
$Lincese = BSD 3;
$Name = mLang;
$Description = A programming language for web programming.;
*/

#pragma once
#include "data_ptr.h"
class Location {
public:
  SrcFilePtr file;
  FunctionPtr function;
  int line;

  Location();

  void set_file (SrcFilePtr file);
  void set_function (FunctionPtr function);
  void set_line (int line);
  SrcFilePtr get_file() const;
  FunctionPtr get_function() const;
  int get_line() const;
};
