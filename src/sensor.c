#include "sensor.h"

SensorData_t* sensorData = NULL;

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

/* 
 * - парсит файл
 * - выделяет паямять под массив структур
 * - заполняет массив структур
 * 
 *   fileName - исходный файл
 *   size - указатель на размер массива структур
 * 
 */
void initSensorData(char* fileName, int* size)
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

    int stringCounter = 0, //строки
        colCounter = 0,    //столбцы  < 6
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
            // temp[colCounter] *= sign;
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
                // printf("%d.\t%d", stringCounter, temp[0]);
                // for (size_t i = 1; i < COLUMN_NUMBER; i++)
                // {
                //     printf(";\t%d", temp[i]);
                // }
                // printf("\n");
                sensorData[dataCounter].year = temp[YEAR];
                sensorData[dataCounter].month = temp[MONTH];
                sensorData[dataCounter].day = temp[DAY];
                sensorData[dataCounter].hour = temp[HOUR];
                sensorData[dataCounter].minute = temp[MINUTE];
                sensorData[dataCounter].temperature = temp[TEMPERATURE];
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

    *size = dataCounter;

    fclose(inputFile);
}


