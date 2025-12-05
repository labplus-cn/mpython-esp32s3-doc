/* 
	LTR308-ALS library example sketch
*/

#include <LTR308.h>
#include <Wire.h>

LTR308 light;

unsigned char gain = 0;     // Gain setting, values = 0-4 
unsigned char integrationTime = 0;  // Integration ("shutter") time, values 0 - 4
unsigned char measurementRate = 3;  // Interval between DATA_REGISTERS update, values 0 - 7, except 4
unsigned char ID;
unsigned char control;

void setup() {
  Serial.begin(9600);
  Serial.println();
  Serial.println("LTR-308ALS example sketch");
  delay(100);

  light.begin();

  if (light.getPartID(ID)) {
    Serial.print("Got Sensor Part ID: 0X");
    Serial.print(ID, HEX);
    Serial.println();
  }
  else {
    byte error = light.getError();
    printError(error);
  }
  
  if (light.setPowerUp()) {
    Serial.print("Powering up...");
    Serial.println();
  }
  else {
    byte error = light.getError();
    printError(error);
  }
  delay(10);

  if (light.getPower(control)) {
    Serial.print("Control byte is: 0X");
    Serial.print(control, HEX);
    Serial.println();
  }
  else {
    byte error = light.getError();
    printError(error);
  }
  
  Serial.println("Setting Gain...");
  
  if (light.setGain(gain)) {
    light.getGain(gain);
    
    Serial.print("Gain Set to 0X");
    Serial.print(gain, HEX);
    Serial.println();
  }
  else {
    byte error = light.getError();
    printError(error);
  }

  Serial.println("Set timing...");
  if (light.setMeasurementRate(integrationTime, measurementRate)) {
    light.getMeasurementRate(integrationTime, measurementRate);
    
    Serial.print("Timing Set to ");
    Serial.print(integrationTime, HEX);
    Serial.println();

    Serial.print("Meas Rate Set to ");
    Serial.print(measurementRate, HEX);
    Serial.println();
  }
  else {
    byte error = light.getError();
    printError(error);
  }
 
}

void loop() {
  int ms = 1000;
  
  delay(ms);
  unsigned long rawData;
  
  if (light.getData(rawData)) {
    
    Serial.print("Raw Data: ");
    Serial.println(rawData);
  
    double lux;    // Resulting lux value
    boolean good;  // True if sensor is not saturated

    good = light.getLux(gain, integrationTime, rawData, lux);
	
    Serial.print("Lux: ");
    Serial.print(lux);
    if (good) Serial.println(" (valid data)"); 
    else Serial.println(" (BAD)");
  }
  else {
    byte error = light.getError();
    printError(error);
  }
}

void printError(byte error) {
  Serial.print("I2C error: ");
  Serial.print(error,DEC);
  Serial.print(", ");
  
  switch(error) {
    case 0:
      Serial.println("success");
      break;
    case 1:
      Serial.println("data too long for transmit buffer");
      break;
    case 2:
      Serial.println("received NACK on address (disconnected?)");
      break;
    case 3:
      Serial.println("received NACK on data");
      break;
    case 4:
      Serial.println("other error");
      break;
    default:
      Serial.println("unknown error");
  }
}
