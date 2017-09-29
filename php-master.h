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
extern "C" {
#endif

#include "net-connections.h"
void start_master (int *http_fd, int (*try_get_http_fd)(void), int http_fd_port);
struct connection *create_pipe_reader (int pipe_fd, conn_type_t *type, void *extra);

#ifdef __cplusplus
}
#endif
