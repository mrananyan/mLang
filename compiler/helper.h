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
#include "trie.h"

template <typename T> struct Helper {
  Trie <T*> trie;
  T* on_fail;

  explicit Helper (T* on_fail);
  void add_rule (const string &rule_template, T *val_, bool need_expand = true);
  void add_simple_rule (const string &rule_template, T *val);
  T* get_default();
  T* get_help (const char *s);

private:
  DISALLOW_COPY_AND_ASSIGN (Helper);
};


#include "helper.hpp"
