#ifndef _SENSOR_H_
#define _SENSOR_H_

#include "config.h"

#define COLUMN_NUMBER 6

typedef struct
{
    uint16_t year;
    uint8_t month;
    uint8_t day;
    uint8_t hour;
    uint8_t minute;
    int8_t temperature;
}SensorData_t;

typedef enum
{
    YEAR,
    MONTH,
    DAY,
    HOUR,
    MINUTE,
    TEMPERATURE
}dataStruct_t;

void initSensorData(char* fileName, int* size);




#endif