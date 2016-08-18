#include "Arduino.h"

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
