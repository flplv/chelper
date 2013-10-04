
#include <chelper/timeout.h>
#include <chelper/checks.h>
#include <sys/time.h>
#include <unistd.h>

uint32_t time_now()
{
    struct timeval tv;
    if (gettimeofday(&tv, NULL) != 0)
    {
        MSG_ERROR("Unable to gettimeofday()", "timeout");
    }

    uint32_t msec = (tv.tv_sec * 1000 + tv.tv_usec / 1000);

    return msec;
}

void timeout_init(timeout_t * cobj)
{
    *cobj = time_now();
}


timeout_t timeout_init_cpy(void)
{
	timeout_t cobj;

	timeout_init(&cobj);

	return cobj;
}


BOOL timeout_check(timeout_t * cobj, uint32_t tout_ms)
{
    return ( !( (time_now() - *cobj) < tout_ms) );
}

BOOL timeout_check_and_reinit(timeout_t * cobj, uint32_t period_ms)
{
    if ( (time_now() - *cobj) < period_ms )
    {
    	return FALSE;
    }
    else
    {
    	*cobj += period_ms;
    	return TRUE;
    }
}

void timeout_sleep(timeout_t *cobj, uint32_t period_ms)
{
	if (timeout_check(cobj, period_ms))
		return;

	usleep(((*cobj + period_ms) - time_now()) * 800);
}
