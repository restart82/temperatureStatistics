#include "config.h"
#include "sensor.h"

extern SensorData_t* sensorData;

int main(int argc, char const *argv[])
{
    int dataSize;
    initSensorData(INPUT_FILE_NAME, &dataSize);

    

    
    return 0;
}
