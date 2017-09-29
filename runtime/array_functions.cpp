/*
$Author = Sargis Ananyan;
$Corp = RedM Inc;
$Web = https://redm.pro/;
$Lincese = BSD 3;
$Name = mLang;
$Description = A programming language for web programming.;
*/

#define _FILE_OFFSET_BITS 64

#include "array_functions.h"

array <string> explode (char delimiter, const string &str, int limit) {
  array <string> res (array_size (limit < 10 ? limit : 1, 0, true));

  int s_len = str.size();
  const char *s = str.c_str();
  int prev = 0;

  if (limit > 1) {
    for (int i = 0; i < s_len; ) {
      if (delimiter == s[i]) {
        res.push_back (string (s + prev, i - prev));
        i++;
        prev = i;
        limit--;
        if (limit == 1) {
          break;
        }
      } else {
        i++;
      }
    }
  }
  res.push_back (string (s + prev, s_len - prev));

  return res;
}

array <string> f$explode (const string &delimiter, const string &str, int limit) {
  if (limit <= 1) {
    php_warning ("Wrong limit %d specified in function explode", limit);
    limit = 1;
  }
  int d_len = delimiter.size();
  if (d_len == 1) {
    return explode (delimiter[0], str, limit);
  }
  if (d_len == 0) {
    php_warning ("Empty delimiter in function explode");
    return array <string> ();
  }

  array <string> res (array_size (limit < 10 ? limit : 1, 0, true));

  const char *d = delimiter.c_str();
  const char *s = str.c_str();
  int s_len = str.size();
  int prev = 0;

  if (limit > 1) {
    for (int i = 0; i < s_len; ) {
      int j;
      for (j = 0; j < d_len && d[j] == s[i + j]; j++) {
      }
      if (j == d_len) {
        res.push_back (string (s + prev, i - prev));
        i += d_len;
        prev = i;
        limit--;
        if (limit == 1) {
          break;
        }
      } else {
        i++;
      }
    }
  }
  res.push_back (string (s + prev, s_len - prev));

  return res;
}


array <array <var>::key_type> f$array_flip (const array <var> &a) {
  array <array <var>::key_type> result;

  for (array <var>::const_iterator it = a.begin(); it != a.end(); ++it) {
    const var &value = it.get_value();
    if (value.is_int() || value.is_string()) {
      result.set_value (value, it.get_key());
    } else {
      php_warning ("Unsupported type of array element \"%s\" in function array_flip", value.get_type_c_str());
    }
  }

  return result;
}

array <array <int>::key_type> f$array_flip (const array <int> &a) {
  array <array <int>::key_type> result;

  for (array <int>::const_iterator it = a.begin(); it != a.end(); ++it) {
    result.set_value (it.get_value(), it.get_key());
  }

  return result;
}

array <array <string>::key_type> f$array_flip (const array <string> &a) {
  array <array <string>::key_type> result;

  for (array <string>::const_iterator it = a.begin(); it != a.end(); ++it) {
    result.set_value (it.get_value(), it.get_key());
  }

  return result;
}


int f$array_sum (const array <int> &a) {
  int result = 0;

  for (array <int>::const_iterator it = a.begin(); it != a.end(); ++it) {
    result += it.get_value();
  }

  return result;
}

double f$array_sum (const array <double> &a) {
  double result = 0;

  for (array <double>::const_iterator it = a.begin(); it != a.end(); ++it) {
    result += it.get_value();
  }

  return result;
}

double f$array_sum (const array <var> &a) {
  double result = 0;

  for (array <var>::const_iterator it = a.begin(); it != a.end(); ++it) {
    result += it.get_value().to_float();
  }

  return result;
}

array <int> f$range (int from, int to) {
  if (from < to) {
    array <int> res (array_size (to - from + 1, 0, true));
    for (int i = from; i <= to; i++) {
      res.set_value (i - from, i);
    }
    return res;
  } else {
    array <int> res (array_size (from - to + 1, 0, true));
    for (int i = from; i >= to; i--) {
      res.set_value (from - i, i);
    }
    return res;
  }
}

array <string> f$range (const string &from_s, const string &to_s) {
  if (from_s.empty() || to_s.empty()) {
    php_warning ("Wrong parameters \"%s\" and \"%s\" for function range", from_s.c_str(), to_s.c_str());
    return array <string>();
  }
  int from = (unsigned char)from_s[0];
  int to = (unsigned char)to_s[0];
  if (from < to) {
    array <string> res (array_size (to - from + 1, 0, true));
    for (int i = from; i <= to; i++) {
      res.set_value (i - from, f$chr (i));
    }
    return res;
  } else {
    array <string> res (array_size (from - to + 1, 0, true));
    for (int i = from; i >= to; i--) {
      res.set_value (from - i, f$chr (i));
    }
    return res;
  }
}
