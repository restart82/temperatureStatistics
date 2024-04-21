#include "config.h"
#include "sensor.h"

int main(int argc, char * const *argv)
{
    int rez;
    int commandCounter = 0;

    while ((rez = getopt(argc, argv, "hf:m:y")) != -1)
    {
        switch (rez)
        {
        case 'h':
            printHelp();
            commandCounter++;
            break;
        case 'f':
            char* cd = INPUT_FILE_DIR;
            char* fileName = malloc(strlen(cd) + strlen(optarg) + 1);
            strcpy(fileName, cd);
            strcat(fileName, optarg);
            initSensorData(fileName);
            commandCounter++;
            break;
        case 'm':
        {
            int month = atoi(optarg);
            if (chekMonth(month))
            {
                float monthMean;
                int monthMax;
                int monthMin;

                getMonthStatistics(month, &monthMean, &monthMax, &monthMin);

                printf("\n%d-month temperature statistics:\n", month);
                printf("  - mean\t%.2f\n", monthMean);
                printf("  - max\t\t%d\n", monthMax);
                printf("  - min\t\t%d\n\n\n", monthMin);
            }  
            else
            {
                printf("Error month not exist!");
                exit(3);
            }
            commandCounter++;
            break;
        }
        case 'y':
        {
            float yearMean;
            int yearMax;
            int yearMin;

            getYearStatistics(&yearMean, &yearMax, &yearMin);

            printf("\nyear temperature statistics:\n");
            printf("  - mean\t%.2f\n", yearMean);
            printf("  - max\t\t%d\n", yearMax);
            printf("  - min\t\t%d\n\n\n", yearMin);

            commandCounter++;
            break;
        }
        case '?':
            printHelp();
            commandCounter++;
            break;
        }
    }

    if (commandCounter == 0)
    {
        printHelp();
    }
    
    return 0;
}
