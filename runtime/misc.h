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


OrFalse <string> f$iconv (const string &input_encoding, const string &output_encoding, const string &input_str);


void f$sleep (const int &seconds);

void f$usleep (const int &micro_seconds);


int f$posix_getpid (void);


string f$serialize (const var &v);

var f$unserialize (const string &v);

string f$json_encode (const var &v, bool simple_encode = false);

var f$json_decode (const string &v, bool assoc = false);

string f$print_r (const var &v, bool buffered = false);

void f$var_dump (const var &v);


/** For local usage only **/
int f$system (const string &query);
