/*
 *
*/

#ifndef _REV_DRIVER_H_INCLUDED
#define _REV_DRIVER_H_INCLUDED

#include <Arduino.h>
#include <cstdint>

using namespace std;

struct MessageMotor {
	uint8_t motor;
  uint16_t power;
};

struct PayloadTwoBytes {
	uint8_t byte_1;
	uint8_t byte_2;
};

struct __attribute__ ((packed)) PacketHeader {
    uint16_t header;
    uint16_t length;
    uint8_t dest_module;
    uint8_t source_module;
    uint8_t packet_num;
    uint8_t reference_num;
    uint16_t packet_id;
};

struct __attribute__ ((packed)) PacketMotorMode {
    uint8_t motor;
    uint8_t mode;
    uint8_t float_at_zero;
};

class RevHubDriver {

public:
  enum motorMode {
    RUN_WITHOUT_ENCODER = 0,
    RUN_USING_ENCODER = 1,
    RUN_TO_POSITION = 2
  };

  enum ReadState {
    START,
    GOT44,
    FOUND_PACKET
  };

  HardwareSerial *hw_serial;

  u_int8_t CreateCRC(u_int8_t *byte, int len);
  void LynxSetMotorChannelModeCommand(uint8_t *buf,int *bufLen, uint8_t motor, RevHubDriver::motorMode mode, bool floatAtZero);
  void LynxSetMotorConstantPowerCommand(uint8_t *buf, int *bufLen, uint8_t motor, uint16_t power);
  void LynxSetMotorTargetVelocityCommand(uint8_t *buf,int *bufLen, uint8_t motor, int16_t velocity);
  void LynxSetMotorChannelEnableCommand(uint8_t *buf,int *bufLen, uint8_t motor, uint8_t enable);
  void LynxSetMotorTargetPositionCommand(uint8_t *buf,int *bufLen, uint8_t motor, uint32_t target, uint16_t tolerance);
  void LynxGetMotorPIDFControlLoopCoefficientsCommand(uint8_t *buf,int *bufLen, uint8_t motor, uint8_t mode);



  void CommandFailSafe(uint8_t *packet,int *packetLen);
  int ReadPacket(HardwareSerial *s);

  RevHubDriver();
  virtual ~RevHubDriver();

  uint8_t packet_number_=1;
  uint8_t dest_module_=2;

protected:

};

#endif




