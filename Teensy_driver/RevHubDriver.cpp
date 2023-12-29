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

void RevHubDriver::LynxSetMotorChannelModeCommand(uint8_t *buffer, int *buffer_length, uint8_t motor, RevHubDriver::MotorMode mode, bool floatAtZero) {
    struct MyPacket {
        PacketHeader h;
        PacketMotorMode m;
        uint8_t crc;
    };

    MyPacket *packet;
    packet = (struct MyPacket *) buffer;

    packet->h.header = 0x4b44;
    packet->h.length = 11+3;
    packet->h.dest_module=RevHubDriver::dest_module_;
    packet->h.source_module=0;
    packet->h.packet_num=packet_number_ = (packet_number_++==0) ? 1:packet_number_;  // skip zero, saw in trace
    packet->h.reference_num=0;
    packet->h.packet_id=(uint16_t)LynxCommand::LynxSetMotorChannelModeCommand;
    packet->m.motor=1;
    packet->m.mode=mode;
    packet->m.float_at_zero=mode;
    packet->crc = CreateCRC((u_int8_t *)packet, sizeof(MyPacket)-1);

    // return buffer_length
    *buffer_length = sizeof(MyPacket);
}

void RevHubDriver::LynxSetMotorConstantPowerCommand(uint8_t *buffer,int *buffer_length, uint8_t motor, uint16_t power) {
    struct MyPacket {
        PacketHeader h;
        uint8_t motor;
        int16_t power;
        uint8_t crc;
    };

    MyPacket *packet;
    packet = (struct MyPacket *) buffer;

    packet->h.header = 0x4b44;
    packet->h.length = 10+3+1;
    packet->h.dest_module=dest_module_;
    packet->h.source_module=0;
    packet->h.packet_num=packet_number_ = (packet_number_++==0) ? 1:packet_number_;  // skip zero, saw in trace
    packet->h.reference_num=0;
    packet->h.packet_id=(uint16_t)LynxCommand::LynxSetMotorConstantPowerCommand;
    packet->motor=motor;
    packet->power=power;
    packet->crc = CreateCRC((u_int8_t *)packet, sizeof(MyPacket)-1);

    // return buffer_length
    *buffer_length = sizeof(MyPacket);
}



int yyy() {
    int x;

    x=10;
    return x;
}

void RevHubDriver::CommandFailSafe(uint8_t *buffer,int *buffer_length) {
    struct MyPacket {
        PacketHeader h;
        uint8_t crc;
    };

    MyPacket *packet;
    packet = (struct MyPacket *) buffer;

    packet->h.header = 0x4b44;
    packet->h.length = 11;
    packet->h.dest_module=dest_module_;
    packet->h.source_module=0;
    packet->h.packet_num=packet_number_ = (packet_number_++==0) ? 1:packet_number_;  // skip zero, saw in trace
    packet->h.reference_num=0;
    packet->h.packet_id=(uint16_t)LynxCommand::COMMAND_NUMBER_FAIL_SAFE;
    packet->crc = CreateCRC((u_int8_t *)packet, sizeof(MyPacket)-1);

    // return buffer_length
    *buffer_length = sizeof(MyPacket);
}

// void xxx() {
//     // for (int i=0;i<buffer_length;i++) {
//     //     s->write(buffer[i]);
//     // }
// }

int RevHubDriver::ReadPacket(HardwareSerial *s) {
    ReadState state = START;
    bool done = false;
    uint8_t incoming_byte;
    uint16_t length;

    digitalWrite(17, HIGH);
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
                    if (incoming_byte == 0x4b) state = FOUND_PACKET;
                    else if (incoming_byte == 0x44) state = GOT44;
                    else state = START;
                }
            break;
            case  FOUND_PACKET:
                // read length 16bit word
                while (s->available() < 2) {}
                incoming_byte = s->read();
                length = incoming_byte;
                incoming_byte = s->read();
                length = length | incoming_byte << 8;
                // for now, eat the rest of the packet
                while (s->available() < (length-4)) {};
                for (int i=0;i< length - 4;i++) {
                    incoming_byte = s->read();
                }
                done = true;
            break;
        }
    }
    digitalWrite(17, LOW); 
    return length;
}
