#ifndef FILE_TRANSFERER_H
#define FILE_TRANSFERER_H

#include "types_def.h"
#include "url.h"

BEGIN_C_DECLS

/*
 * transferer接口定义。
 * 下载工具支持多种不同的下载方式（比如串口+ymodem和tftp），transferer_t描述了不同下载方式需要实现的函数。
 */
struct _transferer_t;
typedef struct _transferer_t transferer_t;

/**
 * \brief 开始传输。
 *
 * \param[in]  t       ： transferer对象
 * \param[out] err_msg ： 如果失败，用于返回错误信息，调用者不需释放。
 *
 * \retval TRUE  成功
 * \retval FALSE 失败 
*/
typedef bool_t (*transferer_start_t)(transferer_t* t, const char** err_msg);

/**
 * \brief 获取当前传输文件的大小。
 *
 * \param[in] t       ： transferer对象
 *
 * \retval 文件的大小。
*/
typedef size_t (*transferer_get_total_size_t)(transferer_t* t);

/**
 * \brief 获取已经传输的字节数。
 *
 * \param[in] t       ： transferer对象
 *
 * \retval 已经传输的字节数。
*/
typedef size_t (*transferer_get_sent_size_t)(transferer_t* t);

/**
 * \brief 销毁transferer对象。
 *
 * \param[in] t       ： transferer对象
 *
*/
typedef void (*transferer_destroy_t)(transferer_t* t);

/**
 * \brief 创建transferer对象。
 *
 * \param[in] t       ： transferer对象
 *
 * \retval transferer对象。
*/
typedef transferer_t* (*transferer_create_t)(url_t* url);

/**
 * \brief 获取transferer对象的属性描述。属性描述主要用于创建设置界面。
 *
 * \retval 属性描述。
*/
typedef const char* (*transferer_get_props_desc_t)();

struct _transferer_t {
	transferer_start_t          start;
	transferer_get_total_size_t get_total_size;
	transferer_get_sent_size_t  get_sent_size;
	transferer_destroy_t        destroy;
};


static inline bool_t transferer_start(transferer_t* t, const char** err_msg){
	return_value_if_fail(t != NULL && t->start != NULL, FALSE);
	return t->start(t, err_msg);
}

static inline size_t transferer_get_total_size(transferer_t* t){
	return_value_if_fail(t != NULL && t->get_total_size != NULL, 0);
	return t->get_total_size(t);
}

static inline size_t transferer_get_sent_size(transferer_t* t){
	return_value_if_fail(t != NULL && t->get_sent_size != NULL, 0);
	return t->get_sent_size(t);
}

static inline void transferer_destroy(transferer_t* t){
	return_if_fail(t != NULL && t->destroy != NULL);
	t->destroy(t);
}

END_C_DECLS

#endif//FILE_TRANSFERER_H

