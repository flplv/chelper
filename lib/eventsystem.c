#include "chelper/eventsystem.h"
#include "chelper/module_macros.h"
#include "chelper/checks.h"
#include "chelper/signalslot_opaque.h"
#include "chelper/ring_fifo.h"

#define MODULE_NAME "event_handler"

void event_handler_init(event_handler_t * cobj)
{
	obj_decl(struct s_event_handler_private, cobj);
	PTR_CHECK(obj, MODULE_NAME);

	obj->opaque_ptr = NULL;

	signal_opaque_init(&obj->signal);
}

void event_handler_deinit(event_handler_t * cobj)
{
	obj_decl(struct s_event_handler_private, cobj);
	PTR_CHECK(obj, MODULE_NAME);

	signal_opaque_deinit(&obj->signal);
}

signal_opaque_t* event_handler_signal(event_handler_t * cobj)
{
	obj_decl(struct s_event_handler_private, cobj);
	PTR_CHECK_RETURN(obj, MODULE_NAME, NULL);

	return &obj->signal;
}

void event_handler_set_args(event_handler_t * cobj, void* ptr)
{
	obj_decl(struct s_event_handler_private, cobj);
	PTR_CHECK(obj, MODULE_NAME);

	obj->opaque_ptr = ptr;
}

static void event_handler_call(event_handler_t * cobj)
{
	obj_decl(struct s_event_handler_private, cobj);
	PTR_CHECK(obj, MODULE_NAME);

	signal_opaque_emit(&obj->signal, obj->opaque_ptr);
}

#undef MODULE_NAME
#define MODULE_NAME "event_loop"

void event_loop_init(event_loop_t * cobj)
{
	obj_decl(struct s_event_loop_private, cobj);
	PTR_CHECK(obj, MODULE_NAME);

	ring_fifo_init(&obj->queue, sizeof (event_handler_t *), 10);
}

void event_loop_deinit(event_loop_t * cobj)
{
	obj_decl(struct s_event_loop_private, cobj);
	PTR_CHECK(obj, MODULE_NAME);

	ring_fifo_deinit(&obj->queue);
}

void event_loop_clear_resize(event_loop_t * cobj, int new_size)
{
	obj_decl(struct s_event_loop_private, cobj);
	PTR_CHECK(obj, MODULE_NAME);

	ring_fifo_deinit(&obj->queue);
	ring_fifo_init(&obj->queue, sizeof (event_handler_t *), new_size);
}

void event_loop_queue_event(event_loop_t * cobj, event_handler_t * handle)
{
	obj_decl(struct s_event_loop_private, cobj);
	PTR_CHECK(obj, MODULE_NAME);

	if (ring_fifo_is_full(&obj->queue))
	{
		MSG_ERROR("Queue full", MODULE_NAME);
		return;
	}

	if (!ring_fifo_push(&obj->queue, (BUFFER_PTR_RDOLY)&handle))
	{
		MSG_ERROR("Unable to push", MODULE_NAME);
		return;
	}
}

bool event_loop_has_pending_events(event_loop_t * cobj)
{
	obj_decl(struct s_event_loop_private, cobj);
	PTR_CHECK_RETURN(obj, MODULE_NAME, false);

	if (ring_fifo_is_empty(&obj->queue))
		return false;

	return true;
}

void event_loop_periodic(event_loop_t * cobj)
{
	obj_decl(struct s_event_loop_private, cobj);
	PTR_CHECK(obj, MODULE_NAME);

	event_handler_t * handle;

	if (ring_fifo_is_empty(&obj->queue))
		return;

	ring_fifo_pop(&obj->queue, (BUFFER_PTR)&handle);
	event_handler_call(handle);
}
