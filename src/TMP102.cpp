
#include "Arduino.h"
#include "lib/Wire.h"

// http://playground.arduino.cc/Code/TMP102

#define TMP102_I2C_ADDRESS 72 /* This is the I2C address for our chip.
This value is correct if you tie the ADD0 pin to ground. See the datasheet for some other values. */

void getTemp102(){
  byte firstbyte, secondbyte; //these are the bytes we read from the TMP102 temperature registers
  int val; /* an int is capable of storing two bytes, this is where we "chuck" the two bytes together. */
  float convertedtemp; /* We then need to multiply our two bytes by a scaling factor, mentioned in the datasheet. */


  /* Reset the register pointer (by default it is ready to read temperatures)
You can alter it to a writeable register and alter some of the configuration -
the sensor is capable of alerting you if the temperature is above or below a specified threshold. */

  Wire.beginTransmission(TMP102_I2C_ADDRESS); //Say hi to the sensor.
  Wire.write(0x00);
  Wire.endTransmission();
  Wire.requestFrom(TMP102_I2C_ADDRESS, 2);
  Wire.endTransmission();


firstbyte      = (Wire.read());
secondbyte     = (Wire.read());
val = ((firstbyte) << 4);
val |= (secondbyte >> 4);
convertedtemp = val*0.0625;


  Serial.print("firstbyte is ");
  Serial.print("\t");
  Serial.println(firstbyte, BIN);
  Serial.print("secondbyte is ");
  Serial.print("\t");
  Serial.println(secondbyte, BIN);
  Serial.print("Concatenated byte is ");
  Serial.print("\t");
  Serial.println(val, BIN);
  Serial.print("Temperature: ");
  Serial.print("\t");
  Serial.print(convertedtemp);
  Serial.println(" C");
  Serial.println();
}

void setup_tmp102(void)
{
    Wire.begin();
	Serial.println("TMP102 example");
}

void loop_tmp102(void)
{
	getTemp102();
	delay(1000);
}
