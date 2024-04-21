#include "sensor.h"

SensorData_t* sensorData = NULL;
int sensorDataSize = 0;

int getDataStringNumber(FILE* file)
{
    int stringCounter = 0;
    char data[30] = {0};
    rewind(file);
    while (fscanf(file, "%s", &data) != EOF)
    {
        stringCounter++;
    }
    rewind(file);
    return stringCounter;
}

void initSensorData(char* fileName)
{
    FILE* inputFile;

    if ((inputFile = fopen(fileName, "r")) == NULL)
    {
        perror("Error occured while opening input file!");
        exit (1);
    }

    int stringNumber = getDataStringNumber(inputFile);
    sensorData = calloc(stringNumber, sizeof(SensorData_t));

    if (sensorData == NULL)
    {
        perror("Error no memory allocation!");
        exit(2);
    }

    int stringCounter = 0,
        colCounter = 0,
        errorCounter = 0,
        dataCounter = 0;
    int sign = 1;
    char c;

    int temp[COLUMN_NUMBER] = {0};

    while (1)
    {
        c = fgetc(inputFile);
        if (c >= '0' && c <= '9')
        {
            temp[colCounter] *= 10;
            temp[colCounter] += (c - '0');
        }
        else if (c == '-')
        {
            sign = (-1);
        }
        else if (c == ';')
        {
            switch (colCounter)
            {
            case YEAR:
                if (temp[colCounter] == CURRENT_YEAR)
                {
                    errorCounter++;
                }
                break;
            case MONTH:
                if (temp[colCounter] > 0 && temp[colCounter] <= 12)
                {
                    errorCounter++;
                }
                break;
            case DAY:
                if (temp[colCounter] > 0 && temp[colCounter] <= 31)
                {
                    errorCounter++;
                }
                break;
            case HOUR:
                if (temp[colCounter] >= 0 && temp[colCounter] <= 24)
                {
                    errorCounter++;
                }
                break;
            case MINUTE:
                if (temp[colCounter] >= 0 && temp[colCounter] <= 60)
                {
                    errorCounter++;
                }
                break;
            }

            colCounter++;
        }
        else if (c == '\n' || c == EOF)
        {
            temp[colCounter] *= sign;

            if (colCounter == TEMPERATURE)
            {
                if (temp[colCounter] >= -99 && temp[colCounter] <= 99)
                {
                    errorCounter++;
                }
            }
            
            if (errorCounter == COLUMN_NUMBER)
            {
                #ifdef DEBUG
                printf("%d.\t%d", stringCounter, temp[0]);
                for (size_t i = 1; i < COLUMN_NUMBER; i++)
                {
                    printf(";\t%d", temp[i]);
                }
                printf("\n");
                #endif
                sensorData[dataCounter].year = (uint16_t)temp[YEAR];
                sensorData[dataCounter].month = (uint8_t)temp[MONTH];
                sensorData[dataCounter].day = (uint8_t)temp[DAY];
                sensorData[dataCounter].hour = (uint8_t)temp[HOUR];
                sensorData[dataCounter].minute = (uint8_t)temp[MINUTE];
                sensorData[dataCounter].temperature = (int8_t)temp[TEMPERATURE];
                dataCounter++;
            }
            else
            {
                printf("ERROR in line %d\n", stringCounter + 1);
            }
            sign = 1;
            stringCounter++;
            colCounter = 0;
            errorCounter = 0;
            for (size_t i = 0; i < COLUMN_NUMBER; i++)
            {
                temp[i] = 0;
            }
            if (c == EOF)
            {
                break;
            }
        }
        else if (c != ' ')
        {
            errorCounter--;
        }
    }

    sensorDataSize = dataCounter;

    fclose(inputFile);
}

void getYearStatistics(float* ptrMean, int* ptrMaximum, int* ptrMininum)
{
    float mean = 0;
    int min = sensorData[0].temperature;
    int max = sensorData[0].temperature;

    for (int i = 0; i < sensorDataSize; i++)
    {
        mean += sensorData[i].temperature;

        if (sensorData[i].temperature > max)
        {
            max = sensorData[i].temperature;
        }

        if (sensorData[i].temperature < min)
        {
            min = sensorData[i].temperature;
        }
    }
    mean = mean / sensorDataSize;

    *ptrMean = mean;
    *ptrMaximum = max;
    *ptrMininum = min;
}

void getMonthStatistics(int monthNumber, float* ptrMean,
        int* ptrMaximum, int* ptrMininum)
{
    float mean = 0;
    int counter = 0;
    int min = 99;
    int max = -99;

    for (int i = 0; i < sensorDataSize; i++)
    {
        if (sensorData[i].month == monthNumber)
            {
            mean += sensorData[i].temperature;

            if (sensorData[i].temperature > max)
            {
                max = sensorData[i].temperature;
            }

            if (sensorData[i].temperature < min)
            {
                min = sensorData[i].temperature;
            }

            counter++;
        }
    }
    mean = mean / counter;

    *ptrMean = mean;
    *ptrMaximum = max;
    *ptrMininum = min;
}

bool chekMonth(int month)
{
    return (month >= 0 && month <= 12);
}

void printHelp()
{
    printf("\nmanual:\n");
    printf("  -h - help\n");
    printf("  -f <filename.csv> - enter input file\n");
    printf("  -m <month number> - get month statistics\n");
    printf("  -y - get year statistics\n\n");
}

