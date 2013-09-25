#ifndef SIGNALSLOT2_H_
#define SIGNALSLOT2_H_

#include "helper_types.h"

void signal2_init(signal2_t *);
void signal2_deinit(signal2_t *);

void signal2_emit(signal2_t *, size_t x, size_t y);

void slot2_init(slot2_t *);
void slot2_deinit(slot2_t *);

void slot2_set(slot2_t *, slot2_func function, slot_arg arg);
void slot2_connect(slot2_t *, signal2_t *);

#endif /* SIGNALSLOT2_H_ */
