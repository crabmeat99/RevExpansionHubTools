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


RhspSerial* rhsp_serialInit(HardwareSerial *s)
{
    RhspSerial *serial = new RhspSerial();

    s->begin(460800);
    s->transmitterEnable(18);
    s->flush();
    s->clear();
    pinMode(17, OUTPUT);
    digitalWrite(17, LOW);

    serial->hardwareSerial = s;

    return serial;
}

int rhsp_serialRead(RhspSerial* serial, uint8_t* buffer, size_t bytesToRead)
{
    uint8_t c;

    if (!serial || !buffer)
    {
        return RHSP_SERIAL_ERROR;
    }

    size_t bytesAvailable = serial->hardwareSerial->available();
    size_t newBytesToRead = (bytesToRead < bytesAvailable) ? bytesToRead : bytesAvailable;

    for (size_t i=0;i<newBytesToRead;i++) {
        c = serial->hardwareSerial->read();
        buffer[i] = c;
    }

    return newBytesToRead;
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

    for (size_t i=0;i<bytesToWrite;i++) {
        serial->hardwareSerial->write(buffer[i]);
    }

    return bytesToWrite;
}

void rhsp_serialClose(RhspSerial* serial)
{

    if (!serial)
    {
        return;
    }
}

