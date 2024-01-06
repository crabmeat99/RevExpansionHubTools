/*
 * serial.c
 *
 *  Created on: Dec 3, 2020
 *  Author: Andrey Mihadyuk
 */
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include "Arduino.h"
#include "HardwareSerial.h"
#include "rhsp_serial.h"

void rhsp_serialInit(RhspSerial* serial)
{
    if (!serial)
    {
        return;
    }
}

int rhsp_serialOpen(RhspSerial* serial,
                    uint32_t baudrate
                    )
{
    if (!serial)
    {
        return RHSP_SERIAL_ERROR;
    }

    return 0;
}

int rhsp_serialRead(RhspSerial* serial, uint8_t* buffer, size_t bytesToRead)
{
    if (!serial || !buffer)
    {
        return RHSP_SERIAL_ERROR;
    }

    int bytesRead;

    //int x = Serial5.available();
    // ssize_t retval;
    // struct timeval tvTimeout;

    return bytesRead;
}

//
// rhsp_serialWrite
// Return: bytes transfered
int rhsp_serialWrite(RhspSerial* serial, const uint8_t* buffer, size_t bytesToWrite)
{
    if (!serial || !buffer)
    {
        return RHSP_SERIAL_ERROR;
    }


    return 0;
}

void rhsp_serialClose(RhspSerial* serial)
{

    if (!serial)
    {
        return;
    }
}

