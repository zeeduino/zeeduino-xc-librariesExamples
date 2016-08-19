/*
 * DataFlash_sectorErase.cpp
 *
 *  Created on: Aug 18, 2016
 *      Author: iceman
 */

#include "Arduino.h"

#include "lib/SPI.h"
#include "DataFlash.h"

DataFlash dataflash_se;
uint8_t currentSector;

static const uint16_t bufferSize[7]     = { 264, 264, 264, 264, 528, 528, 528 };
static const uint16_t pagesSector0b[7]  = { 120, 120, 248, 248, 248, 120, 248 };
static const uint16_t pagesPerSector[7] = { 128, 128, 256, 256, 256, 128, 256 };

void fillPages(uint16_t pageStart, uint16_t pageCount, uint16_t bufferSize)
{
    uint8_t  buffer = 0;
    uint16_t page   = 0;

    for(page=pageStart; page<(pageStart+pageCount); page++)
    {
        Serial.print("Fill page ");
        Serial.print(page, HEX);
        dataflash_se.bufferWrite(buffer, 0);
        for(uint16_t j=0; j<bufferSize; j++)
        {
            SPI.transfer( j & 0xff );
        }
        dataflash_se.bufferToPage(buffer, page);

        int8_t res = dataflash_se.isPageEqualBuffer(page, buffer);
        Serial.print(" status: ");
        Serial.print(res, HEX);
        Serial.println();

        buffer ^= 1;
    }
}

void setBuffer(uint8_t buffer, uint8_t val, uint16_t size)
{
    dataflash_se.bufferWrite(buffer, 0);
    for(uint16_t i=0; i<size; i++)
    {
        SPI.transfer(val);
    }
}

uint16_t  checkPages(uint16_t pageStart, uint16_t pageCount)
{
    uint16_t count = 0;
    int8_t res;
    for(uint16_t page=pageStart; page<(pageCount+pageStart); page++)
    {
        res = dataflash_se.isPageEqualBuffer(page, 0);
        if(res)
        {
            count++;
        }

        Serial.print("Page ");
        Serial.print(page, HEX);
        if(res)
        {
            Serial.println(" was succesfully erased.");
        }
        else
        {
            Serial.println(" was not properly erased.");
        }
    }
    return count;
}

int8_t testSectorErase(int8_t sectorId)
{
    uint16_t pageStart, pageCount;

    uint8_t status = dataflash_se.status();
    uint8_t deviceIndex = ((status & 0x38) >> 3) - 1;

    if(sectorId == AT45_SECTOR_0A)
    {
        pageStart = 0;
        pageCount = 8;
    }
    else if(sectorId == AT45_SECTOR_0B)
    {
        pageStart = 8;
        pageCount = pagesSector0b[deviceIndex];
    }
    else
    {
        pageStart = pagesPerSector[deviceIndex] * static_cast<uint16_t>(sectorId);
        pageCount = pagesPerSector[deviceIndex];
    }
    Serial.println();
    Serial.print("Testing sector ");
    Serial.print(sectorId, HEX);
    Serial.println();

    Serial.println("Fill pages");
    fillPages(pageStart, pageCount, bufferSize[deviceIndex]);

    Serial.println("Erasing sector");
    dataflash_se.sectorErase(sectorId);

    Serial.println("Check pages");
    setBuffer(0, 0xff, bufferSize[deviceIndex]);
    uint16_t res = checkPages(pageStart, pageCount);
    if(res != pageCount)
    {
        Serial.println();
        Serial.print("FAILURE!");
        Serial.println();
        return 0;
    }
    return 1;
}

void setup_dataflash_at45d_sectorErase()
{
    uint8_t status;
    DataFlash::ID id;

    /* Initialize SPI */
    SPI.begin();

    /* Let's wait 1 second, allowing use to press the serial monitor button :p */
    delay(1000);

    /* Initialize dataflash_se */
    dataflash_se.setup(10,11,12);

    delay(10);

    /* Read status register */
    status = dataflash_se.status();

    /* Read manufacturer and device ID */
    dataflash_se.readID(id);

    /* Set baud rate for serial communication */
    Serial.begin(115200);

    /* Display status register */
    Serial.print("Status register :");
    Serial.print(status, BIN);
    Serial.println();

    /* Display manufacturer and device ID */
    Serial.print("Manufacturer ID :"); // Should be 00011111
    Serial.print(id.manufacturer, HEX);
    Serial.println();

    Serial.print("Device ID (part 1) :"); // Should be 00011111
    Serial.print(id.device[0], HEX);
    Serial.println();

    Serial.print("Device ID (part 2) :"); // Should be 00000000
    Serial.print(id.device[1], HEX);
    Serial.println();

    Serial.print("Extended Device Information String Length :"); // 00000000
    Serial.print(id.extendedInfoLength, HEX);
    Serial.println();

    uint8_t buffer = 0;
    uint8_t page   = 0;

    Serial.println("Manual buffer erase : on");
    dataflash_se.manualErase();

    int8_t res = 0;
    res += testSectorErase(AT45_SECTOR_0A);
    res += testSectorErase(AT45_SECTOR_0B);

    for(uint8_t i=10; i<14; i++)
    {
        res += testSectorErase(i);
    }

    Serial.println();
	Serial.print("Test ");
    if(res != 6)
    {
        Serial.println("failed!");
    }
    else
    {
        Serial.println("successful!");
    }
}

void loop_dataflash_at45d_sectorErase()
{
}

