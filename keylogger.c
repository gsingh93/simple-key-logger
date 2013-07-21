#include <stdio.h>
#include <fcntl.h>  // open
#include <stdlib.h>
#include <string.h> // strerror
#include <linux/input.h>

typedef struct input_event input_event;

static void rootCheck();
static char* getKeyboardDeviceFileName();
static int openKeyboardDeviceFile();
static char getKeyChar();

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

   input_event event;
   while (read(kbd_fd, &event, sizeof(input_event)) > 0) {
      if (event.type == EV_KEY) {
         printf("%d\n", event.code);
      }
   }

   printf("%d\n", kbd_fd);
   close(kbd_fd);
   return 0;
}
