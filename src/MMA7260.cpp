// http://lusorobotica.com/index.php/topic,902.0.html

#include "Arduino.h"

#define PIN_X 0
#define PIN_Y 1
#define PIN_Z 2

int  valx;
int  valy;
int  valz;

void setup_mma7260(){
	Serial.println("MMA7260 example");
}

void loop_mma7260(){
  valx = analogRead(PIN_X);
  Serial.print("X-axis: ");
  Serial.println((uint8_t)map(valx, 0, 1023, 0, 255),HEX);

  valy = analogRead(PIN_Y);
  Serial.print("Y-axis: ");
  Serial.println((uint8_t)map(valy, 0, 1023, 0, 255),HEX);

  valz = analogRead(PIN_Z);
  Serial.print("Z-axis: ");
  Serial.println((uint8_t)map(valz, 0, 1023, 0, 255),HEX);

  Serial.println();
  delay(1000);
}
