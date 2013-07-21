#ifndef _CONFIG_H_
#define _CONFIG_H_

typedef struct Config {
   char *logFile;
   char *deviceFile;
} Config;

void Config_cleanup(Config *config);

#endif