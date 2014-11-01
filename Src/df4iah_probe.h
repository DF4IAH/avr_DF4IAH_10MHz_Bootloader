/*
 * df4iah_probe.h
 *
 *  Created on: 01.11.2014
 *      Author: espero
 */

#ifndef DF4IAH_PROBE_H_
#define DF4IAH_PROBE_H_

#include "chipdef.h"


/*
 * Pin "STARTPIN" on port "STARTPORT" in this port has to grounded
 * (active low) to start the bootloader
 */
#define BLPORT		PORTC
#define BLDDR		DDRC
#define BLPIN		PINC
#define BLPNUM		PINC4


void init_probe();


#endif /* DF4IAH_PROBE_H_ */
