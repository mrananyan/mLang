/*
$Author = Sargis Ananyan;
$Corp = RedM Inc;
$Web = https://redm.pro/;
$Lincese = BSD 3;
$Name = mLang;
$Description = A programming language for web programming.;
*/

#pragma once

#include <climits>

#include "mlang_core.h"
#include "string_functions.h"

bool mb_UTF8_check (const char *s);

bool f$mb_check_encoding (const string &str, const string &encoding = CP1251);

int f$mb_strlen (const string &str, const string &encoding = CP1251);

string f$mb_strtolower (const string &str, const string &encoding = CP1251);

string f$mb_strtoupper (const string &str, const string &encoding = CP1251);

OrFalse <int> f$mb_strpos (const string &haystack, const string &needle, int offset = 0, const string &encoding = CP1251);

OrFalse <int> f$mb_stripos (const string &haystack, const string &needle, int offset = 0, const string &encoding = CP1251);

string f$mb_substr (const string &str, int start, int length = INT_MAX, const string &encoding = CP1251);
