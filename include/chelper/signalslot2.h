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

#ifndef SIGNALSLOT2_H_
#define SIGNALSLOT2_H_

#include <chelper/helper_types.h>

#ifdef __cplusplus
extern "C" {
#endif

void signal2_init(signal2_t *);
void signal2_deinit(signal2_t *);

void signal2_emit(signal2_t *, size_t x, size_t y);

bool signal2_is_connected(signal2_t *, slot2_t *slot);

void slot2_init(slot2_t *);
void slot2_deinit(slot2_t *);

void slot2_set(slot2_t *, slot2_func function, slot_arg arg);
void slot2_connect(slot2_t *, signal2_t *);
void slot2_disconnect(slot2_t *, signal2_t *);

#ifdef __cplusplus
}
#endif

#endif /* SIGNALSLOT2_H_ */
