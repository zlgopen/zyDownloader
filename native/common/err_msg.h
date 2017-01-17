#ifndef ERR_MSG_H
#define ERR_MSG_H

#define MSG_OPEN_FILE_FAILED     "open file failed." 
#define MSG_OPEN_SERIAL_FAILED   "open serial port failed."
#define MSG_CREATE_SOCKET_FAILED "create socket failed."
#define MSG_BIND_PORT_FAILED     "bind port failed." 
#define MSG_CONNECT_FAILED       "connect to server failed."
#define MSG_SEND_FILE_FAILED      "send file content failed."
#define MSG_SEND_FILE_HEAD_FAILED "send file header failed."
#define MSG_SYNC_PEER_FAILED      "sync peer failed."
#define MSG_GET_HEADER_CRC_FAILED "get file header CRC failed."

#define SET_ERR_MSG(ret_msg, msg) if(ret_msg != NULL) {*ret_msg = msg;}
#define SET_ERR_MSG_IF(p, ret_msg, msg) if((p) && ret_msg != NULL) {*ret_msg = msg;}

#endif//ERR_MSG_H
