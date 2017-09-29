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
#include "utils.h"
#include "data_ptr.h"

string get_full_path (const string &file_name);

class SrcFile {
public:
  int id;
  string prefix;
  string text, file_name, short_file_name;
  string unified_file_name;
  bool loaded;
  bool is_required;

  string main_func_name;
  FunctionPtr main_function;
  FunctionPtr req_id;

  vector <string_ref> lines;

  SrcFile();
  SrcFile (const string &file_name, const string &short_file_name);
  void add_prefix (const string &s);
  bool load();

  string_ref get_line (int id);
};

struct Line {
  int begin_pos, end_pos;
  SrcFilePtr file;
  bool brk;
  set <int> line_ids;//????
  Line () : begin_pos (0), end_pos (-1), file (), brk(false), line_ids() {
  }
  explicit Line (int begin_pos)
    : begin_pos (begin_pos), end_pos (-1), file(), brk(false), line_ids() {
    }
};

class WriterData {
  private:
    vector <Line> lines;
    string text;
    unsigned long long crc;

    void write_code (FILE *dest_file, const Line &line);
    template <class T> void dump (FILE *dest_file, T begin, T end, SrcFilePtr file);
  public:
    string file_name;
    string subdir;

    WriterData();

    void append (const char *begin, size_t length);
    void append (size_t n, char c);
    void begin_line();
    void end_line();
    void brk();
    void add_location (SrcFilePtr file, int line);

    unsigned long long calc_crc();
    void dump (FILE *dest_file);

    void swap (WriterData &other);
};

class WriterCallbackBase {
  public:
    virtual ~WriterCallbackBase(){}
    virtual void on_end_write (WriterData *data) = 0;
};

class Writer {
  private:
    typedef enum {w_stopped, w_running} state_t;

    state_t state;

    WriterData data;

    WriterCallbackBase *callback;

    int indent_level;
    bool need_indent;

    int lock_comments_cnt;

    void write_indent(void);
    void append (const char *begin, size_t length);
    void append (size_t n, char c);
    void begin_line();
    void end_line();

  public:
    Writer();
    ~Writer();

    void set_file_name (const string &file_name, const string &subdir = "");
    void set_callback (WriterCallbackBase *new_callback);

    void begin_write();
    void end_write();

    void operator() (const string &s);
    void operator() (const char *s);
    void operator() (const string_ref &s);
    void indent(int diff);
    void new_line();
    void brk();
    void operator() (SrcFilePtr file_id, int line_num);
    void lock_comments();
    void unlock_comments();
    bool is_comments_locked();

  private:
    DISALLOW_COPY_AND_ASSIGN (Writer);
};
