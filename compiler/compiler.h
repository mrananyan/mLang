/*
$Author = Sargis Ananyan;
$Corp = RedM Inc;
$Web = https://redm.pro/;
$Lincese = BSD 3;
$Name = mLang;
$Description = A programming language for web programming.;
*/

#pragma once
#include "../common.h"
class Compiler;

class CompilerArgs {
public:
  vector <string> include_dirs;
  vector <string> main_file_names;
  string functions_txt;
  string dest_dir;
  string base_dir;
  string index_path;
  int verbosity;
  bool use_subdirs;
  bool use_safe_integer_arithmetic;
  int threads_number;
  CompilerArgs();
  void set_use_safe_integer_arithmetic (bool new_use_safe_integer_arithmetic);
  void add_include (const string &s);
  void add_main_file (const string &s);
  void set_functions_txt (const string &s);
  void set_dest_dir (const string &s);
  void set_base_dir (const string &s);
  void set_index_path (const string &index_path);
  void set_use_subdirs (bool new_use_subdirs);
  void set_threads_number (int new_threads_number);
  void set_verbosity (int new_verbosity);
};


void compiler_execute (CompilerArgs *args);
