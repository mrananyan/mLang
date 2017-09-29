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

template <typename T> struct Trie {
  Trie *next[256];
  int has_val;
  T val;

  Trie ();

  void add (const string &s, const T &val);
  T *get_deepest (const char *s);
  void clear();
  ~Trie();

private:
  DISALLOW_COPY_AND_ASSIGN (Trie);
};


#include "trie.hpp"
