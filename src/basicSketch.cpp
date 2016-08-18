#include "Arduino.h"

#define FW_VERSION "0.1.7"
void printBanner(void);

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
    setup_mma7260();
}

int ledState = LOW;
int time = 0;

int timeStart = millis();
#define MAX_MILLIS 477218

bool timeLapseMillis(int deltaMs)
{
    int now;
    int delta = 0;

        now = millis();
        if(now < timeStart)
        {
            // this handles timer counter overflow
            // when counter overflows, 'now' becomes < 'start'
            delta = MAX_MILLIS - timeStart + now;
        }
        else
        {
            // regular situation is when 'start' comes before 'now'
            delta = now - timeStart;
        }

        if(delta < deltaMs)
            return false;

        timeStart = now;
        return true;
}

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
    loop_mma7260();

    yield();
}

