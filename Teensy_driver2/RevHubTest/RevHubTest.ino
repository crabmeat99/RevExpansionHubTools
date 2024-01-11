#include "rhsp_revhub.h"
#include "rhsp_rhsp.h"                        
#include "rhsp_deviceControl.h"
#include "HardwareSerial.h"
#include "rhsp_serial.h"

using namespace std;

// set this to the hardware serial port you wish to use
#define HWSERIAL Serial5

static RhspRevHub* hub;
static RhspSerial* serial;
RhspModuleStatus status;
uint8_t nackReasonCode;
int count=0;

enum FailSafeState {
  SEND_FAILSAFE,
  WAIT_FOR_ACK
};

FailSafeState failsafe_state = SEND_FAILSAFE;


void setup() {
  Serial.begin(115200);
  Serial.println("Start Setup");

  serial = rhsp_serialInit(&Serial5);
  hub = rhsp_allocRevHub(serial, 2);
}

void loop() {


  delay(500);
  rhsp_sendKeepAlive(hub,&nackReasonCode);
  delay(50);
  rhsp_setModuleLedPattern1(hub, &nackReasonCode);  
  delay(50);
  rhsp_getModuleStatus(hub, 0, &status, &nackReasonCode);
  delay(50);
  Serial.printf("status = %02x, %02x\n",status.statusWord, status.motorAlerts);
  delay(50);
  rhsp_sendKeepAlive(hub,&nackReasonCode);
  delay(50);
  // r1=rhsp_sendFailSafe(hub, &nackReasonCode); 
  // delay(50);

  for (int i=0;i<6;i++) {
    rhsp_setServoConfiguration(hub, i, 20000, &nackReasonCode);
    delay(50);
  }

  for (int i=0;i<6;i++) {
      rhsp_setServoEnable(hub,i,1,&nackReasonCode);
    delay(50);
  }

  rhsp_setServoPulseWidth(hub,0,1500,&nackReasonCode);
  delay(1000);
  rhsp_setServoPulseWidth(hub,0,2000,&nackReasonCode);
  delay(50);

  rhsp_setModuleLedPattern2(hub, &nackReasonCode);  
  delay(50);
  
  int16_t adcValue;
  rhsp_getADC(hub, 12, 0, &adcValue, &nackReasonCode);
  delay(50);
  Serial.printf("Battery 5v: %d\n", adcValue);

  rhsp_getADC(hub, 13, 0, &adcValue, &nackReasonCode);
  delay(50);
  Serial.printf("Battery 12v: %d\n", adcValue);
    
  rhsp_getADC(hub, 14, 0, &adcValue, &nackReasonCode);
  delay(50);
  Serial.printf("Temperature (c): %d\n", adcValue/10);

  rhsp_setModuleLedColor(hub, 255, 0, 0, &nackReasonCode);  // didn't work
  delay(50);

  while (1) {
    rhsp_sendKeepAlive(hub, &nackReasonCode);
    delay(200);
    rhsp_getModuleStatus(hub, 0, &status, &nackReasonCode);
    delay(50);
    Serial.printf("status = %02x, %02x\n",status.statusWord, status.motorAlerts);
  }

  //int r=rhsp_sendKeepAlive(hub, &nackReasonCode);
  //Serial.printf("********* nLoop (%d, %d, %d) %d\n",r1,r2,r3,count);
  //delay(1500);
  count++;
}
