#include <LynxCommand.h>
#include <RevHubDriver.h>

using namespace std;

// set this to the hardware serial port you wish to use
#define HWSERIAL Serial5

RevHubDriver rh;
uint8_t buffer[20];
int buffer_length;

enum FailSafeState {
  SEND_FAILSAFE,
  WAIT_FOR_ACK
};

FailSafeState failsafe_state = SEND_FAILSAFE;

void setup() {
  Serial.begin(115200);
  HWSERIAL.begin(460800);
  HWSERIAL.transmitterEnable(18);
  HWSERIAL.flush();
  HWSERIAL.clear();
  pinMode(17, OUTPUT);
  digitalWrite(17, LOW); 
}

//unsigned char packet[] = {0x44, 0x4B, 0x0E, 0x00, 0x02, 0x00, 0x4C, 0x00, 0x21, 0x10, 0x01, 0xEA, 0x06, 0x0D};
//unsigned char packet[] = {0x44, 0x4B, 0x0B, 0x00, 0x02, 0x00, 0xF7, 0x00, 0x05, 0x7F, 0x17};

void loop() {
  
  // for (unsigned int i=0;i<sizeof(packet);i++) {
  //     HWSERIAL.write(packet[i]);
  // }

  //Serial.printf("Loop... \n");
  // rh.LynxSetMotorChannelModeCommand(buffer, &buffer_length, 1, RevHubDriver::RUN_WITHOUT_ENCODER, false);  
  // Serial.printf("Len: %d\n",buffer_length);
  // for (int i=0;i<buffer_length;i++) {
  //   Serial.printf("%02x\n",buffer[i]);
  // }

  switch (failsafe_state) {
    case SEND_FAILSAFE:
      delay(500);
      rh.CommandFailSafe(buffer, &buffer_length); 
      Serial.printf("Send FailSafe num = %d\n",buffer[6]); 
      rh.WritePacket(&HWSERIAL, buffer, buffer_length);
      failsafe_state = SEND_FAILSAFE;
    break;

    case WAIT_FOR_ACK:
      int a = HWSERIAL.available();
      if (a > 9) {
        Serial.printf("\nBefore ReadPacket\n");
        int length = rh.ReadPacket(&HWSERIAL);
        Serial.printf("packet number=%d\n",length);
        Serial.printf("print len: %d\n",rh.read_buffer_length);
        Serial.printf("Ack n = %d \n",rh.read_buffer[7]);
        for (int i=0;i<rh.read_buffer_length;i++) Serial.printf("b: %d %02x\n",i,(int)rh.read_buffer[i]);
        failsafe_state = SEND_FAILSAFE;
      }
  }

  //delay(1500);
}