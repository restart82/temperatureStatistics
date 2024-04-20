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

/* 
 * - парсит файл
 * - выделяет паямять под массив структур
 * - заполняет массив структур
 * 
 *   fileName - исходный файл
 * 
 */
void initSensorData(char* fileName);

/*
* - вычисляет среднюю, минимальную и максимальную температуры за год
* 
*   ptrMean - указатель на среднюю годовую температуру
*   ptrMaximum - указатель на максимальную годовую температуру
*   ptrMininum - указатель на минимальную годовую температуру
* 
*/
void getYearStatistics(float* ptrMean, int* ptrMaximum, int* ptrMininum);

/*
* - вычисляет среднюю, минимальную и максимальную температуры за указанный месяц
* 
*   monthNumber - месяц
*   ptrMean - указатель на среднюю месячную температуру
*   ptrMaximum - указатель на максимальную месячную температуру
*   ptrMininum - указатель на минимальную месячную температуру
* 
*/
void getMonthStatistics(int monthNumber, float* ptrMean, int* ptrMaximum, int* ptrMininum);

bool chekMonth(int month);

void printHelp();

#endif