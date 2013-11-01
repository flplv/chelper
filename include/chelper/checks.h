/*
 *    Copyright (c) 2013 Felipe Lavratti (felipe@andradeneves.com)
 *
 *    Permission is hereby granted, free of charge, to any person obtaining a copy
 *    of this software and associated documentation files (the "Software"), to deal
 *    in the Software without restriction, including without limitation the rights
 *    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *    copies of the Software, and to permit persons to whom the Software is
 *    furnished to do so, subject to the following conditions:
 *
 *    The above copyright notice and this permission notice shall be included in
 *    all copies or substantial portions of the Software.
 *
 *    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 *    THE SOFTWARE.
 */

#ifndef OBJCHECK_H_
#define OBJCHECK_H_

#include <chelper/log.h>
#include <chelper/fatal.h>

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
