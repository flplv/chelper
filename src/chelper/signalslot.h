#ifndef SIGNALSLOT_H_
#define SIGNALSLOT_H_

#include "helper_types.h"

void signal_init(signal_t *);
void signal_deinit(signal_t *);

void signal_emit(signal_t *);

void slot_init(slot_t *);
void slot_deinit(slot_t *);

void slot_set(slot_t *, slot_func function, slot_arg arg);
void slot_connect(slot_t *, signal_t *);

#endif /* SIGNALSLOT_H_ */
