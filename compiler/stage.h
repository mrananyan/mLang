/*
$Author = Sargis Ananyan;
$Corp = RedM Inc;
$Web = https://redm.pro/;
$Lincese = BSD 3;
$Name = mLang;
$Description = A programming language for web programming.;
*/

#pragma once
#define compiler_assert(x, y, level)  ({\
  int mlang_error_res__ = 0;\
  if (!(x)) {\
    mlang_error_res__ = 1;\
    on_compilation_error (#x, __FILE__, __LINE__, y, level);\
  }\
  mlang_error_res__;\
})

#define mlang_warning(y)  compiler_assert (0, y, WRN_ASSERT_LEVEL)
#define mlang_error(x, y) compiler_assert (x, y, CE_ASSERT_LEVEL)
#define mlang_error_act(x, y, act) if (mlang_error (x, y)) act;
#define mlang_error_return(x, y) mlang_error_act (x, y, return)
#define mlang_assert(x) compiler_assert (x, "", FATAL_ASSERT_LEVEL)
#define mlang_fail() mlang_assert (0); _exit(1);

typedef enum {WRN_ASSERT_LEVEL, CE_ASSERT_LEVEL, FATAL_ASSERT_LEVEL} AssertLevelT;

void on_compilation_error (const char *description, const char *file_name, int line_number,
  const char *full_description, AssertLevelT assert_level);

#include "location.h"
namespace stage {
  struct StageInfo {
    string name;
    Location location;
    bool global_error_flag;
    bool error_flag;
    StageInfo() :
      name(),
      location(),
      global_error_flag (false),
      error_flag (false) {
    }
  };

  StageInfo *get_stage_info_ptr();

  void error();
  bool has_error();
  bool has_global_error();
  void die_if_global_errors();

  Location *get_location_ptr();
  const Location &get_location();
  void set_location (const Location &new_location);

  void print (FILE *f);
  void print_file (FILE *f);
  void print_function (FILE *f);
  void print_line (FILE *f);
  void print_comment (FILE *f);
  void get_function_history (stringstream &ss, FunctionPtr function);
  string get_function_history();

  void set_name (const string &name);
  const string &get_name();

  void set_file (SrcFilePtr file);
  void set_function (FunctionPtr function);
  void set_line (int line);
  SrcFilePtr get_file (void);
  FunctionPtr get_function (void);
  int get_line (void);

  const string &get_file_name();
  const string &get_function_name();
  string to_str (const Location &new_location);
}
