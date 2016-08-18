#include "Arduino.h"

#include "lib/Wire.h"
#include "Adafruit_Sensor.h"
#include "Adafruit_LSM303_U.h"

/* Assign a unique ID to this sensor at the same time */
Adafruit_LSM303_Accel_Unified accel_lsm303dlhc = Adafruit_LSM303_Accel_Unified(54321);

void displaySensorDetails_lsm303dlhc_a(void)
{
  sensor_t sensor;
  accel_lsm303dlhc.getSensor(&sensor);
  Serial.println("------------------------------------");
  Serial.print  ("Sensor:       "); Serial.println(sensor.name);
  Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
  Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
  Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println(" m/s^2");
  Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println(" m/s^2");
  Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println(" m/s^2");
  Serial.println("------------------------------------");
  Serial.println("");
  delay(500);
}

void setup_lsm303dlhc_a(void)
{
  Serial.println("Accelerometer Test"); Serial.println("");

  /* Initialise the sensor */
  if(!accel_lsm303dlhc.begin())
  {
	/* There was a problem detecting the ADXL345 ... check your connections */
	Serial.println("Ooops, no LSM303 detected ... Check your wiring!");
	while(1);
  }

  /* Display some basic information on this sensor */
  displaySensorDetails_lsm303dlhc_a();
}

void loop_lsm303dlhc_a(void)
{
	  /* Get a new sensor event */
	  sensors_event_t event;
	  accel_lsm303dlhc.getEvent(&event);

	  /* Display the results (acceleration is measured in m/s^2) */
	  Serial.print("X: "); Serial.print(event.acceleration.x); Serial.print("  ");
	  Serial.print("Y: "); Serial.print(event.acceleration.y); Serial.print("  ");
	  Serial.print("Z: "); Serial.print(event.acceleration.z); Serial.print("  ");Serial.println("m/s^2 ");
	  delay(500);
}
