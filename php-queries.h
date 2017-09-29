/*
$Author = Sargis Ananyan;
$Corp = RedM Inc;
$Web = https://redm.pro/;
$Lincese = BSD 3;
$Name = mLang;
$Description = A programming language for web programming.;
*/

#pragma once
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#pragma pack(push,4)

#ifdef __cplusplus
extern "C" {
#endif

void qmem_init (void);
void *qmem_malloc (size_t n);
void qmem_free_ptrs (void);
void qmem_clear (void);

extern long long qmem_generation;

const char* qmem_pstr (char const *msg, ...) __attribute__ ((format (printf, 1, 2)));

typedef struct {
  int len, buf_len;
  char *buf;
} str_buf_t;

typedef struct chain_t_tmp chain_t;
struct chain_t_tmp {
  chain_t *next, *prev;
  char *buf;
  int len;
};

#define PHPQ_X2 0x12340000
#define PHPQ_RPC_ANSWER 0x43210000
#define PHPQ_RPC_MESSAGE 0x31240000
#define PHPQ_CONNECT 0x2f2d0000
#define PHPQ_NETQ 0x3d780000
#define PHPQ_CREATE_QUEUE 0x723d0000
#define PHPQ_QUEUE_EMPTY 0x9fa20000
#define PHPQ_HTTP_LOAD_POST 0x5ac20000
#define NETQ_PACKET 1234

#define PNETF_IMMEDIATE 16

typedef struct {
  int type;
  void *ans;
} php_query_base_t;

typedef struct {
  char *comment;
  int x2;
} php_query_x2_answer_t;

typedef struct {
  php_query_base_t base;

  int val;

} php_query_x2_t;

php_query_x2_answer_t *php_query_x2 (int x);

typedef struct {
  php_query_base_t base;

  const char *data;
  int data_len;
} php_query_rpc_answer;

typedef struct {
  php_query_base_t base;

  const char *data;
  int data_len;
  long long auth_key_id;
  long long session_id;
} php_query_rpc_message;

typedef struct {
  int connection_id;
} php_query_connect_answer_t;

typedef enum {p_memcached, p_sql, p_rpc, p_get, p_get_id} protocol_t;

typedef struct {
  php_query_base_t base;

  const char *host;
  int port;
  protocol_t protocol;
} php_query_connect_t;

php_query_connect_answer_t *php_query_connect (const char *host, int port, protocol_t protocol);

int engine_mc_connect_to (const char *host, int port, int timeout_ms);

typedef struct {
  int loaded_bytes;
} php_query_http_load_post_answer_t;

typedef struct {
  php_query_base_t base;

  char *buf;
  int min_len;
  int max_len;
} php_query_http_load_post_t;

typedef struct data_reader_t_tmp data_reader_t;
struct data_reader_t_tmp {
  int len, readed;
  void (*read) (data_reader_t *reader, void *dest);
  void *extra;
};

typedef enum {nq_error, nq_ok} nq_state_t;

typedef struct {
  nq_state_t state;

  const char *desc;
  const char *res;
  int res_len;
  chain_t *chain;

  long long result_id;
} php_net_query_packet_answer_t;

typedef struct {
  php_query_base_t base;

  int connection_id;
  const char *data;
  int data_len;
  long long data_id;

  double timeout;
  protocol_t protocol;
  int extra_type;
} php_net_query_packet_t;

typedef struct net_ansgen_t_tmp net_ansgen_t;
typedef enum {st_ansgen_done, st_ansgen_error, st_ansgen_wait} ansgen_state_t;

typedef struct {
  void (*error) (net_ansgen_t *self, const char *);
  void (*timeout) (net_ansgen_t *self);
  void (*set_desc) (net_ansgen_t *self, const char *);
  void (*free) (net_ansgen_t *self);
} net_ansgen_func_t;

struct net_ansgen_t_tmp {
  long long qmem_req_generation;
  ansgen_state_t state;
  php_net_query_packet_answer_t *ans;
  net_ansgen_func_t *func;
};

typedef struct mc_ansgen_t_tmp mc_ansgen_t;
typedef struct {
  void (*value) (mc_ansgen_t *self, data_reader_t *data);
  void (*end) (mc_ansgen_t *self);
  void (*xstored) (mc_ansgen_t *self, int is_stored);
  void (*other) (mc_ansgen_t *self, data_reader_t *data);
  void (*version) (mc_ansgen_t *self, data_reader_t *data);
  void (*set_query_type) (mc_ansgen_t *self, int query_type);
} mc_ansgen_func_t;

struct mc_ansgen_t_tmp {
  net_ansgen_t base;
  mc_ansgen_func_t *func;
};

typedef enum {ap_any, ap_get, ap_store, ap_other, ap_err, ap_version} mc_ansgen_packet_state_t;//TODO ans?

typedef struct {
  net_ansgen_t base;
  mc_ansgen_func_t *func;

  mc_ansgen_packet_state_t state;

  str_buf_t *str_buf;
} mc_ansgen_packet_t;

mc_ansgen_t *mc_ansgen_packet_create (void);

typedef struct command_t_tmp command_t;
struct command_t_tmp {
  void (*run) (command_t *command, void *data);
  void (*free) (command_t *command);
};

typedef struct sql_ansgen_t_tmp sql_ansgen_t;
typedef struct {
  void (*set_writer) (sql_ansgen_t *self, command_t *writer);
  void (*ready) (sql_ansgen_t *self, void *data);
  void (*packet) (sql_ansgen_t *self, data_reader_t *reader);
  void (*done) (sql_ansgen_t *self);
} sql_ansgen_func_t;

struct sql_ansgen_t_tmp {
  net_ansgen_t base;
  sql_ansgen_func_t *func;
};


typedef enum {sql_ap_init, sql_ap_wait_conn, sql_ap_wait_ans} sql_ansgen_packet_state_t;//TODO ans?
typedef struct {
  net_ansgen_t base;
  sql_ansgen_func_t *func;

  sql_ansgen_packet_state_t state;

  command_t *writer;

  chain_t *chain;
} sql_ansgen_packet_t;

sql_ansgen_t *sql_ansgen_packet_create (void);

typedef struct net_send_ansgen_t_tmp net_send_ansgen_t;
typedef struct {
  void (*set_writer) (net_send_ansgen_t *self, command_t *writer);
  void (*send_and_finish) (net_send_ansgen_t *self, void *data);
} net_send_ansgen_func_t;

struct net_send_ansgen_t_tmp {
  net_ansgen_t base;
  net_send_ansgen_func_t *func;

  command_t *writer;
  long long qres_id;
};


net_send_ansgen_t *net_send_ansgen_create (void);

typedef struct {
  php_query_base_t base;
  long long *request_ids;
  int request_ids_len;
} php_query_create_queue_t;

typedef struct {
  long long queue_id;
} php_query_create_queue_answer_t;

typedef struct {
  php_query_base_t base;
  long long queue_id;
} php_query_queue_empty_t;

typedef struct {
  int empty;
} php_query_queue_empty_answer_t;

extern void (*got_result) (long long id);

typedef enum {qr_before_wait, qr_wait, qr_ok, qr_failed, qr_done} qres_state_t;
typedef enum {qr_watchcat = 1, qr_ans = 2, qr_any = 3} qres_type_t;
typedef struct qres_t_tmp qres_t;
struct qres_t_tmp {
  qres_type_t type;
  qres_state_t state;
  long long id;

  char *data;
  int data_len;

  double timeout;

  int ref_cnt;
  qres_t *watchcat;
  qres_t *next;
  qres_t *prev;
};

long long create_qres_ans (void);
long long create_qres_watchcat (long long *ids, int ids_n);

int qres_save (qres_t *qres, char *data, int data_len);
int qres_error (qres_t *qres);
int qres_readed (qres_t *qres);
void qres_free (qres_t *qres);
int qres_is_ready (qres_t *qres);
long long qres_next_id (qres_t *qres);

void qresults_clean();

qres_t *get_qres (long long qres_id, qres_type_t type);
void qres_set_timeout (qres_t *qres, double timeout);
double qres_get_timeout (qres_t *qres);

typedef struct net_get_ansgen_t_tmp net_get_ansgen_t;
typedef struct {
  void (*answer) (net_get_ansgen_t *self, qres_t *qres);
  void (*set_id) (net_get_ansgen_t *self, long long request_id);
  double (*try_wait) (net_get_ansgen_t *self, double precise_now);
  void (*done) (net_get_ansgen_t *self);
} net_get_ansgen_func_t;

struct net_get_ansgen_t_tmp {
  net_ansgen_t base;
  net_get_ansgen_func_t *func;

  long long request_id;
//  net_send_ansgen_state_t state;
};


net_get_ansgen_t *net_get_ansgen_create (void);

void init_drivers (void);

#ifdef __cplusplus
}
#endif

#pragma pack(pop)
