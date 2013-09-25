
#include "chelper/signalslot2.h"
#include "chelper/vector.h"
#include "chelper/checks.h"
#include "chelper/log.h"

static void slot2_call(slot2_t *, size_t, size_t);

void signal2_init(signal2_t * cobj)
{
	struct s_signal2_private * obj = (struct s_signal2_private *) cobj;
	PTR_CHECK(obj, "signal2");

	vector_init(&obj->slot2s_vector, sizeof(slot2_t *));
}

void signal2_deinit(signal2_t * cobj)
{
	struct s_signal2_private * obj = (struct s_signal2_private *) cobj;
	PTR_CHECK(obj, "signal2");

	vector_deinit(&obj->slot2s_vector);
}

void signal2_emit(signal2_t *cobj, size_t x, size_t y)
{
	uint32_t n_of_slot2s;
	slot2_t *slot2_to_be_called = NULL;

	struct s_signal2_private * obj = (struct s_signal2_private *) cobj;
	PTR_CHECK(obj, "signal2");

	n_of_slot2s = vector_size(&obj->slot2s_vector);

	while(n_of_slot2s--)
	{
		slot2_to_be_called = *(slot2_t **)vector_at(&obj->slot2s_vector, n_of_slot2s);
		slot2_call(slot2_to_be_called, x, y);
	}

}

static BOOL signal2_is_connected(signal2_t *cobj, slot2_t *slot2)
{
	uint32_t n_of_slot2s;
	slot2_t *slot2_to_be_checked;

	struct s_signal2_private * obj = (struct s_signal2_private *) cobj;
	PTR_CHECK_RETURN(obj, "signal2", FALSE);

	n_of_slot2s = vector_size(&obj->slot2s_vector);

	while(n_of_slot2s--)
	{
		slot2_to_be_checked = *(slot2_t **)vector_at(&obj->slot2s_vector, n_of_slot2s);
		if(slot2 == slot2_to_be_checked)
			return TRUE;
	}

	return FALSE;
}

static void signal2_connect(signal2_t *cobj, slot2_t *slot2)
{
	struct s_signal2_private * obj = (struct s_signal2_private *) cobj;
	PTR_CHECK(obj, "signal2");

	if (signal2_is_connected(cobj, slot2))
		return;

	vector_add(&obj->slot2s_vector, (BUFFER_PTR)&slot2);
}

void slot2_init(slot2_t * cobj)
{
	struct s_slot2_private * obj = (struct s_slot2_private *) cobj;
	PTR_CHECK(obj, "slot2");
}

void slot2_deinit(slot2_t * cobj)
{
	struct s_slot2_private * obj = (struct s_slot2_private *) cobj;
	PTR_CHECK(obj, "slot2");;
}

void slot2_set(slot2_t *cobj, slot2_func function, slot_arg arg)
{
	struct s_slot2_private * obj = (struct s_slot2_private *) cobj;
	PTR_CHECK(obj, "slot2");

	if (!function) {
		LOG_ERROR("slot2", "bad slot2 function");
		return;
	}

	obj->func = function;
	obj->arg0 = arg;
	obj->set = TRUE;
}

void slot2_connect(slot2_t *cobj, signal2_t* signal2)
{
	struct s_slot2_private * obj = (struct s_slot2_private *) cobj;
	PTR_CHECK(obj, "slot2");

	signal2_connect(signal2, cobj);
}

static void slot2_call(slot2_t *cobj, size_t x, size_t y)
{
	struct s_slot2_private * obj = (struct s_slot2_private *) cobj;
	PTR_CHECK(obj, "slot2");

	if (!obj->set) {
		LOG_ERROR("slot2", "no slot2 function set");
		return;
	}

	if (!obj->func) {
		LOG_ERROR("slot2", "bad slot2 function");
		return;
	}

	obj->func(obj->arg0, x, y);
}
