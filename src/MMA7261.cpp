#include "Arduino.h"

#define PIN_X 0
#define PIN_Y 1
#define PIN_Z 2

#define PIN_GS1 5
#define PIN_GS2 6

#define BITS_PER_VOLT_3_3V (1023/3.3)
#define VOLTS_PER_BIT_3_3V (3.3/1023.0)

// How many A/D bits for 1g
#define BITS_PER_G_2_5G (BITS_PER_VOLT_3_3V*0.48)
#define BITS_PER_G_3_3G (BITS_PER_VOLT_3_3V*0.36)
#define BITS_PER_G_6_7G (BITS_PER_VOLT_3_3V*0.18)
#define BITS_PER_G_10G (BITS_PER_VOLT_3_3V*0.12)

static float bitsPerG = BITS_PER_G_2_5G;

void setup_mma7261(){
	Serial.println("MMA7261 example");

	pinMode(PIN_GS2, OUTPUT);
	pinMode(PIN_GS1, OUTPUT);

	// slelect g-range: 1.5g, sensitivity: 800mV/g
	digitalWrite(PIN_GS2, LOW);
	digitalWrite(PIN_GS1, LOW);
	bitsPerG = BITS_PER_G_2_5G;

	// slelect g-range: 2g, sensitivity: 600mV/g
//	digitalWrite(PIN_GS2, LOW);
//	digitalWrite(PIN_GS1, HIGH);
//	bitsPerG = BITS_PER_G_3_3G;

	// slelect g-range: 4g, sensitivity: 300mV/g
//	digitalWrite(PIN_GS2, HIGH);
//	digitalWrite(PIN_GS1, LOW);
//	bitsPerG = BITS_PER_G_6_7G;

	// slelect g-range: 6g, sensitivity: 200mV/g
//	digitalWrite(PIN_GS2, HIGH);
//	digitalWrite(PIN_GS1, HIGH);
//	bitsPerG = BITS_PER_G_10G;
}

void loop_mma7261(){
	int  valX;
	int  valY;
	int  valZ;

  valX = analogRead(PIN_X);
  Serial.println("X-axis: ");
  Serial.println(valX-512);
  Serial.print((valX-512)/bitsPerG);
  Serial.println("g");
  Serial.print(valX*VOLTS_PER_BIT_3_3V);
  Serial.println("V");

  valY = analogRead(PIN_Y);
  Serial.println("Y-axis: ");
  Serial.println(valY-512);
  Serial.print((valY-512)/bitsPerG);
  Serial.println("g");
  Serial.print(valY*VOLTS_PER_BIT_3_3V);
  Serial.println("V");

  valZ = analogRead(PIN_Z);
  Serial.println("Z-axis: ");
  Serial.println(valZ-512);
  Serial.print((valZ-512)/bitsPerG);
  Serial.println("g");
  Serial.print(valZ*VOLTS_PER_BIT_3_3V);
  Serial.println("V");

  Serial.println();
  delay(1000);
}
