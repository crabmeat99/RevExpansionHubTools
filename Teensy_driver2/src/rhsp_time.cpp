/*
 * time.c
 *
 *  Created on: Dec 3, 2020
 *      Author: user
 */
#include <time.h>

#include "rhsp_time.h"
#include <Arduino.h>

uint32_t rhsp_getSteadyClockMs(void)
{
    return millis();
}
