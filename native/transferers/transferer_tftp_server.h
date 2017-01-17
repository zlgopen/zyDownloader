
#ifndef TRANSFERER_TFTP_SERVER_H
#define TRANSFERER_TFTP_SERVER_H

#include "transferer.h"

BEGIN_C_DECLS

/**
 * transferer_tftp_server是在本地启动一个tftpserver，传输一个文件后就停止服务。
 * 本函数向transferer工厂注册transferer_tftp_server，注册之后才能被使用。
 */
bool_t transferer_tftp_server_register_creator_desc();

END_C_DECLS

#endif//TRANSFERER_TFTP_SERVER_H
