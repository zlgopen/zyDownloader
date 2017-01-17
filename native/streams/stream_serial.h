#ifndef STREAM_SERIAL_H
#define STREAM_SERIAL_H
#include "stream.h"
#include "serial/serial.h"

BEGIN_C_DECLS

/**
 * \brief 打开串口，并创建一个stream对象。
 *
 * \param[in]  port ： 串口设备名或设备文件。
 * \param[in]  baudrate ：波特率
 * \param[in]  bytesize ：数据位
 * \param[in]  parity   ：奇偶校验
 * \param[in]  stopbits ：停止位
 * \param[in]  flowcontrol ：流控方法。
 *
 * \retval stream对象
*/
stream_t* stream_serial_create(
		const char* port,
		uint32_t baudrate,
		serial::bytesize_t bytesize,
		serial::parity_t parity,
		serial::stopbits_t stopbits,
		serial::flowcontrol_t flowcontrol
	);

END_C_DECLS

#endif//STREAM_SERIAL_H

