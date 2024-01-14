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
char interfaceName[5];

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
  int r;

  delay(500);
  rhsp_sendKeepAlive(hub,&nackReasonCode);
  delay(50);
  rhsp_setModuleLedPattern1(hub, &nackReasonCode);  
  delay(50);
  rhsp_sendKeepAlive(hub,&nackReasonCode);
  delay(50);
  //char *interfaceName = "DEKA";

  interfaceName[0] = 'D';
  interfaceName[1] = 'E';
  interfaceName[2] = 'K';
  interfaceName[3] = 'A';
  interfaceName[4] = 0;
  r = rhsp_queryInterface(hub, interfaceName, &nackReasonCode);
  Serial.printf("queryInterface: %d\n",r);
  delay(50);
  r = rhsp_ftdiResetControl(hub, 1, &nackReasonCode);
  Serial.printf("ftdiResetControl: %d\n",r);
  delay(50);
  r = rhsp_getModuleStatus(hub, 1, &status, &nackReasonCode);
  Serial.printf("getModuleStatus: %d\n",r);
  delay(50);
  Serial.printf("status = %02x, %02x\n",status.statusWord, status.motorAlerts);
  delay(50);

  r = rhsp_sendKeepAlive(hub,&nackReasonCode);
  Serial.printf("sendKeepAlive: %d\n",r);
  delay(50);
  r = rhsp_getModuleStatus(hub, 1, &status, &nackReasonCode);
  Serial.printf("getModuleStatus: %d\n",r);
  delay(50);

  RhspDebugGroupNumber d = RHSP_DEBUG_GROUP_NUMBER_MODULE_LED;
  RhspVerbosityLevel v = RHSP_VERBOSITY_LEVEL_3;
  r = rhsp_setDebugLogLevel(hub,d,v,&nackReasonCode);
  Serial.printf("setDebugLogLevel: %d\n",r);
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

  //MotorMode m = MOTOR_MODE_OPEN_LOOP; 
  MotorMode m = MOTOR_MODE_REGULATED_POSITION;
  for (int i=0;i<3;i++) {
    rhsp_setMotorChannelMode(hub,i,m,0,&nackReasonCode);
    delay(50);
    rhsp_setMotorTargetVelocity(hub,i,2000,&nackReasonCode);
    delay(50);
    rhsp_setMotorTargetPosition(hub,i,0,10,&nackReasonCode);
    //rhsp_setMotorConstantPower(hub,i,0.3,&nackReasonCode);
    delay(50);
    rhsp_setMotorChannelEnable(hub,i,1,&nackReasonCode);
    delay(50);
  }

  rhsp_setServoPulseWidth(hub,0,1500,&nackReasonCode);
  delay(1000);
  rhsp_setServoPulseWidth(hub,0,2000,&nackReasonCode);
  delay(50);

  // rhsp_setModuleLedPattern2(hub, &nackReasonCode);  
  // delay(50);
  
  // int16_t adcValue;
  // r = rhsp_getADC(hub, 12, 0, &adcValue, &nackReasonCode);
  // delay(50);
  // Serial.printf("Battery 5v(%d): %d\n", r, adcValue);

  // rhsp_getADC(hub, 13, 0, &adcValue, &nackReasonCode);
  // delay(50);
  // Serial.printf("Battery 12v: %d\n", adcValue);
    
  // rhsp_getADC(hub, 14, 0, &adcValue, &nackReasonCode);
  // delay(50);
  // Serial.printf("Temperature (c): %d\n", adcValue/10);

  // rhsp_setModuleLedColor(hub, 255, 0, 0, &nackReasonCode);  // didn't work
  // delay(50);

  unsigned long startMillis = millis();  //some global variables available anywhere in the program
  while (millis() < (startMillis + 5000)) {
    rhsp_sendKeepAlive(hub, &nackReasonCode);
    delay(30);
    rhsp_getModuleStatus(hub, 1, &status, &nackReasonCode);
    delay(30);
    Serial.printf("status = %02x, %02x\n",status.statusWord, status.motorAlerts);
  }

  rhsp_sendFailSafe(hub, &nackReasonCode);

  while(1) {};
  //int r=rhsp_sendKeepAlive(hub, &nackReasonCode);
  //Serial.printf("********* nLoop (%d, %d, %d) %d\n",r1,r2,r3,count);
  //delay(1500);
  count++;
}
