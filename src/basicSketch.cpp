#include "Arduino.h"

#define FW_VERSION "0.1.7"
void printBanner(void);
bool timeLapseMillis(int deltaMs);

void setup_bmp085(void);
void loop_bmp085(void);

void setup_cap1188(void);
void loop_cap1188(void);

void setup_temt6000(void);
void loop_temt6000(void);

void setup_tmp102(void);
void loop_tmp102(void);

void setup_itg3200(void);
void loop_itg3200(void);

void setup_mma7260(void);
void loop_mma7260(void);

void setup_tcs34725(void);
void loop_tcs34725(void);

void setup_lsm303dlhc_a(void);
void loop_lsm303dlhc_a(void);

void setup_lsm303dlhc_m(void);
void loop_lsm303dlhc_m(void);

void setup_l3gd20u(void);
void loop_l3gd20u(void);

void setup_adxl345(void);
void loop_adxl345(void);

void setup_pwm(void);
void loop_pwm(void);

void setup(void)
{
    Serial.begin(115200, SERIAL_8N1);
    printBanner();
    Serial.println("library examples");
    Serial.print("v");
    Serial.println(FW_VERSION);

    pinMode(LED_BUILTIN, OUTPUT);

//    setup_bmp085();
//    setup_cap1188();
//    setup_temt6000();
//    setup_tmp102();
//    setup_itg3200();
//    setup_mma7260();
//    setup_tcs34725();
//    setup_lsm303dlhc_a();
//    setup_lsm303dlhc_m();
//    setup_l3gd20u();
//    setup_adxl345();
    setup_pwm();
}

int ledState = LOW;

void loop(void)
{
    if(timeLapseMillis(1000))
	{
		digitalWrite(LED_BUILTIN, ledState);
		ledState = ledState == LOW ? HIGH : LOW;
	}

//    loop_bmp085();
//    loop_cap1188();
//    loop_temt6000();
//    loop_tmp102();
//    loop_itg3200();
//    loop_mma7260();
//    loop_tcs34725();
//    loop_lsm303dlhc_a();
//    loop_lsm303dlhc_m();
//    loop_l3gd20u();
//    loop_adxl345();
    loop_pwm();

    yield();
}

