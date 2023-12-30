#include <LynxCommand.h>
#include <RevHubDriver.h>

using namespace std;

// set this to the hardware serial port you wish to use
#define HWSERIAL Serial5

RevHubDriver rh;
uint8_t buffer[20];
int buffer_length;

void setup() {
  Serial.begin(9600);
  HWSERIAL.begin(460800);
  HWSERIAL.transmitterEnable(18);
  HWSERIAL.flush();
  HWSERIAL.clear();
  pinMode(17, OUTPUT);
}

//unsigned char packet[] = {0x44, 0x4B, 0x0E, 0x00, 0x02, 0x00, 0x4C, 0x00, 0x21, 0x10, 0x01, 0xEA, 0x06, 0x0D};
//unsigned char packet[] = {0x44, 0x4B, 0x0B, 0x00, 0x02, 0x00, 0xF7, 0x00, 0x05, 0x7F, 0x17};

void loop() {
  
  // for (unsigned int i=0;i<sizeof(packet);i++) {
  //     HWSERIAL.write(packet[i]);
  // }

  Serial.printf("Starting... \n");
  // rh.LynxSetMotorChannelModeCommand(buffer, &buffer_length, 1, RevHubDriver::RUN_WITHOUT_ENCODER, false);  
  // Serial.printf("Len: %d\n",buffer_length);
  // for (int i=0;i<buffer_length;i++) {
  //   Serial.printf("%02x\n",buffer[i]);
  // }

  rh.CommandFailSafe(buffer, &buffer_length);  
  // for (int i=0;i<buffer_length;i++) {
  //   Serial.printf("%02x\n",buffer[i]);
  // }
  rh.WritePacket(&HWSERIAL, buffer, buffer_length);

  while (HWSERIAL.available()) {
    int extra = HWSERIAL.available();
    Serial.printf("e=%d\n",extra);
    if (extra > 0) {
    int length = rh.ReadPacket(&HWSERIAL);
    Serial.printf("l=%d\n",length);
    }
  }

  //rh.WritePacket(&HWSERIAL, buffer, buffer_length);

  delay(1500);
  //while(1){};
}