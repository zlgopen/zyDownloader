
#ifndef TRANSFERER_TCP_H
#define TRANSFERER_TCP_H

#include "transferer.h"

BEGIN_C_DECLS

/**
 * transferer_tcp提供在TCP上基于ymodem协议传输一个文件给服务器。
 * 服务器使用：https://github.com/SecurityToolsArchive/lrzsz.git
 * 服务器启动方式：./lrz  --overwrite --binary --tcp-server --ymodem
 * 本函数向transferer工厂注册transferer_tcp，注册之后才能被使用。
 */
bool_t transferer_tcp_register_creator_desc();

END_C_DECLS

#endif//TRANSFERER_TCP_H
