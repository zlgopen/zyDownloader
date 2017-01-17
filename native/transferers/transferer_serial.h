
#ifndef TRANSFERER_SERIAL_H
#define TRANSFERER_SERIAL_H

#include "transferer.h"

BEGIN_C_DECLS

/**
 * transferer_serial提供在串口上基于ymodem协议传输一个文件给对方。
 * 本函数向transferer工厂注册transferer_serial，注册之后才能被使用。
 */
bool_t transferer_serial_register_creator_desc();

END_C_DECLS

#endif//TRANSFERER_SERIAL_H
