#ifndef _LOG_H_
#define _LOG_H_

#include <stdio.h>

#define ARRAY_SIZE(arr) (sizeof(arr)/sizeof(arr[0]))

#define LOG(msg, ...) printf(msg "\n", ##__VA_ARGS__)
#define LOG_ERROR(msg, ...) printf(msg "\n", ##__VA_ARGS__)

#endif
