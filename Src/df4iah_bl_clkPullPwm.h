/*
 * df4iah_clkPullPwm.h
 *
 *  Created on: 24.11.2014
 *      Author: espero
 */

#ifndef DF4IAH_BL_CLKPULLPWM_H_
#define DF4IAH_BL_CLKPULLPWM_H_


#define DEFAULT_PWM_COUNT  									186


void clkPullPwm_bl_init();
void clkPullPwm_bl_close();

void clkPullPwm_bl_setRatio(uint8_t ratio);

void clkPullPwm_bl_togglePin();
void clkPullPwm_bl_endlessTogglePin();

#endif /* DF4IAH_BL_CLKPULLPWM_H_ */
