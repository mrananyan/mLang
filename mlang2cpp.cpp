/*
$Author = Sargis Ananyan;
$Corp = RedM Inc;
$Web = https://redm.pro/;
$Lincese = BSD 3;
$Name = mLang;
$Description = A programming language for web programming.;
*/

#include "compiler/compiler.h"
#include <pwd.h>

/***
 * Kitten compiler for PHP interface
 **/
void usage (void) {
  printf ("This is for internal usage only! Use mlang.py\n"
          "mlang2cpp. Convert php code into C++ code\n"
          "-a\tUse safe integer arithmetic\n"
          "-b<dir>\tBase directory. Use it when compiling the same code from different directories\n"
          "-d<dir>\tDestination directory\n"
          "-f<file>\tInternal file with library headers and e.t.c.\n"
          "-i<file>\tIndex for faster compilations\n"
          "-I<dir>\tDirectory where php files will be searched\n"
          "-j<thread_cnt>\tUse multiple threads\n"
          "-r\tSplit output into multiple directories\n"
          "-v\tVerbosity\n");
}


static void runtime_handler (const int sig) {
  fprintf (stderr, "%s caught, terminating program\n", sig == SIGSEGV ? "SIGSEGV" : "SIGABRT");
  dl_print_backtrace();
  dl_print_backtrace_gdb();
  _exit (EXIT_FAILURE);
}

static void set_debug_handlers (void) {
//  signal (SIGFPE, dl_runtime_handler);
  dl_signal (SIGSEGV, runtime_handler);
  dl_signal (SIGABRT, runtime_handler);
}

int main (int argc, char *argv[]) {
  set_debug_handlers();
  int i;

  int verbosity = 0;
  struct passwd *user_pwd = getpwuid (getuid());
  dl_passert (user_pwd != NULL, "Failed to get user name");
  char *user = user_pwd->pw_name;
  if (user != NULL && (!strcmp (user, "levlam") || !strcmp (user, "arseny30"))) {
    verbosity = 3;
  }

  CompilerArgs *args = new CompilerArgs();
  while ((i = getopt (argc, argv, "arvb:f:d:i:j:I:")) != -1) {
    switch (i) {
    case 'a':
      args->set_use_safe_integer_arithmetic (true);
      break;
    case 'f':
      args->set_functions_txt (optarg);
      break;
    case 'I':
      args->add_include (optarg);
      break;
    case 'd':
      args->set_dest_dir (optarg);
      break;
    case 'i':
      args->set_index_path (optarg);
      break;
    case 'r':
      args->set_use_subdirs (true);
      break;
    case 'b':
      args->set_base_dir (optarg);
      break;
    case 'v':
      verbosity++;
      break;
    case 'j':
      args->set_threads_number (atoi (optarg));
      break;
    default:
      printf ("Unknown option '%c'", (char)i);
      usage();
      exit (1);
    }
  }
  args->set_verbosity (verbosity);


  if (optind >= argc) {
    usage();
    return 2;
  }

  while (optind < argc) {
    args->add_main_file (argv[optind]);
    optind++;
  }

  compiler_execute (args);

  return 0;
}
