#ifndef HELPER_TYPES_H_
#define HELPER_TYPES_H_

#if !defined SYSTEM_UNIT_TEST
#include <malloc.h>
#else
#include "CppUTest/MemoryLeakDetectorMallocMacros.h"
#endif

#include <stdint.h>

#ifndef FALSE
#define FALSE 0
#endif
#ifndef TRUE
#define TRUE 1
#endif
#ifndef BOOL
#define BOOL uint32_t
#endif
#ifndef __SIZE_TYPE__
typedef unsigned int size_t;
#endif

#define BUFFER_PTR_RDOLY const uint8_t *
#define BUFFER_PTR uint8_t *

typedef uint32_t timeout_t;

struct s_vector_private
{
	uint32_t item_size;
	uint32_t used_slots;
	uint32_t buffer_total_slots;
	uint8_t *buffer;
};
typedef uint8_t vector_t[sizeof(struct s_vector_private)];

typedef void * slot_arg;
typedef void(*slot_func)(slot_arg);
typedef void(*slot2_func)(slot_arg, size_t, size_t);

struct s_signal_private
{
	vector_t slots_vector;
};
typedef uint8_t signal_t[sizeof(struct s_signal_private)];

struct s_slot_private
{
	slot_func func;
	slot_arg arg0;
	BOOL set;
};
typedef uint8_t slot_t[sizeof(struct s_slot_private)];

struct s_signal2_private
{
	vector_t slot2s_vector;
};
typedef uint8_t signal2_t[sizeof(struct s_signal2_private)];

struct s_slot2_private
{
	slot2_func func;
	slot_arg arg0;
	BOOL set;
};
typedef uint8_t slot2_t[sizeof(struct s_slot2_private)];

struct s_my_string
{
	char * str_data;
	size_t str_len;
	size_t mem_size;
	signal_t update_signal;
};
typedef uint8_t my_string_t[sizeof(struct s_my_string)];


#endif /* HELPER_TYPES_H_ */
