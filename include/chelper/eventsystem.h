#ifndef EVENTSYSTEM_H_
#define EVENTSYSTEM_H_

#include <chelper/helper_types.h>

struct s_event_handler_private
{
	void * data_arg;
	size_t size_arg;
	signal_opaque_t signal;
};
typedef uint8_t event_handler_t[sizeof(struct s_event_handler_private)];

void event_handler_init(event_handler_t *);
void event_handler_deinit(event_handler_t *);
signal_opaque_t * event_handler_signal(event_handler_t *);
void event_handler_set_args(event_handler_t *, void * data, size_t size);

struct s_event_loop_private
{
	ring_fifo_t queue;
};
typedef uint8_t event_loop_t[sizeof(struct s_event_loop_private)];


void event_loop_init(event_loop_t *);
void event_loop_deinit(event_loop_t *);
void event_loop_clear_resize(event_loop_t *, int new_size);

void event_loop_queue_event(event_loop_t *, event_handler_t *); /* ownership is not passed */

bool event_loop_has_pending_events(event_loop_t *);
void event_loop_periodic(event_loop_t *);


#endif /* EVENTLOOP_H_ */
