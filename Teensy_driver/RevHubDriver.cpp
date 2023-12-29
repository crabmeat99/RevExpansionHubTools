/*
 * RevDriver library
 */

#include <errno.h>
#include <cstdio>
#include <string>
#include <vector>

#include "RevHubDriver.h"
#include "LynxCommand.h"
#include "HardwareSerial.h"
#include "Arduino.h"

RevHubDriver::RevHubDriver() 
{
}

RevHubDriver::~RevHubDriver()
{
}

uint8_t RevHubDriver::CreateCRC(u_int8_t *byte, int len) {
    u_int8_t sum=0;
    for (int i=0;i<len;i++) {
        sum += byte[i];
    }
    return sum;
}

void RevHubDriver::LynxSetMotorChannelModeCommand(uint8_t *buf,int *bufLen,int dest_module, int motor, RevHubDriver::motorMode mode, bool floatAtZero) {
    struct MyPacket {
        PacketHeader h;
        PacketMotorMode m;
        uint8_t crc;
    };

    MyPacket *packet;
    packet = (struct MyPacket *) buf;

    packet->h.header = 0x4b44;
    packet->h.length = 11+3;
    packet->h.dest_module=dest_module;
    packet->h.source_module=0;
    packet->h.packet_num=packet_number_;
    packet->h.reference_num=0;
    packet->h.packet_id=(uint16_t)LynxCommand::LynxSetMotorChannelModeCommand;
    packet->m.motor=1;
    packet->m.mode=0;
    packet->m.float_at_zero=mode;
    packet->crc = CreateCRC((u_int8_t *)packet, sizeof(MyPacket)-1);

    // return bufLen
    *bufLen = sizeof(MyPacket);
}

void RevHubDriver::CommandFailSafe(uint8_t *buf,int *bufLen,int dest_module) {
    struct MyPacket {
        PacketHeader h;
        uint8_t crc;
    };

    MyPacket *packet;
    packet = (struct MyPacket *) buf;

    packet->h.header = 0x4b44;
    packet->h.length = 11;
    packet->h.dest_module=dest_module;
    packet->h.source_module=0;
    packet->h.packet_num=packet_number_++;  packet_number_ = (packet_number_==0) ? 1:packet_number_;  // skip zero, saw in trace
    packet->h.reference_num=0;
    packet->h.packet_id=(uint16_t)LynxCommand::COMMAND_NUMBER_FAIL_SAFE;
    packet->crc = CreateCRC((u_int8_t *)packet, sizeof(MyPacket)-1);

    // return bufLen
    *bufLen = sizeof(MyPacket);
}

void RevHubDriver::ReadPacket(HardwareSerial *s) {
    ReadState state = START;
    bool done = false;
    uint8_t incoming_byte;

    while (!done) {
        switch(state) {
            case START:
            if (s->available() > 0) {
                incoming_byte = s->read();
                if (incoming_byte == 0x44) state = GOT44;
            }
            break;
            case  GOT44:
                if (s->available() > 0) {
                incoming_byte = s->read();
                if (incoming_byte == 0x44) state = GOT44;
                else if (incoming_byte == 0x4b) state = FOUND_PACKET;
                else if (incoming_byte ==  0x44) state = GOT44;
                else state = START;
            }
            break;
            case  FOUND_PACKET:
            break;
        }
    }

}
// import time
// import serial
// from commands import *

// def xread_packet(ser):
// 	return

// def read_packet(ser):
// 	state = 'START'
// 	next_state = 'START'
// 	done = False
// 	pbuf = bytearray()
// 	while not done:
// 		if state == 'START':     
// 			while ser.inWaiting() == 0:
// 				pass
// 			temp = ser.read(1)
// 			if temp == b'\x44':
// 				next_state = 'GOT44'
// 		elif state == 'GOT44':
// 			while ser.inWaiting() == 0:
// 				pass
// 			temp = ser.read(1)
// 			if temp == b'\x4b':
// 				next_state = 'FOUND_PACKET'
// 			elif temp == b'\x44':
// 				next_state = 'GOT44'
// 			else:
// 				next_state = 'START'
// 		elif state == 'FOUND_PACKET':
// 			while ser.inWaiting() == 0:
// 				pass
// 			temp = ser.read(1)  # low byte of length
			
// 			# Construct what we have so far
// 			pbuf = bytearray()  # clear buffer
// 			pbuf += b'\x44'
// 			pbuf += b'\x4b'
// 			pbuf += temp

// 			# Read the rest of the packet
// 			len = int.from_bytes(temp, "little")
// 			pbuf += ser.read(len - 3)

// 			next_state = 'DONE'
// 		elif state == 'DONE':
// 			done = True
// 		state = next_state
// 		#time.sleep(.1)

// 	return(pbuf)

