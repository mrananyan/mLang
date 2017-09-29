/*
$Author = Sargis Ananyan;
$Corp = RedM Inc;
$Web = https://redm.pro/;
$Lincese = BSD 3;
$Name = mLang;
$Description = A programming language for web programming.;
*/

#pragma once


//C interface
#ifdef __cplusplus
#include <cstring>
extern "C" {
#else
#include <string.h>
#endif


/** http_query_data **/
typedef struct {
  char *uri, *get, *headers, *post, *request_method;
  int uri_len, get_len, headers_len, post_len, request_method_len;
  int keep_alive;
  unsigned int ip;
  unsigned int port;
} http_query_data;

http_query_data *http_query_data_create (const char *qUri, int qUriLen, const char *qGet, int qGetLen, const char *qHeaders,
  int qHeadersLen, const char *qPost, int qPostLen, const char *request_method, int keep_alive, unsigned int ip, unsigned int port);
void http_query_data_free (http_query_data *d);

/** rpc_query_data **/
typedef struct {
  int *data, len;

  long long req_id;

  /** PID **/
  unsigned ip;
  short port;
  short pid;
  int utime;
} rpc_query_data;

rpc_query_data *rpc_query_data_create (int *data, int len, long long req_id, unsigned int ip, short port, short pid, int utime);
void rpc_query_data_free (rpc_query_data *d);

/** php_query_data **/
typedef struct {
  http_query_data *http_data;
  rpc_query_data *rpc_data;
} php_query_data;

php_query_data *php_query_data_create (http_query_data *http_data, rpc_query_data *rpc_data);
void php_query_data_free (php_query_data *d);


/** script_t **/
typedef struct {
  void (*run) (php_query_data *, void *mem, size_t mem_size);
  void (*clear) (void);
} script_t;

script_t *get_script (const char *name);
void set_script (const char *name, void (*run)(php_query_data *, void *, size_t), void (*clear) (void));

/** script result **/

typedef struct {
  int return_code, exit_code;
  const char *headers, *body;
  int headers_len, body_len;
} script_result;

#ifdef __cplusplus
}
#endif
