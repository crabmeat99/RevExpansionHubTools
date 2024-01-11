/*
 * serial.h
 *
 *  Created on: Dec 3, 2020
 *  Author: Andrey Mihadyuk
 *
 */

#ifndef ARCH_INCLUDES_RHSP_SERIAL_H_
#define ARCH_INCLUDES_RHSP_SERIAL_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "Arduino.h"
#include "HardwareSerial.h"

#include "rhsp_errors.h"

#define RHSP_SERIAL_INFINITE_TIMEOUT    -1

typedef struct {
    HardwareSerial *hardwareSerial;
    int rxTimeoutMs;
} RhspSerial;

/**
 * @brief serial port init
 *
 * @param[in] serial serial
 *
 * @note this fucntion shall be called once before using serial port
 *
 * */
RhspSerial* rhsp_serialInit(HardwareSerial *s);

/**
 * @brief read bytes from serial port
 *
 * @param[in]  serial serial port instance
 * @param[out] buffer        buffer
 * @param[in]  bytesToRead   bytes to read
 *
 * @return number of read bytes in case success, otherwise negative error code
 * */
int rhsp_serialRead(RhspSerial* serial, uint8_t* buffer, size_t bytesToRead);

/**
 * @brief write bytes to serial port
 *
 * @param[in] serial serial port instance
 * @param[in] buffer        buffer
 * @param[in] bytesToWrite  bytes to write
  *
 * @return number of written bytes in case success, otherwise negative error code
 * */
int rhsp_serialWrite(RhspSerial* serial, const uint8_t* buffer, size_t bytesToWrite);

/**
 * @brief close serial port
 *
 * @param[in] serial serial port
 *
 * */
void rhsp_serialClose(RhspSerial* serial);

#endif /* ARCH_INCLUDES_RHSP_SERIAL_H_ */
