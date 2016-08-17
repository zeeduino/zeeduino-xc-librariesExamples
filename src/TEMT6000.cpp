
#include "Arduino.h"

// Connected to AD channel 0
#define TEMT_OUT_PIN 0

void setup_temt6000(void)
{
	Serial.println("TEMT-6000 example");
}

#define VCC 3.3

void loop_temt6000(void)
{
	int data = analogRead(TEMT_OUT_PIN);
	float volts = data * VCC / 1024;

	float amps = volts / 10000.0;  // across 10kOhm
	float microamps = amps * 1000000;
	float lux = microamps * 2.0;

	Serial.print("data: ");
	Serial.println(data);
	Serial.print("Vout: ");
	Serial.print(volts);
	Serial.println("V");
	Serial.print("lux: ");
	Serial.println(lux);
	Serial.println();
	delay(1000);
}
