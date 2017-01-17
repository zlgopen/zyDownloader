#ifndef STREAM_TCP_H
#define STREAM_TCP_H

#include "stream.h"

BEGIN_C_DECLS

/**
 * \brief 创建一个socket，并在指定的端口号上监听。
 *
 * \param[in]  port       ： 端口号
 *
 * \retval socket
*/
int       tcp_listen(int port);

/**
 * \brief 连接到指定的服务器，并在对应的socket上创建一个stream对象。
 *
 * \param[in]  host       ： 服务器
 * \param[in]  port       ： 端口号
 *
 * \retval stream对象
*/
stream_t* tcp_connect(const char* host, int port);

/**
 * \brief 在指定的socket上接受一个客户端，并在对应的socket上创建一个stream对象。
 *
 * \param[in]  sock       ： 用tcp_listen创建的socket。
 *
 * \retval stream对象
*/
stream_t* tcp_accept(int sock);

#define DEFAULT_PORT 9988 

END_C_DECLS

#endif//STREAM_TCP_H

