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

#ifndef SIGNALSLOTDATA_H_
#define SIGNALSLOTDATA_H_

#include <chelper/helper_types.h>

#ifdef __cplusplus
extern "C" {
#endif

void signal_data_init(signal_data_t *);
void signal_data_deinit(signal_data_t *);

bool signal_data_is_connected(signal_data_t *, slot_data_t *);
void signal_data_emit(signal_data_t *, void * data, size_t size);

void slot_data_init(slot_data_t *);
void slot_data_deinit(slot_data_t *);

void slot_data_set(slot_data_t *, slot_data_func function, slot_arg arg);
void slot_data_connect(slot_data_t *, signal_data_t *);
void slot_data_disconnect(slot_data_t *, signal_data_t *);

#ifdef __cplusplus
}
#endif

#endif /* SIGNALSLOT2_H_ */
