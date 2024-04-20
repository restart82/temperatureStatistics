#ifndef _CONFIG_H
#define _CONFIG_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

#define PRINT_INT(n)    printf("%d\n", n)
#define PRINT_STR(s)    printf("%s\n", s)
#define PRINT_CH(c)     printf("%c\n", c)

#define CURRENT_YEAR    2021
#define INPUT_FILE_NAME  "temperature_small.csv"
// #define INPUT_FILE_NAME  "temperature_big.csv"

#endif