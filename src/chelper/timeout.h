
#ifndef TIMEOUT_H_
#define TIMEOUT_H_

#include "chelper/helper_types.h"

void timeout_init(timeout_t *);
timeout_t timeout_init_cpy(void);

/* Return true if tout_ms has elapsed */
BOOL timeout_check(timeout_t *, uint32_t tout_ms);

/* Return true if tout_ms has elapsed and reinit cobj, so it can be used after to create periodically execution */
BOOL timeout_check_and_reinit(timeout_t * cobj, uint32_t period_ms);

/* Sleep until the next timeout (use only to spend time while waiting for a timeout,
   do not count on time precision of this function) */
void timeout_sleep(timeout_t *cobj, uint32_t period_ms);

uint32_t time_now(void);

#endif /* TIMEOUT_H_ */
