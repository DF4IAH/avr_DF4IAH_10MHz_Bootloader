/*
 * df4iah_probe.c
 *
 *  Created on: 01.11.2014
 *      Author: espero
 */

#include "df4iah_probe.h"


#ifdef RELEASE
__attribute__((section(".df4iah_probe"), aligned(2)))
#endif
void init_probe()
{
	BLDDR  &= ~(1<<BLPNUM);							// set probe line as input
	BLPORT |=  (1<<BLPNUM);							// and enable the pullup
}
