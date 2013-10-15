#include "chelper/my_string.h"
#include "chelper/vector.h"
#include "chelper/checks.h"
#include "chelper/signalslot.h"

#define SIGNATURE_MY_STRING (ADDRESS_TO_SIGNATURE_CAST)&my_string_create


void my_string_init(my_string_t * cobj)
{
	struct s_my_string* obj = (struct s_my_string *)cobj;
	PTR_CHECK(obj, "my_string");

	vector_init(&obj->str_data, sizeof(char));
	signal_init(&obj->update_signal);
}

void my_string_deinit(my_string_t *cobj)
{
	struct s_my_string* obj = (struct s_my_string *)cobj;
	PTR_CHECK(obj, "my_string");

	signal_deinit(&obj->update_signal);
	vector_deinit(&obj->str_data);
}

void my_string_clear(my_string_t * cobj)
{
	struct s_my_string* obj = (struct s_my_string *)cobj;
	PTR_CHECK(obj, "my_string");

	vector_clear(&obj->str_data);
}

void my_string_set(my_string_t *cobj, const char* str)
{
	size_t len;

	struct s_my_string* obj = (struct s_my_string *)cobj;
	PTR_CHECK(obj, "my_string");

	len = my_strlen(str);

	vector_clear(&obj->str_data);
	vector_add_many(&obj->str_data, (BUFFER_PTR_RDOLY)str, len + 1);

	signal_emit(&obj->update_signal);
}

const char* my_string_data(my_string_t* cobj)
{
	struct s_my_string* obj = (struct s_my_string *)cobj;
	PTR_CHECK_RETURN(obj, "my_string", NULL);

	return (const char *)vector_data(&obj->str_data);
}

size_t my_string_len(my_string_t* cobj)
{
	struct s_my_string* obj = (struct s_my_string *)cobj;
	PTR_CHECK_RETURN(obj, "my_string", 0);

	return vector_size(&obj->str_data) - 1;
}

signal_t * my_string_update_signal(my_string_t * cobj)
{
	struct s_my_string* obj = (struct s_my_string *)cobj;
	PTR_CHECK_RETURN(obj, "my_string", NULL);

	return &obj->update_signal;
}

size_t my_strlen(const char* str)
{
	size_t len = 0;
	while (*str++)
		len++;
	return len;
}

