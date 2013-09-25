
#include "chelper/signalslot.h"
#include "chelper/vector.h"
#include "chelper/checks.h"
#include "chelper/log.h"

static void slot_call(slot_t *);

void signal_init(signal_t * cobj)
{
	struct s_signal_private * obj = (struct s_signal_private *) cobj;
	PTR_CHECK(obj, "signal");

	vector_init(&obj->slots_vector, sizeof(slot_t *));
}

void signal_deinit(signal_t * cobj)
{
	struct s_signal_private * obj = (struct s_signal_private *) cobj;
	PTR_CHECK(obj, "signal");

	vector_deinit(&obj->slots_vector);
}

void signal_emit(signal_t * cobj)
{
	uint32_t n_of_slots;
	slot_t * slot_to_be_called;

	struct s_signal_private * obj = (struct s_signal_private *) cobj;
	PTR_CHECK(obj, "signal");

	n_of_slots = vector_size(&obj->slots_vector);

	while(n_of_slots--)
	{
		slot_to_be_called = *(slot_t **)vector_at(&obj->slots_vector, n_of_slots);
		slot_call(slot_to_be_called);
	}
}

static BOOL signal_is_connected(signal_t *cobj, slot_t *slot)
{
	uint32_t n_of_slots;
	slot_t * slot_to_be_checked;

	struct s_signal_private * obj = (struct s_signal_private *) cobj;
	PTR_CHECK_RETURN(obj, "signal", FALSE);

	n_of_slots = vector_size(&obj->slots_vector);

	while(n_of_slots--)
	{
		slot_to_be_checked = *(slot_t **)vector_at(&obj->slots_vector, n_of_slots);
		if(slot == slot_to_be_checked)
			return TRUE;
	}

	return FALSE;
}

static void signal_connect(signal_t *cobj, slot_t *slot)
{
	struct s_signal_private * obj = (struct s_signal_private *) cobj;
	PTR_CHECK(obj, "signal");

	if (signal_is_connected(cobj, slot))
		return;

	vector_add(&obj->slots_vector, (BUFFER_PTR)&slot);
}

void slot_init(slot_t * cobj)
{
	struct s_slot_private * obj = (struct s_slot_private *) cobj;
	PTR_CHECK(obj, "slot");
}

void slot_deinit(slot_t * cobj)
{
	struct s_slot_private * obj = (struct s_slot_private *) cobj;
	PTR_CHECK(obj, "slot");
}

void slot_set(slot_t *cobj, slot_func function, slot_arg arg)
{
	struct s_slot_private * obj = (struct s_slot_private *) cobj;
	PTR_CHECK(obj, "slot");

	if (!function) {
		LOG_ERROR("slot", "bad slot function");
		return;
	}

	obj->func = function;
	obj->arg0 = arg;
	obj->set = TRUE;
}

void slot_connect(slot_t *cobj, signal_t* signal)
{
	struct s_slot_private * obj = (struct s_slot_private *) cobj;
	PTR_CHECK(obj, "slot");

	signal_connect(signal, cobj);
}

static void slot_call(slot_t *cobj)
{
	struct s_slot_private * obj = (struct s_slot_private *) cobj;
	PTR_CHECK(obj, "slot");

	if (!obj->set) {
		LOG_ERROR("slot", "no slot function set");
		return;
	}

	if (!obj->func) {
		LOG_ERROR("slot", "bad slot function");
		return;
	}

	obj->func(obj->arg0);
}
