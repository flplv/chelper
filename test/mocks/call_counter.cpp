/*
 * CallCounter.cpp
 *
 *  Created on: Jan 20, 2013
 *      Author: fanl
 */

#ifndef CALLCOUNTER_CPP_
#define CALLCOUNTER_CPP_

static int counter;

int CallCounter_GetCounter(void)
{
	return counter;
}

void CallCounter_ResetCounter(void)
{
	counter = 0;
}

void CallCounter_CallMeToCount(void)
{
	counter++;
}


#endif /* CALLCOUNTER_CPP_ */
