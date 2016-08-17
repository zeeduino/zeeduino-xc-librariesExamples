#include "Arduino.h"

const char * banner[] = {
R"(                  _       _           )",
R"( _______  ___  __| |_   _(_)_ __   ___)",
R"(|_  / _ \/ _ \/ _` | | | | | '_ \ / _ \ )",
R"( / /  __/  __/ (_| | |_| | | | | | (_) |)",
R"(/___\___|\___|\__,_|\__,_|_|_| |_|\___/ )",
NULL};

void printBanner(void)
{
    int bidx = 0;
    while(banner[bidx] != NULL)
    {
    	Serial.println(banner[bidx]);
    	bidx++;
    }
}

