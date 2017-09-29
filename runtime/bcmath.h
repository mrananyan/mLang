/*
$Author = Sargis Ananyan;
$Corp = RedM Inc;
$Web = https://redm.pro/;
$Lincese = BSD 3;
$Name = mLang;
$Description = A programming language for web programming.;
*/

#pragma once

#include "mlang_core.h"

void f$bcscale (int scale);

string f$bcdiv (const string &lhs, const string &rhs, int scale = INT_MIN);

string f$bcmod (const string &lhs, const string &rhs);

string f$bcpow (const string &lhs, const string &rhs);

string f$bcadd (const string &lhs, const string &rhs, int scale = INT_MIN);

string f$bcsub (const string &lhs, const string &rhs, int scale = INT_MIN);

string f$bcmul (const string &lhs, const string &rhs, int scale = INT_MIN);

int f$bccomp (const string &lhs, const string &rhs, int scale = INT_MIN);

void bcmath_init_static (void);
