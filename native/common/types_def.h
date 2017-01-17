#ifndef TYPES_DEF_H
#define TYPES_DEF_H 
#include <stdlib.h>
#include <string.h>

#include <stdio.h>
#define trace printf

#include <assert.h>

typedef int bool_t;
typedef float float32_t;
typedef double floa64_t;

#if defined(WIN32) || defined(DEVICE_BUILD)
typedef signed char        int8_t;
typedef short              int16_t;
typedef int                int32_t;
typedef long long          int64_t;
typedef unsigned char      uint8_t;
typedef unsigned short     uint16_t;
typedef unsigned int       uint32_t;
typedef unsigned long long uint64_t;
#else
#ifndef _INT8_T_DECLARED
typedef __int8_t int8_t;
#define _INT8_T_DECLARED
#endif
#ifndef _UINT8_T_DECLARED
typedef __uint8_t uint8_t;
#define _UINT8_T_DECLARED
#endif

#ifndef _INT16_T_DECLARED
typedef __int16_t int16_t;
#define _INT16_T_DECLARED
#endif
#ifndef _UINT16_T_DECLARED
typedef __uint16_t uint16_t;
#define _UINT16_T_DECLARED
#endif

#ifndef _INT32_T_DECLARED
typedef __int32_t int32_t;
#define _INT32_T_DECLARED
#endif
#ifndef _UINT32_T_DECLARED
typedef __uint32_t uint32_t;
#define _UINT32_T_DECLARED
#endif
#endif//WIN32



#ifndef errno_t
typedef int errno_t;
#endif

#define ERRNO_OK 0
#define ERRNO_FAIL -1
#define ERRNO_NO_SPACE -2
#define ERRNO_NOT_FOUND -3
#define ERRNO_NO_PERMISSION -4
#define ERRNO_INVALID_PARAMS -5

#ifndef TRUE
#	define TRUE 1
#endif
#ifndef FALSE
#	define FALSE 0
#endif

#ifdef __cplusplus
#	define BEGIN_C_DECLS extern "C" {
#	define END_C_DECLS }
#else
#	define BEGIN_C_DECLS
#	define END_C_DECLS
#endif

#ifndef WIN32
#	define strncpy_s(a, al, b, bl) strncpy(a, b, bl);
#endif//WIN32

typedef void (*GObjectDestroyFunc)(void* obj);

typedef struct _GObject {
	GObjectDestroyFunc destroy;
	void* obj;
}GObject;

static inline GObject gobject_init(GObjectDestroyFunc destroy, void* obj) {
	GObject gobject;
	gobject.destroy = destroy;
	gobject.obj = obj;
	
	return gobject;
}

typedef int (*hash_func_t)(const void* data, size_t len);
typedef int (*compare_func_t)(const void* a, const void* b, size_t len);
typedef bool_t (*visit_func_t)(void* ctx, const void* data);

#define ELM_NR(a) (sizeof(a)/sizeof(a[0]))
#ifdef NDEBUG
#	define ENSURE(p) (void)(p)
#else
#	define ENSURE(p) assert(p)
#endif

#ifdef NDEBUG
#	define return_if_fail(p) if(!(p)) {return;}
#	define return_value_if_fail(p, value) if(!(p)) {return (value);}
#else
#	define return_if_fail(p) if(!(p)) \
	{trace("%s:%d "#p"\n", __FUNCTION__, __LINE__); return;}
#	define return_value_if_fail(p, value) if(!(p)) \
	{trace("%s:%d "#p"\n", __FUNCTION__, __LINE__); return (value);}
#endif

void socketInit();
void socketDeinit();
void msleep(int ms);
void closeSocket(int sock);

#endif//TYPES_DEF_H 
