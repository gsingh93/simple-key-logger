#ifndef _LOG_H_
#define _LOG_H_

#include <stdio.h>

#define ASSERT_ON_COMPILE(expn) typedef char __C_ASSERT__[(expn) ? 1 : -1]

#define ARRAY_SIZE(arr) (sizeof(arr)/sizeof(arr[0]))

#define LOG(msg, ...) printf(msg "\n", ##__VA_ARGS__)
#define LOG_ERROR(msg, ...) printf(msg "\n", ##__VA_ARGS__)

#endif
