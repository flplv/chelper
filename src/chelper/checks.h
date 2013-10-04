#ifndef OBJCHECK_H_
#define OBJCHECK_H_

#include "chelper/log.h"
#include "chelper/fatal.h"

#define MEMORY_ALLOC_CHECK(__obj) \
	if (!__obj) { \
		MSG_ERROR("Failed to alloc memory", "Malloc"); \
		fatal("Locked"); \
 		while(1); \
	}

#define PTR_CHECK(__ptr, __module__) \
	if (!__ptr) { \
		MSG_ERROR("Invalid Pointer", __module__); \
		return; \
	}

#define PTR_CHECK_SILENT(__ptr, __module__) \
	if (!__ptr) { \
		return; \
	}

#define PTR_CHECK_RETURN(__ptr, __module__, __ret__) \
	if (!__ptr) { \
		MSG_ERROR("Invalid Pointer", __module__); \
		return __ret__; \
	}


#endif /* OBJCHECK_H_ */
