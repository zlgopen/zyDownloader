#ifndef TRANFERER_FACTORY_H
#define TRANFERER_FACTORY_H

#include "transferer.h"

BEGIN_C_DECLS

/*
 * transferer_factory是transferer的工厂：
 * transferer使用者只能通过transferer_factory遍历和创建transferer。
 * transferer的实现者则需要向transferer_factory注册。
 */

typedef struct _transferer_desc_t {
	const char* name;                          //transferer的名字。
	transferer_create_t create;                //transferer的构造函数
	transferer_get_props_desc_t get_props_desc;//transferer的属性描述文件。
}transferer_desc_t;


/**
 * \brief 遍历已经注册的transferer对象
 *
 * \param[in] visit       ： 遍历时的回调函数。
 * \param[in] ctx         ： 遍历时的回调函数的上下文。
 *
 * \retval TRUE  成功
 * \retval FALSE 失败 
*/
bool_t transferer_factory_foreach(visit_func_t visit, void* ctx);

/**
 * \brief 注册的transferer对象
 *
 * \param[in] transferer_desc ： 遍历时的回调函数的上下文。
 *
 * \retval TRUE  成功
 * \retval FALSE 失败 
*/
bool_t transferer_factory_register(const transferer_desc_t* transferer_desc);

/**
 * \brief 注销的transferer对象
 *
 * \param[in] transferer_desc ： 遍历时的回调函数的上下文。
 *
 * \retval TRUE  成功
 * \retval FALSE 失败 
*/
bool_t transferer_factory_unregister(const transferer_desc_t* transferer_desc);

/**
 * \brief 创建支持指定URL的transferer对象
 *
 * \param[in] url ： url。url的协议(schema)与transferer的name进行比较。
 *
 * \retval transferer对象
*/
transferer_t* transferer_factory_create(const char* url);

END_C_DECLS

#endif//TRANFERER_FACTORY_H

